#ifndef menuStuff_h
#define menuStuff_h

#include <AccelStepper.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>


extern AccelStepper stepper;
extern Adafruit_SSD1306 display;
extern volatile boolean button;
extern volatile boolean right;
extern volatile boolean left;

extern int menuitem;
extern int numCount;
//~~~~~~stepper declarations pin~~~~~~~~~~
extern int smDirectionPin; //Direction pin
extern int smStepPin; //Stepper pin
extern int smEnablePin; //Motor enable pin

void menuGeneration(int numItems,String str[]);
void quickAccess();
void manualMove();
void zeroSystem();
void createSlide();
void durationSlide(int duration);
int timeLimit(int low,int high, char *str);

#endif
