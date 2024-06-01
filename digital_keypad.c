#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
{
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    static unsigned char longpress; 
    static unsigned char prev_key = 0x00;
    
    if (mode == LEVEL_DETECTION)
    {
        return KEYPAD_PORT & INPUT_LINES;
    }
    else
    {
        if (((KEYPAD_PORT & INPUT_LINES) != ALL_RELEASED) && once)
        {
            once = 0;
            longpress=0;
            prev_key=KEYPAD_PORT & INPUT_LINES;
            
        }
        else if ( !once && (prev_key==(KEYPAD_PORT & INPUT_LINES)) && longpress<30)
        {
            longpress++;
        }
        else if (longpress==30)
        {
            longpress++;
            return prev_key | 0x80;
        }
        else if (((KEYPAD_PORT & INPUT_LINES) == ALL_RELEASED) && !once)
        {
            once = 1;
            if(longpress<30)
            {
                return prev_key;
            }
        }
    }
    
    return ALL_RELEASED;
}
