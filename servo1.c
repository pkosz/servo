#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"
#define DETECTOR_bm (1<<10)

enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS,};

struct Servo {
    enum ServoState eState;
    unsigned int uiCurrentPosition;
    unsigned int uiDesiredPosition;
};

struct Servo sServo;
unsigned int uiLed = 0;

void DetectorInit(void) {
    IO0DIR &= ~(DETECTOR_bm);
}

enum DetectorState eReadDetector(void) {
    if(IO0PIN & DETECTOR_bm) {
        return INACTIVE;
    }
    else {
        return ACTIVE;
    }
}

void ServoCallib(void) {
    sServo.eState = CALLIB;
		
}

void ServoGoTo(unsigned int uiPosition) {
    sServo.uiDesiredPosition = uiPosition;
    sServo.eState = IN_PROGRESS;
    

}

void Automat(void) {
    switch(sServo.eState) {
        case CALLIB:
            if(eReadDetector() == INACTIVE) {
                LedStepRight();
            } else {
                sServo.uiCurrentPosition = 0;
                sServo.uiDesiredPosition = 0;
                sServo.eState = IDLE;
            }
            break;
        case IN_PROGRESS:
            if(sServo.uiDesiredPosition == sServo.uiCurrentPosition) {
                sServo.eState = IDLE;
            }
            else if(sServo.uiDesiredPosition > sServo.uiCurrentPosition) {
                LedStepLeft();
                sServo.uiCurrentPosition++;
            }
            else if(sServo.uiDesiredPosition < sServo.uiCurrentPosition) {
                LedStepRight();
                sServo.uiCurrentPosition--;
            }
            break;
        case IDLE:
            if(sServo.uiDesiredPosition != sServo.uiCurrentPosition) {
                sServo.eState = IN_PROGRESS;
            }
            break;
    }
	}

void ServoInit(unsigned int uiServoFrequency) {
    unsigned int uiDelayTime = 1000000 / uiServoFrequency;
    LedInit();
    DetectorInit();
    sServo.eState = CALLIB;
    Timer0Interrupts_Init(uiDelayTime, &Automat);
		
		

}

