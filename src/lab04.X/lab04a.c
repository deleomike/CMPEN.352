
//------------------------------------------------------------------------------
// File:          lab03.c
// Written By:    Mike DeLeo, Morayo Ogunsina
// Modified By:   Mike DeLeo, Morayo Ogunsina
// Date Created:  4 Feb 18
// Date Modified: 7 Feb 18
// Description:   Program to simulate rolling a die
// Compiler:	  XC8 v1.33
// Target:        PIC16F1709
// Schematic(s):  Drawing L01-11
//
// Revision History (date, initials, description)
//  16 Jan 18, egw100, Initial version
//------------------------------------------------------------------------------

// Includes
#include "lab04a.h"



//uint8_t time[4] =     {5,4,3,2}; //Time as an array Digit 1, Digit 2, Digit 3, Digit 4, thousands place
//uint8_t sleep[2] =    {0,0};      //first is sleep, second counts to 250, then increments sleep[0]]
//uint8_t select = 4;            //selects relative to bit
//uint16_t count = 0;            //go up to half second
//uint8_t count_WALTERS = 0;
//uint8_t count_SLEEPY_WALTERS =0;
//uint8_t count_TIME = 0;

uint8_t Player_Turn = 1;    //1 for p1, 2 for p2
GAMESTATE_type state = TITLE_SCREEN;
uint8_t BUTTON[3] = {0,0,0};    //0 is ok, 1 is Roll, 2 is hold

uint8_t OK_ONS = 0;
uint8_t ROLL_ONS   = 0;
uint8_t HOLD_ONS =   0;
uint8_t OK_SAMPLE  = 0;
uint8_t ROLL_SAMPLE= 0;
uint8_t HOLD_SAMPLE =0;

uint8_t OK_DEBOUNCED  =  0;
uint8_t ROLL_DEBOUNCED = 0;
uint8_t HOLD_DEBOUNCED = 0;

uint8_t OK_DEBOUNCED_LC= 0;
uint8_t ROLL_DEBOUNCED_LC= 0;
uint8_t HOLD_DEBOUNCED_LC= 0;

uint8_t count = 1;

