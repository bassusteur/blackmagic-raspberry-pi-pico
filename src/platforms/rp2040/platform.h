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

/* This file provides the platform specific declarations for the Raspberry PI foundation RP2040 implementation. */

#ifndef PLATFORMS_RP2040_PLATFORM_H
#define PLATFORMS_RP2040_PLATFORM_H

#include "timing_rp2040.h"
#include "timing.h"
#include "gpio.h"
#include "multicore_rp2040.h"

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include <string.h>

#define PLATFORM_IDENT "(RP2040) "
#define RP2040 1
#define NO_LIBOPENCM3

#define TDI_PIN   1
#define TMS_PIN   2
#define TCK_PIN   4
#define TDO_PIN   3
#define TRST_PIN  5
#define JTAG_PORT[5] = {TDI_PIN,TMS_PIN,TCK_PIN,TDO_PIN,TRST_PIN};

#define SWDIO_PIN  2
#define SWCLK_PIN  4
#define SWDIO_PORT[2] = {SWDIO_PIN,SWCLK_PIN};

#define NRST_PIN  5

#define LED_PIN  25

#define TMS_SET_MODE() gpio_set_dir(TMS_PIN, GPIO_OUT);

#define SWDIO_MODE_FLOAT() \
	for(int i=0; i<1; i++) {                        \
        gpio_init(SWDIO_PORT[i]);                   \
        gpio_set_pulls(SWDIO_PORT[i], 0, 0);        \
	}

#define SWDIO_MODE_DRIVE()                         \
	do {                                           \
	}

extern void set_idle_state(int state);
#define SET_RUN_STATE(state)                         \
	{                                                \
		gpio_set_val(LED_PIN, state); \
		running_status = (state);                    \
	}
#define SET_IDLE_STATE(state)                         \
	{                                                 \
		gpio_set_val(LED_PIN, !state); \
	}
#define SET_ERROR_STATE(state)

#endif /* PLATFORMS_RP2040_PLATFORM_H */