/* 
 * File:   lab05.c
 * Author: MAD6068
 *
 * Created on February 14, 2018, 6:44 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

//------------------------------------------------------------------------

// File:          lab05.c
// Written By:    E.G. Walters
// Date Created:  20 Jan 15
// Description:   First program to work with PIC32 on Uno32 board
// Compiler:       XC32 v1.34
// Target:        PIC32MX340F512H
// Schematic(s):  Drawing L05-01
//
// Revision History (date, initials, description)
//   9 Sep 15, egw100, Updated for EE 316 FA 15
//   24 Jan 17, egw100, Updated for CMPEN 352W SP 17
//   13 Feb 18, egw100, Updated for CMPEN 352W SP 18
//------------------------------------------------------------------------------
#include "lab05.h"

uint8_t seconds = 0;
uint8_t minutes = 0;
uint32_t mscount =  0;
//------------------------------------------------------------------------------
// Function: main()
//------------------------------------------------------------------------------
void main(void) {
MCU_initialize();
uint32_t i;  // loop index
uint32_t loopcount = 0; // number of times main loop has executed
uint8_t ascii = 0;
while(1) {
// Toggle LD5
    
    // Delay
    for (ascii = 'A'; ascii <= 'Z'; ascii++)
    {
        printf("%c", ascii);
        for (i = 0; i < DELAY; i++)
        {// do nothing
        }
    }
    printf("\n");
       
}

} // end main()


//------------------------------------------------------------------------------
// Function: MCU_initialize()
// Params:   void
// Returns:  void
// Initialization code for the application
//------------------------------------------------------------------------------
void MCU_initialize(void) {
// Use multi-vector interrupt mode
INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
// Configure oscillators
OSCCONbits.PBDIV = 0b11;  // PBCLK is SYSCLK/8 = 10 MHz
// Init UART 1 to communicate with PC
U1MODEbits.UEN = 0b00;
U1MODEbits.PDSEL = 0b00;  // 8-bit data, no parity
U1MODEbits.STSEL = 0;  // 1 stop bit
U1BRG = 64;  // PBCLK = 10 MHz so Baud rate = 9600
U1STAbits.UTXEN = 1;
U1STAbits.URXEN = 1;
U1MODEbits.ON = 1;  // Turn on UART
printf("\n\n---------------\nUART Configured\n  Hello TTY!\n---------------\n");

// Configure Timer1 to interrupt every 1 ms
T1CON = 0x00; // Disable timer, prescale = 1:1, source = PBCLK
TMR1 = 0;     // Clear timer count
PR1 = 10000;  // PBCLK is 10 MHz, so 10 000 counts = 1 kHz
IPC1bits.T1IP = 7; // Interrupt priority = 7 (highest priority)
IPC1bits.T1IS = 3; // Subpriority = 3 (highest)
IFS0bits.T1IF = 0; // Clear interrupt flag
IEC0bits.T1IE = 1; // Enable interrupt
T1CONbits.ON = 1;  // Enable timer
// Configure tristates
LD5_TRIS = TRIS_OUTPUT; // Set pin to output

// Enable global interrupts
INTEnableInterrupts();
} // end MCU_initialize()


//------------------------------------------------------------------------------
// Function: _mon_putc()
// Params:   c; character to send to stdout
// Returns:  void
// Redfine _mon_putc so stdout goes to UART
//------------------------------------------------------------------------------
void _mon_putc (char c) {

while(U1STAbits.UTXBF);  // wait for transmit buffer to be available
    U1TXREG = c;
} // end _mon_putc()

//------------------------------------------------------------------------------
// Function: Timer1Handler()
// Params:   void
// Returns:  void
// Interrupt handler for Timer 1
//------------------------------------------------------------------------------
//double first_samp = 0;
//double second_samp = 0;
void __ISR(_TIMER_1_VECTOR, IPL7SOFT) Timer1Handler(void) {
    // Clear interrupt flag
    IFS0bits.T1IF = 0;
    TMR1 = 0;
//    if (first_samp = 0){
//        first_samp = TMR1;
//    }
//    else if (second_samp = 0){
//        second_samp = TMR1;
//    }
//    else{
//        double temp =1 / (first_samp - second_samp);
//        printf(" %F ",temp);
//        first_samp = 0;
//        second_samp =0;
//    }
//LD5_OUT = ~LD5_OUT;
    mscount++;
    if (mscount == 1000){
        mscount = 0;
        seconds++;
        printf(" <%02d:%02d> ", minutes, seconds);
        LD5_OUT = ~LD5_OUT;
    }
    if (seconds == 60){
        seconds = 0;
        minutes++;
    }
//     if (time[4] == 10)//least significant bit sets to zero, increment next
//    {
//        time[3]++;
//        time[4] = 0;
//    }
//    else if (time[3] == 5){    //rollover
//        time[3] = 0;
//        time[2]++;
//
//    }
//    else if (time[2] == 60){    //rollover
//        time[2] = 0;
//        time[1]++;
//
//    }
//    else if (time[1] == 250){     //rollover
//        time[1] = 0;
//
//    }
    
    
    // Add your code here to keep track of minutes and seconds
   //blink the LD5 LED and send the minutes and seconds to the
    // terminal every second//
    
}
// end Timer1Handler()

