#include "string.h"

string_b8 set_at(string_b8 dest, uint8_t index, unsigned char val){
    if (index == 8){
        dest.s7 = val;
    }
    if (index == 7){
        dest.s6 = val;
    }
    if (index == 6){
        dest.s5 = val;
    }
    if (index == 5){
        dest.s4 = val;
    }
    if (index == 4){
        dest.s3 = val;
    }
    if (index == 3){
        dest.s2 = val;
    }
    if (index == 2){
        dest.s1 = val;
    }
    if (index == 1){
        dest.s0 = val;
    }
    else{}
    return dest;
}

string_b8 set_at_range(string_b8 dest, uint8_t start, uint8_t stop, unsigned char val){
//    if (stop < 1)
//    {stop = 1;}
//    else if (stop > 8)
//    {stop = 8;}
//     if (stop < 1)
//    {stop = 1;}
//    if (stop > 8)
//    {stop = 8;)
    for (start; start <=stop; start++){
        dest = set_at(dest,start,val);
    }
    
    return dest;
}

string_b8 new_string(unsigned char str[], uint8_t size)
{
    string_b8 temp;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (i < size){
            temp = set_at(temp, i+1,str[i]);
        }
        else{
            temp = set_at(temp, i+1, 0);
        }
    }

    return temp;
}

unsigned char find (string_b8 source1, uint8_t index){
    string_b8 source = source1; //copy
    unsigned char val = 0;  // temp
    if (index == 8){
        val = source.s7;
    }
    if (index == 7){
        val = source.s6;
    }
    if (index == 6){
        val = source.s5;
    }
    if (index == 5){
        val = source.s4;
    }
    if (index == 4){
        val = source.s3;
    }
    if (index == 3){
       val = source.s2;
    }
    if (index == 2){
        val = source.s1;
    }
    if (index == 1){
       val = source.s0;
    }
    return val;
}

string_b8 copy(string_b8 dest, string_b8 source){
    string_b8 copy;
    for (uint8_t i = 1; i <= 8; i++){
        set_at(copy, i, find(source,i));//sets the copy at i to the source at i
    }
    return copy;
}

string_b8 num2str(uint8_t num, uint8_t size){
    //!!!!!!!!!!!!!!!There is a More efficient way than this
    string_b8 x;
    uint8_t temp = num % 10;    //tens place
    x = set_at(x,size,temp+48);    //give first number in the string
    for (uint8_t i = 1; i < size; i++){
        num = num - temp;   //subtract moded number from number given
        num = num / 10;     //bring number given back by one place
        temp = num % 10;    //mod a number
        x = set_at(x,size-i,temp+48);   //adds a character the next highest spot
    }

    return x;
}