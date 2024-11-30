#include "LCD.h"


void LCD_initialize(void){
    EN_PIN = 0;
    __delay_ms(100);    //wait 100ms
    //THERE IS SOMETHING THAT NEEDS TO BE INIT FOR DELAY

    //Powerup routine

    //LATC = FUNCTION_SET
    LCD_SendCommand(FUNCTION_SET); //00001100
    //First bit, 0 is position blink char at the cursor is off
    //Second bit, 0 is Cursor OFF
    //Third bit, 1 is Display ON
    //4-8th bits, 00001 is Command: Display on/off control

    __delay_ms(4); //wait 1ms

    LCD_SendCommand(DISPLAY_ON); //00111000
    //Third bit, 0 is use 5x7 char
    //fourth bit, 1 is use two lines
    //fifth bit, 1 is 8 bit data width
    //6-8th bits, 001 is command function set

    

    

    __delay_ms(5);  //wait 1 ms
    LCD_ClearDisplay();
    return;

}

void LCD_SendCommand(uint8_t cmd){
    RS_PIN = 0; //READ SET on
    RW_PIN = 0; //WRITE

    //PUT DATA on DB7 to DB0
    LATC = cmd;
//    LCD1 = cmd & 1; //bitwise, selects the n bit of the command, to send
//    LCD2 = cmd & 2;
//    LCD3 = cmd & 3;
//    LCD4 = cmd & 4;
//    LCD5 = cmd & 5;
//    LCD6 = cmd & 6;
//    LCD7 = cmd & 7;
//    LCD8 = cmd & 8;
    //LATC = cmd;

    EN_PIN = 1; //ENABLE
    __delay_ms(1); //Wait 1 ms
    EN_PIN = 0;
    //Address increments automatically
    return;

}

uint8_t position = 0x0;
void LCD_SendCharacter(uint8_t ch){
    //LCD_SendCommand(position);
    RS_PIN = 1;
    RW_PIN = 0;

    LATC = ch;
    EN_PIN = 1;
    __delay_ms(1);
    EN_PIN = 0;
    position++;
    if (position == 0x0F+1){
        position = 0x40;    //move to next line
        LCD_SendCommand(128+position);
    }
    if (position == (0x4F+1)){
        position = 0x0;     //reset to first line
        LCD_SendCommand(128+position);
    }
//    position++;
//    if (position == 0x4F){
//        position = 0b10000000;
//    }
}

//// this a matrix of 37 x 8
//// This holds the values to send to the LCD and have it recognize the character
//uint8_t const static Characters [38] = {
//        {48},//0
//        {49},//1
//        {50},//2,
//        {51},//3
//        {52},//4
//        {53},//5
//        {54},//6
//        {55},//7
//        {56},//8
//        {57},//9
//        {65},//A   (10)
//        {66},//B
//        {67},//C
//        {68},//D
//        {69},//E
//        {70},//F   (15)
//        {71},//G
//        {72},//H
//        {73},//I
//        {74},//J
//        {75},//K   (20)
//        {76},//L
//        {77},//M
//        {78},//N
//        {79},//O
//        {80},//P   (25)
//        {81},//Q
//        {82},//R
//        {83},//S
//        {84},//T
//        {85},//U   (30)
//        {86},//V
//        {87},//W
//        {88},//X
//        {89},//Y
//        {90},//Z   (35)
//        {58},//:
//        {32}//SPACE
//};

//COPY OF BIT VALUES FOR CHARACTERS
//uint8_t const static Characters [37][8] = {
//        {0,0,1,1,0,0,0,0},//0
//        {0,0,1,1,0,0,0,1},//1
//        {0,0,1,1,0,0,1,0},//2,
//        {0,0,1,1,0,0,1,1},//3
//        {0,0,1,1,0,1,0,0},//4
//        {0,0,1,1,0,1,0,1},//5
//        {0,0,1,1,0,1,1,1},//6
//        {0,0,1,1,1,0,0,0},//7
//        {0,0,1,1,1,0,0,1},//8
//        {0,0,1,1,1,0,1,0},//9
//        {0,1,0,0,0,0,0,1},//A   (10)
//        {0,1,0,0,0,0,1,0},//B
//        {0,1,0,0,0,0,1,1},//C
//        {0,1,0,0,0,1,0,0},//D
//        {0,1,0,0,0,1,0,1},//E
//        {0,1,0,0,0,1,1,0},//F   (15)
//        {0,1,0,0,0,1,1,1},//G
//        {0,1,0,0,1,0,0,0},//H
//        {0,1,0,0,1,0,0,1},//I
//        {0,1,0,0,1,0,1,0},//J
//        {0,1,0,0,1,0,1,1},//K   (20)
//        {0,1,0,0,1,1,0,0},//L
//        {0,1,0,0,1,1,0,1},//M
//        {0,1,0,0,1,1,1,0},//N
//        {0,1,0,0,1,1,1,1},//O
//        {0,1,0,1,0,0,0,0},//P   (25)
//        {0,1,0,1,0,0,0,1},//Q
//        {0,1,0,1,0,0,1,0},//R
//        {0,1,0,1,0,0,1,1},//S
//        {0,1,0,1,0,1,0,0},//T
//        {0,1,0,1,0,1,0,1},//U   (30)
//        {0,1,0,1,0,1,1,0},//V
//        {0,1,0,1,0,1,1,1},//W
//        {0,1,0,1,1,0,0,0},//X
//        {0,1,0,1,1,0,0,1},//Y
//        {0,1,0,1,1,0,1,0},//Z   (35)
//        {0,0,1,1,1,0,1,0},//:
//        {0,0,1,0,0,0,0,0},//SPACE
//};
//size is not inclusive. 1->8
void LCD_SendString(string_b8 x,uint8_t size){
    
    for (uint8_t i = 1; i <= size; i++){
        unsigned char temp = find(x,i); //saves the char here so it doesnt keep running to find it
        if ((temp >= 97) &&(temp <= 122)){
            LCD_SendCharacter(temp-32);   //lowercase, but we're sending uppercase 
        }
        else{
            LCD_SendCharacter(temp);
        }
    }
    return;
}

void LCD_ClearDisplay(void){
    LCD_SendCommand(CLEAR_DISPLAY);
    return;
}

void LCD_NextLine(void){
    position = 0b1000000;
    position = position +  16;
    return;
}

void LCD_SendPhrase(char str[], uint8_t size){
    string_b8 temp = new_string(str,size);  //creates 8 bit string
    LCD_SendString(temp,size);  //Sends string
}

void LCD_SendHalfBlank(void){
    string_b8 temp = set_at_range(temp, 1,8,32);   //fill string with " "
    LCD_SendString(temp,8); //Send
}

void LCD_SendFullBlank(void){
    LCD_SendHalfBlank();
    LCD_SendHalfBlank();
}