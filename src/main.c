#include <msp430.h>
#include "jdy33.h"

void main(void) {
    // Stop the Watchdog Timer
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= BIT0;      // Configure P1.0 as output (LED) 
    P1OUT &= ~BIT0;     // Turn off the LED

    jdy33_init(9600);   // Initialize the JDY33 at 9600 baud
    
    jdy33_set_name("TEST_MSP430"); // Set the Bluetooth Classic name
    jdy33_reset(); // Reset the JDY33 module

    __bis_SR_register(GIE); // Enable GIE for the UART interrupts

    // Send a message string via Bluetooth
    jdy33_send_string("\r\n--- JDY-33 Library Test ---\r\n");
    jdy33_send_string("Send 'H' to Turn ON LED, 'L' to Turn OFF\r\n");

    while(1) {
        // BLUETOOTH DATA RECEPTION (RX)
        if (jdy33_available()) { // Has JDY33 received Bluetooth data?
            uint8_t rx_data = jdy33_read_byte(); // Read received byte 

            // Turn on the LED if the received data is 'H' or 'h'
            if (rx_data == 'H' || rx_data == 'h') {
                P1OUT |= BIT0; 
                jdy33_send_string(">> LED is ON\r\n");
            } 
            // Turn of the LED if the received data is 'L' or 'l'
            else if (rx_data == 'L' || rx_data == 'l') {
                P1OUT &= ~BIT0; 
                jdy33_send_string(">> LED is OFF\r\n");
            }
            // Echo the received data
            else {
                jdy33_send_string("Received: ");
                jdy33_send_byte(rx_data);
                jdy33_send_string("\r\n");
            }
        }

        // SEND BLUETOOTH DATA EVERY 1-2 SECONDS BASED ON BLOCK
        static uint16_t loop_count = 0;
        if (++loop_count > 50000) { 
             jdy33_send_string("Waiting for command...\r\n");
             loop_count = 0;
        }
        
        __delay_cycles(100); // reduce CPU load
    }
}