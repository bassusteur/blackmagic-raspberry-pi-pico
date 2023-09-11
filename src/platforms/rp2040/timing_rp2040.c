/*
 * This file is part of the Black Magic Debug project.
 *
 * Written by Treble <bassusteur@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "general.h"
#include "platform.h"
#include "morse.h"

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/clocks.h"

bool running_status = false;
static volatile uint32_t time_ms = 0;
uint32_t target_clk_divider = 0;

static size_t morse_tick = 0;

static volatile bool alarm_fired;

#define ALARM_NUM 0
#define ALARM_IRQ TIMER_IRQ_0

static void alarm_irq(void) {
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);
    alarm_fired = true;
}

void platform_timing_init(void)
{
    // enable interrupt for the alarm
    hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM);
    // set irq handler for the alarm irq
    irq_set_exclusive_handler(ALARM_IRQ, alarm_irq);
    // enable the alarm irq
    irq_set_enabled(ALARM_IRQ, true);
    // prepare data to to write to the alarm register
    uint64_t target = timer_hw->timerawl + SYSTICKHZ;
    // arm the alarm writing target to the register
    timer_hw->alarm[ALARM_NUM] = (uint32_t) target;
}

void platform_delay(uint32_t ms)
{
	platform_timeout_s timeout;
	platform_timeout_set(&timeout, ms);
	while (!platform_timeout_is_expired(&timeout))
		continue;
}

uint32_t platform_time_ms(void)
{
	return time_ms;
}

uint32_t platform_max_frequency_get(void)
{
    return 125000000U;
}

void platform_max_frequency_set(const uint32_t frequency)
{
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
                    frequency/1000000 * MHZ,
                    frequency/1000000 * MHZ);
}

