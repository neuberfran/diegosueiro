// Copyright 2015-2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdint.h>
#include <sys/param.h>

#include "esp_attr.h"
#include "esp32s3/clk.h"
#include "soc/rtc.h"

// g_ticks_us defined in ROMs for PRO and APP CPU
extern uint32_t g_ticks_per_us_pro;

int IRAM_ATTR esp_clk_cpu_freq(void)
{
    return MHZ(g_ticks_per_us_pro);
}

int IRAM_ATTR esp_clk_apb_freq(void)
{
    return MHZ(MIN(g_ticks_per_us_pro, 80));
}

int IRAM_ATTR esp_clk_xtal_freq(void)
{
    return MHZ(rtc_clk_xtal_freq_get());
}

void IRAM_ATTR ets_update_cpu_frequency(uint32_t ticks_per_us)
{
    /* Update scale factors used by esp_rom_delay_us */
    g_ticks_per_us_pro = ticks_per_us;
}
