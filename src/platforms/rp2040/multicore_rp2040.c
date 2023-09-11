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

#include "multicore_rp2040.h"

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
static void cdc_task(void)
{
  while(!queue_is_empty(&wqueue))
  {
    queue_remove_blocking(&wqueue, &WRITEBUF);
    if(tud_cdc_connected())
      tud_cdc_write_char(WRITEBUF);
  }

  while (tud_cdc_connected() && tud_cdc_available())
  {
    tud_cdc_read(&READBUF, 1);
    queue_add_blocking(&rqueue, &READBUF);
  }

  if(tud_cdc_connected())
    tud_cdc_write_flush();
}

void multicore_loop()
{
    //tusb_init();
    while(1)
    {
      tud_task();
      cdc_task();
    }
}

void multicore_init()
{
  board_init();
  //tud_init(BOARD_TUD_RHPORT);
  tusb_init();

  queue_init(&wqueue, sizeof(char), 64);
  queue_init(&rqueue, sizeof(char), 64);

  multicore_reset_core1();
	multicore_fifo_drain();
  multicore_launch_core1(multicore_loop);
}