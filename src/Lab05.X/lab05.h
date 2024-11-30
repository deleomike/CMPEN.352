
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


//------------------------------------------------------------------------------
// File:          lab05.h
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
#ifndef LAB05_H
#define    LAB05_H
// PIC32MX340F512H Configuration Bit Settings
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider(PLL Divide by 1)
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits(Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable(Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over(Disabled)
#pragma config POSCMOD = HS             // Primary OscillatorConfiguration (HS osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active othe OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor(Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and MonitorSelection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler(1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDTDisabled (SWDTEN Bit Controls))
#pragma config DEBUG = OFF              // Background Debugger Enable(Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select(ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect(Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit(Protection Disabled)








#define _SUPPRESS_PLIB_WARNING
#include <plib.h>

#pragma config CP = OFF                 // Code Protect (ProtectionDisabled)
// Includes
#include <xc.h>
#include <stdint.h>
// Defines
#define TRIS_OUTPUT 0  // Used to set tristate to output
#define TRIS_INPUT 1   // Used to set tristate to input
#define LD5_OUT PORTFbits.RF0      // LED pin value
#define LD5_TRIS TRISFbits.TRISF0  // LED pin tristate
#define DELAY 20000
// Function prototypes
void MCU_initialize(void);
void _mon_putc (char c);
#endif     /* LAB05_H */
