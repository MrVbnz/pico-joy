// STD
#include "stdlib.h"
#include "stdio.h"
// TinyUSB
#include "bsp/board_api.h"
#include "tusb.h"
// TinyUSB custom descriptors
#include "usb_descriptors.h"
// GPIO
#include "hardware/gpio.h"
// #include "hardware/adc.h"

// #include "blinker.h"
// #include "pico_hid.h"

void main(void) 
{
  board_init();

  adc_init();
  adc_gpio_init(26);
  adc_select_input(0);

  // init device stack on configured roothub port
  tud_init(BOARD_TUD_RHPORT);

  if (board_init_after_tusb) 
  {
    board_init_after_tusb();
  }

  while (1)
  {
    tud_task();
    led_blinking_task();
    // input_handling_task();
    hid_task();
  }
}

// void input_handling_task() {
//     gamepad_report.x = adc_read();
// }