//------------------------------------------------------------------------------
// Function: main()
//------------------------------------------------------------------------------
void main(void) {

    MCU_initialize();   //set all the variables for LED, ANSEL,

    ei();   //Enable Global Interrupts
    
    uint8_t P1_Score = 123;
    uint8_t P2_Score = 0;
     uint8_t R_NUM = 0;;

     uint8_t P1_Turn = 0;
     uint8_t P2_Turn = 0;
    

    //If Stop is pressed, stop counting
    //If start is pressed, keep ounting
    //If reset is pressed, set to zero
    while(1) {

        
        OK_ONS = OK_DEBOUNCED & ~OK_DEBOUNCED_LC;
        OK_DEBOUNCED_LC = OK_DEBOUNCED;
        ROLL_ONS = ROLL_DEBOUNCED & ~ROLL_DEBOUNCED_LC;
        ROLL_DEBOUNCED_LC = ROLL_DEBOUNCED;
        HOLD_ONS = HOLD_DEBOUNCED & ~HOLD_DEBOUNCED_LC;
        HOLD_DEBOUNCED_LC = HOLD_DEBOUNCED;


        if (state == TITLE_SCREEN){
            P1_Score = 0;
            P2_Score = 0;
            LCD_SendPhrase("Welcome ", 8);
            LCD_SendPhrase("To Pig  ", 8);
            //LCD_SendFullBlank();    //Line extends to 32, this ends that
            //LCD_NextLine();
            LCD_SendPhrase("Press OK", 8);

            LCD_SendHalfBlank();
            //LCD_SendFullBlank();
            if (OK_ONS == 1){
                state = SHOW_SCORE; //OK has been pressed, go to SHOW SCORE
            }
        //__delay_ms(1000);
      //  LCD_ClearDisplay();
        }
        
        else if (state == SHOW_SCORE){
            LCD_SendPhrase("Player 1", 8);
            LCD_SendPhrase(" : ", 3);
            string_b8 temp = num2str(P1_Score,3);
            LCD_SendString(temp,3);
            LCD_SendPhrase("  ",2);
            //Displays first score

            LCD_SendPhrase("Player 2", 8);
            LCD_SendPhrase(" : ", 3);
            string_b8 temp = num2str(P2_Score,3);
            LCD_SendString(temp,3);
            LCD_SendPhrase("  ",2);
            //Displays second score

            if (OK_ONS == 1){
                state = INDICATE_TURN; //OK has been pressed, go to SHOW SCORE
            }
        }
        else if (state == INDICATE_TURN){

            LCD_ShowTurn();
            LCD_SendPhrase("'s Turn ",8);

            LCD_SendPhrase("To Roll ",8);
            LCD_SendHalfBlank();

            if (OK_ONS == 1){
                state = ROLL_PROMPT;
            }
            //NEEDS A WAY TO GET TO ROLL PROMPT
        }
        else if (state == ROLL_PROMPT){
            LCD_SendPhrase("$$ROLL$$",8);
            LCD_SendPhrase("$$ROLL$$",8);
            LCD_SendPhrase("$$ROLL$$",8);
            LCD_SendPhrase("$$ROLL$$",8);

            if (ROLL_ONS == 1){
                state = ROLLING_GRAPHIC;
            }

        }
        else if (state == ROLLING_GRAPHIC){

            for(uint8_t i = 0; i < 100; i++){
            string_b8 temp1;
            temp1 = set_at_range(temp1,1,8,255);
            temp1 = set_at(temp1,1,80);
            temp1 = set_at(temp1,3,73);
            temp1 = set_at(temp1,5,71);
            temp1 = set_at(temp1,7,36);
            LCD_SendString(temp1,7);
            __delay_ms(1);
            }
            LCD_SendPhrase("    ",4);
//            string_b8 temp2 = temp1;
//            temp2 = set_at(temp2,1,Random()+48);
//            temp2 = set_at(temp2,3,Random()+48);
//            temp2 = set_at(temp2,5,Random()+48);
//            temp2 = set_at(temp2,7,Random()+48);
//            LCD_SendString(temp2,8);
            if (ROLL_ONS == 0){
                state = GET_ROLL;
            }
            
        }

        else if (state == GET_ROLL){
            R_NUM = Random();
            if (R_NUM == 1){
                state = LOSE_TURN;
            }
            else{
                state = ADD_ROLL;   //Roll is 2->6
            }
        }
        else if (state == LOSE_TURN){
            LCD_ShowTurn();
            LCD_SendPhrase(" Has    ",8);
            LCD_SendPhrase("Lost a t",8);
            LCD_SendPhrase("urn     ",8);
            if (Player_Turn == 1){
                P1_Turn =0;
            }
            else{
                P2_Turn = 0;
            }
            if (OK_ONS == 1){
                state = CHANGE_PLAYER;
            }

        }
        else if (state == ADD_ROLL){
            if (Player_Turn == 1){
                P1_Turn = P1_Turn + R_NUM;
            }
            else{
                P2_Turn = P2_Turn + R_NUM;
            }

            state = SHOW_TURN_TOTAL;
        }
        else if (state == SHOW_TURN_TOTAL){
            //TODO
            string_b8 temp;
            LCD_SendPhrase("Die Roll",8);
            LCD_SendPhrase(":   ",4);
            temp = num2str(R_NUM,1);
            LCD_SendString(temp,3);    //Fills out rest of line
            LCD_SendPhrase(" ",1);
            LCD_SendPhrase("Turn Tot",8);
            LCD_SendPhrase("al: ",4);
            if (Player_Turn == 1){
                temp = num2str(P1_Turn,3);  //convert turn to string
            }
            else{
                temp = num2str(P2_Turn,3);  //convert turn to string
            }
            LCD_SendString(temp,3);     //display turns
            LCD_SendPhrase(" ",1);      //Fill up extra space

            if (Player_Turn == 1){
                if (P1_Turn >=100){
                    P1_Score = P1_Score + P1_Turn;//score and turn >= 100
                    state = SHOW_WINNER;
                }
                else if(ROLL_ONS == 1){
                    state = ROLLING_GRAPHIC;
                }
                else if(HOLD_ONS == 1){
                    state = ADD_TURN_TOTAL;
                }
            }
            else{
                if (P2_Turn >=100){
                    P2_Score = P2_Score + P2_Turn;//score and turn >= 100
                    state = SHOW_WINNER;
                }
                else if(ROLL_ONS == 1){
                    state = ROLLING_GRAPHIC;
                }
                else if(HOLD_ONS == 1){
                    state = ADD_TURN_TOTAL;
                }
            }

        }
        else if (state == SHOW_WINNER){
            if (P1_Score >= 100){
                LCD_SendPhrase("Player 1",8);
                LCD_SendPhrase("Has Won!",8);
            }
            else{
                LCD_SendPhrase("Player 2",8);
                LCD_SendPhrase("Has Won!",8);
            }

            if (OK_ONS == 1){
                state = TITLE_SCREEN;
            }
        }
        else if (state == ADD_TURN_TOTAL){
            if (Player_Turn == 1){
                P1_Score = P1_Score + P1_Turn;
            }
            else{
                P2_Score = P2_Score + P2_Turn;
            }
            state = CHANGE_PLAYER;
        }
        else if (state == CHANGE_PLAYER){
            if (Player_Turn == 1){
                Player_Turn = 2;
            }
            else{
                Player_Turn = 1;
            }
            state = SHOW_SCORE;
        }
        else{//RESET
            __delay_ms(250);
            state = TITLE_SCREEN;
        }

    }

     // end while(1)

} // end main()

uint8_t Random(){
    return count;
}

void LCD_ShowTurn(){
    if (Player_Turn == 1){
        LCD_SendPhrase("Player 1",8);
    }
    else{
        LCD_SendPhrase("Player 2",8);
    }
    return;
}

