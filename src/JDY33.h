#ifndef JDY33_H_
#define JDY33_H_

#include "uart.h"

// Define the role for the module
typedef enum {
    JDY33_SLAVE  = 0,
    JDY33_MASTER = 1
} JDY33_ROLE;

void jdy33_init(uint32_t target_baudrate); // Force initialization
void jdy33_set_name(const char *name); // Configure the module name
void jdy33_set_role(JDY33_ROLE role); // Set the module role
void jdy33_reset(void); // Reset the module

void jdy33_send_byte(uint8_t data); // Send one byte via Bluetooth
void jdy33_send_string(const char *str); // Send string via Bluetooth
uint8_t jdy33_available(void); // Check received Bluetooth data
uint8_t jdy33_read_byte(void); // Read one received byte 

#endif /* JDY33_H_ */