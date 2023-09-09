/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2011  Black Sphere Technologies Ltd.
 * Written by Gareth McMullin <gareth@blacksphere.co.nz>
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
#include "gdb_if.h"
#include "usb_serial.h"

static uint32_t count_out;
static uint32_t count_in;
static uint32_t out_ptr;
static char buffer_out[CDCACM_PACKET_SIZE];  // DEFINE CDCACM_PACKET_SIZE LATER IN TINY USB CONFIG
static char buffer_in[CDCACM_PACKET_SIZE];


void gdb_if_putchar(const char c, const int flush)
{
    /*
    buffer_in[count_in++] = c;
    if (flush || count_in == CDCACM_PACKET_SIZE)
    {
        while()
            continue;
    }
    */
}

char gdb_if_getchar(void)
{
    return "B";
}

char gdb_if_getchar_to(uint32_t timeout)
{
    return "B";
}
