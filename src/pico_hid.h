#ifndef PICO_HID_H
#define PICO_HID_H

#include "stdint.h"
#include "hardware/adc.h"

#include "hid.h"
#include "blinker.h"
#include "usb_descriptors.h"

static hid_gamepad_report_t* gamepad_report;

void hid_task(void);

void send_hid_report();

// Device callbacks
void tud_mount_cb(void);
void tud_umount_cb(void);
void tud_suspend_cb(bool remote_wakeup_en);
void tud_resume_cb(void);

// Unimplemented device callbacks
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len);
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

#endif