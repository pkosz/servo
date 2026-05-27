#include <LPC21xx.H>
#include "keyboard.h"

#define But0_bm 0x00000010
#define But1_bm 0x00000020
#define But2_bm 0x00000040
#define But3_bm 0x00000080

void KeyBoardInit(void)
{
    IO0DIR &= ~(But0_bm | But1_bm | But2_bm | But3_bm);
}


enum iButtonState eKeyboardRead(void)
{
    if(1 == (0 == (IO0PIN & But0_bm))) {
        return BUTTON_0;
    }
    else if(1 == (0 == (IO0PIN & But2_bm))) {
        return BUTTON_1;
    }
    else if(1 == (0 == (IO0PIN & But1_bm))) {
        return BUTTON_2;
    }
    else if(1 == (0 == (IO0PIN & But3_bm))) {
        return BUTTON_3;
    }

    return RELASED;
}