//------------------------------------------------------------------------------
// Function:   initialize()
// Parameters: void
// Returns:    void
//Initialization code for the application
//------------------------------------------------------------------------------
void MCU_initialize(void) {

    // Configure oscillator for 32 MHz
    OSCCONbits.IRCF = 14;  // Internal frequency 8 MHz x 4 (PLL)
    OSCCONbits.SPLLEN = 1; // Enable 4x PLL
    OSCCONbits.SCS = 0;    // Fosc comes from PLLMUX

    OPTION_REGbits.TMR0CS = 0;  //Select Oscillator Frequency FOSC / 4
    OPTION_REGbits.PSA = 0;     //Use Prescalar, scale the frequency
    OPTION_REGbits.PS = 0b100;  //Use 1:32 Prescaled

    TMR0 = 6;   //256-250 = 6, count head start
    TIMER0_FLAG = 0;    //Clear interrupt flag
    TMR0IE = 1;         //Enable Timer 0 interrupt
    //TMR0IE may cause an interrupt immediately

    //////////////////////////////////////
   // LEDBLINK = 1;
    //OSCTUNE = 0b100000; //Oscillator frequency minimum


    // Configure I/O pins
    // RA4, input,  Roll Pushbutton
    // RA5, input,  On/Off Switch
    // RC0, output, LED1 (Upper Left)
    // RC1, output, LED2 (Upper Right))
    // RC2, output, LED3 (Middle Left)
    // RC3, output, LED4 (Center)
    // RC4, output, LED5 (Middle Right)
    // RC5, output, LED6 (Lower Left)
    // RC6, output, LED7 (Lower Right)
    ANSELA  = 0b00000000;  // Port A analog select (0=digital, 1=analog)
    ANSELB  = 0b00000000;  // Port B analog select (0=digital, 1=analog)
    ANSELC  = 0b00000000;  // Port C analog select (0=digital, 1=analog)
    SLRCONA = 0b00000000;  // Port A slew rate control (1=slew rate limited)
    SLRCONB = 0b00000000;  // Port B slew rate control (1=slew rate limited)
    SLRCONC = 0b00000000;  // Port C slew rate control (1=slew rate limited)
    TRISA   = 0b11111111;  // Port A tri-state (0=output, 1=input)
    TRISB   = 0b00000000;  // Port B tri-state (0=output, 1=input)
    TRISC   = 0b00000000;  // Port C tri-state (0=output, 1=input)


    LCD_initialize();

} // end initialize()



void interrupt ISR(void){
    //Check flags and call appropriate handlers
    if (TMR0IE && TIMER0_FLAG)
    {
        //CAll time 0 handler
        Timer0Handler();
    }
    return;
}

//Use interrupt handler to change the state b
void Timer0Handler(void){
    TMR0IF = 0; //Reset Interrupt Flag for timer
    TMR0 = 6;
    OK_DEBOUNCED = OK_ & OK_SAMPLE
            | OK_SAMPLE & OK_DEBOUNCED
            | OK_ & OK_DEBOUNCED;
    ROLL_DEBOUNCED = ROLL_ & ROLL_SAMPLE
            | ROLL_SAMPLE & ROLL_DEBOUNCED
            | ROLL_ & ROLL_DEBOUNCED;
    HOLD_DEBOUNCED = HOLD_ & HOLD_SAMPLE
            | HOLD_SAMPLE & HOLD_DEBOUNCED
            | HOLD_ & HOLD_DEBOUNCED;

    OK_SAMPLE = OK_;
    ROLL_SAMPLE = ROLL_;
    HOLD_SAMPLE = HOLD_;

    //debounce value is last two values held by the sample
    count++;
    if (count == 7){
        count = 1;
    }
    if (OK_DEBOUNCED == 1 && ROLL_DEBOUNCED == 1 && HOLD_DEBOUNCED == 1){
        state = RESET;
    }
    
//    DIGIT1 = 0;
//    DIGIT2 = 0;
//    DIGIT3 = 0;
//    DIGIT4 = 0;
//    count++;
//    count_TIME++;
//    if (count_TIME == 10 )
//    {
//        count_TIME = 0;
//        time[3] = time[3] + count_WALTERS; //increment first number
//    }
//    if (count > 250 && sleep[0] < 20){
//        LEDBLINK = ~LEDBLINK;
//        count = 0;
//    }
//        sleep[1] = sleep[1] + count_SLEEPY_WALTERS; //increment sleep 250 counter
//    if (sleep[1] >= 250){   //sleep counter is at 250 mSeconds, increment sleep counter
//        sleep[1] = 0;
//        sleep[0]++;
//        if (sleep[0] == 250){
//            sleep[0] = 21;
//        }
//    }
//
//    select--;
//    if (select == 0){
//        select = 4;
//    }
//
//    if (sleep[0] >= 20) //this is greater than 5 seconds
//        {
//          reset();    //Display nothing
//        }
//
//        else{
//           if (select == 1){
//                DIGIT4  = 1;
//            }
//            else if (select == 2){
//                DIGIT3 = 1;
//            }
//            else if (select == 3){
//                DIGIT2 = 1;
//            }
//            else{
//                DIGIT1 = 1;
//            }
//           Display(time, select);
//
//         }
    return;
}
