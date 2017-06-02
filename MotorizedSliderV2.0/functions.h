#ifndef Functions_h
#define Functions_h

#include <Arduino.h>

extern volatile boolean right;
extern volatile boolean left;

extern int menuitem;
extern int numCount;
//~~~~~~stepper declarations pin~~~~~~~~~~
extern int smDirectionPin; //Direction pin
extern int smStepPin; //Stepper pin
extern int smEnablePin; //Motor enable pin

void rotate(int steps, float speed);
int menuCounter(int high);
int numCounter(int low, int high);

#endif
