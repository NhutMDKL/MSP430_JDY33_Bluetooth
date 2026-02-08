#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init(uint32_t baudrate);      // UART Initialize
void uart_send_byte(uint8_t data);      // Send byte via UART
void uart_send_string(const char *str); // Send a string via UART
uint8_t uart_available(void);           // Check for received data
uint8_t uart_read_byte(void);           // Read one byte from UART RX buffer

#endif /* UART_H_ */
