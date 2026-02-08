#include <msp430.h>
#include "uart.h"

// UART receive buffer, max 64 bytes
#define RX_BUFFER_SIZE 64
volatile uint8_t rx_buffer[RX_BUFFER_SIZE];

volatile uint8_t rx_head = 0; // RX buffer writre index (ISR)
volatile uint8_t rx_tail = 0; // RX buffer read index

// UART INITIALIZE
void uart_init(uint32_t baudrate)
{
    // Set DCO = 8MHz 
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL  = CALDCO_8MHZ;

    // UART pin: P1.1 RX, P1.2 TX 
    P1SEL  |= BIT1 | BIT2;
    P1SEL2 |= BIT1 | BIT2;

    UCA0CTL1 |= UCSWRST; // Hold USCI in reset 
    UCA0CTL1 |= UCSSEL_2; // Select SMCLK 

    // Baudrate config 
    switch (baudrate)
    {
        case 9600:         
            UCA0BR0  = 833 & 0xFF;
            UCA0BR1  = 833 >> 8;
            UCA0MCTL = UCBRS2;
            break;

        case 19200:
            UCA0BR0  = 416 & 0xFF;
            UCA0BR1  = 416 >> 8;
            UCA0MCTL = UCBRS2;
            break;

        case 38400:
            UCA0BR0  = 208;
            UCA0BR1  = 0;
            UCA0MCTL = UCBRS2;
            break;

        case 57600:
            UCA0BR0  = 138;
            UCA0BR1  = 0;
            UCA0MCTL = UCBRS2;
            break;

        case 115200:       
            UCA0BR0  = 69;
            UCA0BR1  = 0;
            UCA0MCTL = UCBRS2 | UCBRS1;
            break;

        default:           
            UCA0BR0  = 833 & 0xFF;
            UCA0BR1  = 833 >> 8;
            UCA0MCTL = UCBRS2;
            break;
    }

    UCA0CTL1 &= ~UCSWRST; // Release reset USCI 
    IE2 |= UCA0RXIE; // Enable RX interrupt
}

// SEND BYTE VIA UART
void uart_send_byte(uint8_t data)
{
    while (!(IFG2 & UCA0TXIFG)); // Wait until UART TX buffer is ready
    UCA0TXBUF = data; // Send one byte
}

// SEND A STRING VIA UART
void uart_send_string(const char *str)
{
    // Send a string byte by byte
    while (*str)
    {
        uart_send_byte(*str++);
    }
}

// CHECK FOR RECEIVED DATA
uint8_t uart_available(void)
{
    uint8_t h = rx_head; 
    uint8_t t = rx_tail; 
    return (uint8_t)(h != t); 
}

// READ ONE BYTE FROM UART RX BUFFER
uint8_t uart_read_byte(void)
{
    uint8_t data = 0;
    uint8_t h, t;

    // Save the current interrupt state and disable interrupts
    uint16_t gie_state = __get_SR_register() & GIE;
    __disable_interrupt(); 

    h = rx_head; // Snapshot of RX head index
    t = rx_tail; // snapshot of RX tail index

    if (h != t) // If the RX buffer is not emty
    {
        // Read data and advance tail index
        data = rx_buffer[t];
        t = (uint8_t)((t + 1) % RX_BUFFER_SIZE);
        rx_tail = t;
    }

    // Restore the initial interrupt state
    if(gie_state) __enable_interrupt();

    return data;
}

// UART RX ISR: TRIGGERED ON EACH RECEIVED BYTE
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    uint8_t h = rx_head; // Snapshot of RX head index
    uint8_t t = rx_tail; // Snapshot of RX tail index
    uint8_t next = (uint8_t)((h + 1) % RX_BUFFER_SIZE); // Nest head position

    if (next != t) // If the RX buffer is not full   
    {
        // Write received byte to buffer and update RX head index
        rx_buffer[h] = UCA0RXBUF; 
        rx_head = next; 
    }
}