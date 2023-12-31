/*
 * Copyright (c) 2019 Centaur Analytics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <sensor.h>
#include <misc/printk.h>
#include <misc/__assert.h>
#include <logging/log.h>
#include <gpio.h>

void main(void)
{
	printk("Running on %s!\n", CONFIG_ARCH);
	struct device *dev = device_get_binding(DT_INST_0_TI_HDC_LABEL);

	__ASSERT(dev != NULL, "Failed to get device binding");

	printk("Dev %p name %s is ready!\n", dev, dev->config->name);

	struct sensor_value temp, humidity;

	while (1) {
		/* take a sample */
		printk("Fetching...\n");
		sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);

		/* print the result */
		printk("Temp = %d.%06d C, RH = %d.%06d %%\n",
		       temp.val1, temp.val2, humidity.val1, humidity.val2);

		/* wait for the next sample */
		k_sleep(K_SECONDS(10));
	}
}
