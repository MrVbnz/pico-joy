#ifndef BLINKER_H
#define BLINKER_H

#include "bsp/board_api.h"

void led_blinking_task(void);

/* 
 * Blink pattern:
 * 250ms - device not mounted
 * 1000ms - device mounted
 * 2500ms - device is suspended
 */

enum {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

#endif