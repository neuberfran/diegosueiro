# SPDX-License-Identifier: BSD-3-Clause

add_local_sources(sof notifier.c)

if (CONFIG_AMS)
	add_local_sources(sof ams.c)
endif()

if (CONFIG_MULTICORE)
	add_local_sources(sof cpu.c)
endif()
