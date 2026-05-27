#ifndef SERVO_H
#define SERVO_H

void ServoInit(unsigned int uiServoFrequency);
void ServoGoTo(unsigned int uiPosition);
void ServoCallib(void);

#endif