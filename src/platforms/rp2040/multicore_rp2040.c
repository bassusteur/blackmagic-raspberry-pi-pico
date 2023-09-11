/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2022 1BitSquared <info@1bitsquared.com>
 * Written by Rachel Mant <git@dragonmux.network>
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

  if(tud_cdc_connected())
  {
    uint32_t count = tud_cdc_read(READBUF, sizeof(READBUF));
    for(int i=0; i<count; i++)
    {
      queue_add_blocking(&rqueue, &READBUF[i]);
    }
  }

  if(tud_cdc_connected())
    tud_cdc_write_flush();
}

void multicore_loop()
{
    //tusb_init();
    board_init();
    tud_init(BOARD_TUD_RHPORT);

    while(1)
    {
      tud_task();
      cdc_task();
    }
}

void multicore_init()
{
  queue_init(&wqueue, sizeof(char), 1);
  queue_init(&rqueue, sizeof(char), 1);

  multicore_launch_core1(multicore_loop);
}