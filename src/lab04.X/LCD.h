/* 
 * File:   LCD.h
 * Author: MAD6068
 *
 * Created on February 7, 2018, 7:31 PM
 */


#include "string.h"
#include <xc.h>
#include <stdint.h>
#ifndef LCD_H
#define LCD_H

#define CLEAR_DISPLAY 0b00000001
#define DISPLAY_ON   0b00001100   //12    //Blink char at curs off, cursor off, display on
#define FUNCTION_SET  0b00111000  //56   //uses 5x7 char, 2 lines, and 8 bit data width
#define RS_PIN PORTBbits.RB4 //1 is read/set, 0 is do not
#define RW_PIN PORTBbits.RB5 //1 is read, 0 is write
#define EN_PIN PORTBbits.RB6 //Enable pin, 0 is off, 1 is on
//RS 4
//rw 5
//en 6

//#define LCD1 PORTCbits.RC0  // Segment A
//#define LCD2 PORTCbits.RC1  // Segment B
//#define LCD3 PORTCbits.RC2  // Segment C
//#define LCD4 PORTCbits.RC3  // Segment D
//#define LCD5 PORTCbits.RC4  // Segment E
//#define LCD6 PORTCbits.RC5  // segment F
//#define LCD7 PORTCbits.RC6  // segment G
//#define LCD8 PORTCbits.RC7  //LED Turns on when RC7 is 0
#define LCD1 PORTCbits.RC0  // Segment A
#define LCD2 PORTCbits.RC1  // Segment B
#define LCD3 PORTCbits.RC2  // Segment C
#define LCD4 PORTCbits.RC3  // Segment D
#define LCD5 PORTCbits.RC4  // Segment E
#define LCD6 PORTCbits.RC5  // segment F
#define LCD7 PORTCbits.RC6  // segment G
#define LCD8 PORTCbits.RC7  //LED Turns on when RC7 is 0

#define _XTAL_FREQ 32000000

//Precondition: nothing
//Postcondition: intializes LCD
void LCD_Initialize(void);

//Precondition: 8 bit command, int or bits
//Postcondition: sends command to LCd
void LCD_SendCommand(uint8_t cmd);

//Precondition: 8 bit string, and size of string
//Postcondition: sends string, character by character to LCD using send character
void LCD_SendString(string_b8 x, uint8_t size);

//Precondition: nothing
//Postcondition: sends a command to clear the display
void LCD_ClearDisplay(void);

//Precondition: int version of character
//Postcondition: sends character to LCD
void LCD_SendCharacter(uint8_t ch);

//Precondition: nothing
//Postcondition: sets current position to next line (NOT USED)
void LCD_NextLine(void);

//Precondition: easier way to use 8 bit string. send a char array and size
//Postcondition: sends string through send character
void LCD_SendPhrase(char str[], uint8_t size);

//Precondition: nothing
//Postcondition: sends 8 bits of blank characters
void LCD_SendHalfBlank(void);

//Precondition: nothing
//Postcondition: calls send half blank twice
void LCD_SendFullBlank(void);



#endif LCD_H
