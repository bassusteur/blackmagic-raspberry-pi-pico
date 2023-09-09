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

char WRITEBUF[32];
char READBUF[QUEUE_LENGTH];

static void echo_serial_port(uint8_t itf)
{
  //char buf[64] = "aaaabbbbcccc";
  for(int i; i<sizeof(WRITEBUF); i++)
  {
    if(WRITEBUF[i] == 0x00)
    {
      queue_remove_blocking(&wqueue, &WRITEBUF);
    }
    else
    {
    tud_cdc_n_write_char(itf, WRITEBUF[i]);
    }
    tud_cdc_n_write_flush(itf);
  }
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
static void cdc_task(void)
{
  uint8_t itf;

  for (itf = 0; itf < CFG_TUD_CDC; itf++)
  {
    // connected() check for DTR bit
    // Most but not all terminal client set this when making connection
    // if ( tud_cdc_n_connected(itf) )
    {
      if ( tud_cdc_n_available(itf) )
      {
        uint32_t buf;

        uint32_t count = tud_cdc_n_read(itf, buf, sizeof(buf));

        // echo back to both serial ports
        echo_serial_port(0);
      }
    }
  }
}

void multicore_loop()
{
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
  strcpy(WRITEBUF, "hello my name is");
  queue_init(&wqueue, sizeof(WRITEBUF), QUEUE_LENGTH);
  //queue_init(&rqueue, sizeof(READBUF), QUEUE_LENGTH);

  queue_add_blocking(&wqueue, &WRITEBUF);

  multicore_launch_core1(multicore_loop);
}