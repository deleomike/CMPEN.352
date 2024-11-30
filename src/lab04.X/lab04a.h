
//------------------------------------------------------------------------------
// File:          lab02.h
// Written By:    Mike DeLeo
// Modified By:   Morayo Ogunsina
// Date Created:  4 Feb 18
// Date Modified: 7 Feb 18
// Description:   Program to simulate rolling a die
// Compiler:	  XC8 v1.33
// Target:        PIC16F1709
// Schematic(s):  Drawing L01-11
//
// Revision History : none
//------------------------------------------------------------------------------

#include <xc.h>
#include <stdint.h>
#include <string.h>

#include "LCD.h"
#ifndef LAB04_H
#define LAB04_H

    // MCU Configuration Bits
    #pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
    #pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
    #pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
    #pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
    #pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
    #pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
    #pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
    #pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
    #pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)
    #pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
    #pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
    #pragma config ZCDDIS = ON      // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR)
    #pragma config PLLEN = OFF      // Phase Lock Loop enable (4x PLL is enabled by SPLLEN)
    #pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
    #pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
    #pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
    #pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)
//#pragma config T0CKI = 1;

    // Defines
    #define OK_ PORTAbits.RA2     // Start Button
    #define ROLL_  PORTAbits.RA4  // Stop button
    #define HOLD_ PORTAbits.RA5  // Reset button
    
    #define TIMER0_FLAG TMR0IF   //Interrupt flag for timer 0




    // Function Prototypes

    //------------------------------------------------------------------------------
    //Name: intialize(void)
    //Precondition: Nothing
    //Postcondition: Nothing
    //Function: calls reset(), sets ANSELS, Slew Rate and tri states
    //------------------------------------------------------------------------------
    void MCU_initialize(void);

    //------------------------------------------------------------------------------
    //Name: reset()
    //Precondition: Nothing
    //Postcondition: Nothing
    //Function: sets all LEDS to 0
    //------------------------------------------------------------------------------
    void reset(void);

    //------------------------------------------------------------------------------
    //Name: reset()
    //Precondition: Current dievalue (int 8)
    //Postcondition: Nothing
    //Function: Sets all of the LEDS to the pattern for the current die value
    //------------------------------------------------------------------------------
   

    void Timer0Handler(void);

    void interrupt ISR(void);

    //Precondition: nothing
    //Postcondition: gives a "random" number. counts up from the timer 0 handler
    uint8_t Random();

    //Precondition: nothing
    //Postcondition: prints out player 1 or player 2
    void LCD_ShowTurn();

typedef enum {
    TITLE_SCREEN,
    SHOW_SCORE,
    INDICATE_TURN,
    ROLL_PROMPT,
    ROLLING_GRAPHIC,
    GET_ROLL,
    LOSE_TURN,
    ADD_ROLL,
    SHOW_TURN_TOTAL,
    SHOW_WINNER,
    ADD_TURN_TOTAL,
    CHANGE_PLAYER,
    RESET,
}GAMESTATE_type;  //STATE MACHINE

#endif /*LAB04_H*/
