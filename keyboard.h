#ifndef KEYBOARD_H
#define KEYBOARD_H

enum iButtonState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
void KeyBoardInit(void);
enum iButtonState eKeyboardRead(void);

#endif