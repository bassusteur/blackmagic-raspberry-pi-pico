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

#ifndef PLATFORMS_RP2040_MULTICORE_H
#define PLATFORMS_RP2040_MULTICORE_H

#include "platform.h"
#include "general.h"
#include "pico/util/queue.h"

char READBUF[1024U];
char WRITEBUF;

queue_t wqueue;
queue_t rqueue;

void multicore_init(void);

#endif