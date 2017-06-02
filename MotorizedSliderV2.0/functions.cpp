#include "functions.h"

int menuCounter(int high) //function to count menu numbers
{
  //loops the count back to the highest or lowest number.
  if (left) {
    left = false;
    menuitem--;
    if (menuitem==0) {menuitem=high;}      
  }
  if (right) {
    right = false;
    menuitem++;
    if (menuitem==high+1) {menuitem=1;}      
  }  
  return menuitem;
}

int numCounter(int low, int high) // function to count custom ranges of numbers
{
  if (left) {
    left = false;
    numCount--;
    if (numCount<=0) {numCount=high;}      
  }
  if (right) {
    right = false;
    numCount++;
    if (numCount>=high+1) {numCount=low;}      
  }  
  return numCount;
}

//Obsolete Code Section. Used in case without AccelStepper

//void rotate(int steps, float speed){
//
//  digitalWrite(smEnablePin, LOW); //Enabling the motor, so it will move when asked to
// 
//  /*This section looks at the 'steps' argument and stores 'HIGH' in the 'direction' variable if */
//  /*'steps' contains a positive number and 'LOW' if it contains a negative.*/
//  int direction;
// 
//  if (steps > 0){
//    direction = HIGH;
//  }else{
//    direction = LOW;
//  } 
//  speed = 1/speed * 70; //Calculating speed
//  steps = abs(steps); //Stores the absolute value of the content in 'steps' back into the 'steps' variable
// 
//  digitalWrite(smDirectionPin, direction); //Writes the direction (from our if statement above), to the EasyDriver DIR pin
// 
//  /*Steppin'*/
//  for (int i = 0; i < steps; i++){
//    digitalWrite(smStepPin, HIGH);
//    delayMicroseconds(speed);
//    digitalWrite(smStepPin, LOW);
//    delayMicroseconds(speed);
//  } 
//  digitalWrite(smEnablePin, HIGH); //Disbales the motor, so it can rest untill the next time it is called uppond
//}

//todo add accelerate option

void accelStep()
{
  
  
}

