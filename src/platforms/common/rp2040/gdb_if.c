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
#include "gdb_if.h"
#include "usb_serial.h"

extern queue_t wqueue;
extern queue_t rqueue;

void gdb_if_putchar(const char c, const int flush)
{
    queue_add_blocking(&wqueue, &c);
}

char gdb_if_getchar(void)
{
    char c;
    queue_remove_blocking(&rqueue, &c);
    return c;
}

char gdb_if_getchar_to(uint32_t timeout)
{
    char c;
    queue_remove_blocking(&rqueue, &c);
    return c;
}
