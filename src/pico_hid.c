#include "pico_hid.h"

#define RANGE (INT8_MAX - INT8_MIN + 1)


void send_hid_report(void)
{  
  if (!tud_hid_ready()) return;

  hid_gamepad_report_t report =
  {
    .x   = 0,
    .y = 0,
    .z = 0,
    .rz = 0,
    .rx = 0,
    .ry = 0,
    .hat = 0,
    .buttons = 0
  };



  //int8_t value = (adc_read() / 256) - 128;
  adc_select_input(1);
  float raw_value = (float)adc_read();
  static float max0, min0;
  if (raw_value > max0) max0 = raw_value;
  if (raw_value < min0) min0 = raw_value;
  raw_value = ((raw_value - min0) / (max0 - min0) - 0.5f) * 2.0f;
  report.y = (int8_t)(raw_value * 127);
  
  adc_select_input(0);
  raw_value = (float)adc_read();
  static float max1, min1;
  if (raw_value > max1) max1 = raw_value;
  if (raw_value < min1) min1 = raw_value;
  raw_value = ((raw_value - min1) / (max1 - min1) - 0.5f) * 2.0f;
  report.x = (int8_t)(raw_value * 127);
  // int8_t v1 = raw_value;
  // int8_t v2 = raw_value >> 8; //board_button_read() > 0 ? -1 : 1;

  // report.x = v1;
  // report.y = v2;

  tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));

  //tud_hid_report(1, gamepad_report, sizeof(gamepad_report));
}

// Every 10ms, we will sent 1 repor
void hid_task(void)
{
  // Poll every 10ms
  const uint32_t interval_ms = 10;
  static uint32_t start_ms = 0;


  if (board_millis() - start_ms < interval_ms) return; // not enough time
  start_ms += interval_ms;

  if (tud_suspended())
  {
    tud_remote_wakeup();
  }
  else
  {
    send_hid_report();
  }
}


//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = tud_mounted() ? BLINK_MOUNTED : BLINK_NOT_MOUNTED;
}

//--------------------------------------------------------------------+
// Unimplemented device callbacks
//--------------------------------------------------------------------+

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) instance;
  (void) len;
  (void) report;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) bufsize;  
}