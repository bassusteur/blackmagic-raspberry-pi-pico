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

#include "platform.h"
#include "general.h"
#include "usb.h"

void platform_init(void)
{
    gpio_init(TDI_PIN);
    gpio_init(TMS_PIN);
    gpio_init(TCK_PIN);
    gpio_init(TDO_PIN);
    gpio_init(LED_PIN);
    gpio_init(NRST_PIN);

    // set JTAG pin directions
    gpio_set_dir(TDI_PIN, GPIO_IN);
    gpio_set_dir(TMS_PIN, GPIO_IN);
    gpio_set_dir(TCK_PIN, GPIO_IN);
    gpio_set_dir(TDO_PIN, GPIO_OUT);

    // set led pin direction
    gpio_set_dir(LED_PIN, GPIO_OUT);
    // set nrst pin direction
    gpio_set_dir(NRST_PIN, GPIO_OUT);
    // init our timer
    platform_timing_init();
    blackmagic_usb_init();
}

void platform_nrst_set_val(bool assert)
{
    gpio_set_val(NRST_PIN, !assert);
}

bool platform_nrst_get_val(void)
{
    return (gpio_get(NRST_PIN)) ? false : true;
}

const char *platform_target_voltage(void)
{
	return "ABSENT!";
}

void platform_request_boot(void){}

int platform_hwversion(void)
{
	return 0;
}

void platform_target_clk_output_enable(bool enable)
{
	(void)enable;
}

bool platform_spi_init(const spi_bus_e bus)
{
	(void)bus;
	return false;
}

bool platform_spi_deinit(const spi_bus_e bus)
{
	(void)bus;
	return false;
}

bool platform_spi_chip_select(const uint8_t device_select)
{
	(void)device_select;
	return false;
}

uint8_t platform_spi_xfer(const spi_bus_e bus, const uint8_t value)
{
	(void)bus;
	return value;
}

void set_idle_state(int state)
{
    
}