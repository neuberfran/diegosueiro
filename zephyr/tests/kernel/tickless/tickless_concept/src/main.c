/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <power.h>

#define STACK_SIZE (512 + CONFIG_TEST_EXTRA_STACKSIZE)
#define NUM_THREAD 4
static K_THREAD_STACK_ARRAY_DEFINE(tstack, NUM_THREAD, STACK_SIZE);
static struct k_thread tdata[NUM_THREAD];
/*for those not supporting tickless idle*/
#ifndef CONFIG_TICKLESS_IDLE
#define CONFIG_TICKLESS_IDLE_THRESH 20
#endif
/*sleep duration tickless*/
#define SLEEP_TICKLESS	 __ticks_to_ms(CONFIG_TICKLESS_IDLE_THRESH)

/*sleep duration with tick*/
#define SLEEP_TICKFUL	 __ticks_to_ms(CONFIG_TICKLESS_IDLE_THRESH - 1)

/*slice size is set as half of the sleep duration*/
#define SLICE_SIZE	 __ticks_to_ms(CONFIG_TICKLESS_IDLE_THRESH >> 1)
#define SLICE_SIZE_CYCLES \
	(u32_t)(SLICE_SIZE * sys_clock_hw_cycles_per_sec() / 1000)

/*mimimum slice duration accepted by the test: (SLICE_SIZE - 1ms) */
#define SLICE_SIZE_MIN_CYCLES \
	(u32_t)(SLICE_SIZE_CYCLES - (sys_clock_hw_cycles_per_sec() / 1000))

/*maximum slice duration accepted by the test: (SLICE_SIZE + 1ms) */
#define SLICE_SIZE_MAX_CYCLES \
	(u32_t)(SLICE_SIZE_CYCLES + (sys_clock_hw_cycles_per_sec() / 1000))

/*align to millisecond boundary*/
#if defined(CONFIG_ARCH_POSIX)
#define ALIGN_MS_BOUNDARY()		       \
	do {				       \
		u32_t t = k_uptime_get_32();   \
		while (t == k_uptime_get_32()) \
			k_busy_wait(50);       \
	} while (0)
#else
#define ALIGN_MS_BOUNDARY()		       \
	do {				       \
		u32_t t = k_uptime_get_32();   \
		while (t == k_uptime_get_32()) \
			;		       \
	} while (0)
#endif
K_SEM_DEFINE(sema, 0, NUM_THREAD);
static u32_t elapsed_slice;

static u32_t cycles_delta(u32_t *reftime)
{
	u32_t now, delta;

	now = k_cycle_get_32();
	delta = now - *reftime;
	*reftime = now;

	return delta;
}


static void thread_tslice(void *p1, void *p2, void *p3)
{
	u32_t t = cycles_delta(&elapsed_slice);

	TC_PRINT("elapsed slice %d, expected: <%d, %d>\n",
		t, SLICE_SIZE_MIN_CYCLES, SLICE_SIZE_MAX_CYCLES);

	/**TESTPOINT: verify slicing scheduler behaves as expected*/
	zassert_true(t >= SLICE_SIZE_MIN_CYCLES, NULL);
	zassert_true(t <= SLICE_SIZE_MAX_CYCLES, NULL);

	/*keep the current thread busy for more than one slice*/
	k_busy_wait(1000 * SLEEP_TICKLESS);
	k_sem_give(&sema);
}
/**
 * @addtogroup kernel_tickless_tests
 * @{
 */

/**
 * @brief Verify system clock with and without tickless idle
 *
 * @details Check if system clock recovers and works as expected
 * when tickless idle is enabled and disabled.
 */
void test_tickless_sysclock(void)
{
	volatile u32_t t0, t1;

	ALIGN_MS_BOUNDARY();
	t0 = k_uptime_get_32();
	k_sleep(SLEEP_TICKLESS);
	t1 = k_uptime_get_32();
	TC_PRINT("time %d, %d\n", t0, t1);
	/**TESTPOINT: verify system clock recovery after exiting tickless idle*/
	zassert_true((t1 - t0) >= SLEEP_TICKLESS, NULL);

	ALIGN_MS_BOUNDARY();
	t0 = k_uptime_get_32();
	k_sem_take(&sema, SLEEP_TICKFUL);
	t1 = k_uptime_get_32();
	TC_PRINT("time %d, %d\n", t0, t1);
	/**TESTPOINT: verify system clock recovery after exiting tickful idle*/
	zassert_true((t1 - t0) >= SLEEP_TICKFUL, NULL);
}

/**
 * @brief Verify tickless functionality with time slice
 *
 * @details Create threads of equal priority and enable time
 * slice. Check if the threads execute more than a tick.
 */
void test_tickless_slice(void)
{
	k_tid_t tid[NUM_THREAD];

	k_sem_reset(&sema);
	/*enable time slice*/
	k_sched_time_slice_set(SLICE_SIZE, K_PRIO_PREEMPT(0));

	/*synchronize to tick boundary*/
	k_sleep(1);

	/*create delayed threads with equal preemptive priority*/
	for (int i = 0; i < NUM_THREAD; i++) {
		tid[i] = k_thread_create(&tdata[i], tstack[i], STACK_SIZE,
					 thread_tslice, NULL, NULL, NULL,
					 K_PRIO_PREEMPT(0), 0,
					 SLICE_SIZE + __ticks_to_ms(1));
	}

	/*synchronize to tick boundary.*/
	k_sleep(1);

	/*set reference time to last tick boundary*/
	elapsed_slice = z_tick_get_32() * sys_clock_hw_cycles_per_tick();

	/*relinquish CPU and wait for each thread to complete*/
	for (int i = 0; i < NUM_THREAD; i++) {
		k_sem_take(&sema, K_FOREVER);
	}

	/*test case teardown*/
	for (int i = 0; i < NUM_THREAD; i++) {
		k_thread_abort(tid[i]);
	}
	/*disable time slice*/
	k_sched_time_slice_set(0, K_PRIO_PREEMPT(0));
}

/**
 * @}
 */
void test_main(void)
{
	ztest_test_suite(tickless_concept,
			 ztest_unit_test(test_tickless_sysclock),
			 ztest_unit_test(test_tickless_slice));
	ztest_run_test_suite(tickless_concept);
}