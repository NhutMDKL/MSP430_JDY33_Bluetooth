#include <msp430.h>
#include "JDY33.h"

// FORCE INITIALIZATION
void jdy33_init(uint32_t target_baudrate) {
    uint8_t baud_code = 0;
    // List of popular baund rates
    uint32_t scan_bauds[] = {115200, 9600, 38400, 19200, 57600};
    uint8_t i;

    // Identify baud_code corresponding to target_baudrate
    switch (target_baudrate) {
        case 9600:   baud_code = 4; break;
        case 19200:  baud_code = 5; break;
        case 38400:  baud_code = 6; break;
        case 57600:  baud_code = 7; break;
        case 115200: baud_code = 8; break;
        default:     target_baudrate = 9600; baud_code = 4; break; 
    }

    // Scan for a valid baud rate
    for (i = 0; i < 5; i++) {
        uart_init(scan_bauds[i]); // Initialize UART baud rate 
        __delay_cycles(80000); // Wait for stabilization
        
        // Send AT command to configure the UART baud rate
        uart_send_string("AT+BAUD");
        uart_send_byte(baud_code + '0');
        uart_send_string("\r\n");
        
        __delay_cycles(400000);   // Wait for stabilization
    }

    // Sync UART and JDY33 baud rates
    uart_init(target_baudrate);
    
    // Reset the JDY33 module
    jdy33_reset();
}

// Configure the name of the JDY33 module in Bluetooth Classic mode
void jdy33_set_name(const char *name) {
    uart_send_string("AT+NAME");
    uart_send_string(name);
    uart_send_string("\r\n");
    __delay_cycles(1600000); 
}

// Reset the JDY33 module 
void jdy33_reset(void) {
    uart_send_string("AT+RESET\r\n");
    __delay_cycles(8000000); 
}

// Set role for the JDY33 module
void jdy33_set_role(JDY33_ROLE role) {
    if (role == JDY33_MASTER) uart_send_string("AT+ROLE1\r\n");
    else uart_send_string("AT+ROLE0\r\n");
    __delay_cycles(1600000);
}

// Transmit one byte via Bluetooth 
void jdy33_send_byte(uint8_t data) {
    uart_send_byte(data);
}

// Transmit string via Bluetooth
void jdy33_send_string(const char *str) {
    uart_send_string(str);
}

// Check the received Bluetooth data
uint8_t jdy33_available(void) {
    return uart_available();
}

// Read one received byte
uint8_t jdy33_read_byte(void) {
    return uart_read_byte();
}