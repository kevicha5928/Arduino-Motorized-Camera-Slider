#include "menuStuff.h"
#include "functions.h"

//generates a menu of quick access time slides
void quickAccess()
{
  zeroSystem();
  boolean state = true;
  display.clearDisplay();
  delay(500);
  button = false;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Quick Prog");
  display.drawLine(0,15,127,15,WHITE);
  Serial.println(button);
  
  while(state)
  {
//    define menu size
    menuCounter(4);
    String mainMenu[] = {">10 sec",">20 sec",">1 min",">Back"};
//    generate menu
    menuGeneration(4,mainMenu);
    if(button == true)//if button is pressed
      {
        delay(500); // time delay to ensure button is released
        button=false;//set button state to false, otherwise it will remain true. it is toggle.
        switch(menuitem){
          case 1:
            durationSlide(10);
            break;
          case 2:
            durationSlide(20);  
            break;
          case 3:
            durationSlide(60);
            break;
          case 4:
            break;
        }
        state = false;      
      }
  }
  delay(500);
  
  
  
  
  
}

//function to manually jog motor position
//not particularly useful, but you never know...
//There is probably a better way to code this up
void manualMove()
{
//  zeroSystem();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Scroll to Move");
  display.drawLine(0,15,127,15,WHITE);
  display.setTextColor(WHITE,BLACK);
  display.setCursor(20,30);
  display.println("LEFT"); 
  display.setCursor(20,40);
  display.println("RIGHT");
  display.setCursor(0,50);
  display.println("Press to Return");
  delay(500);
  button=false;  
  int timeDiff;
  int lastTime = millis();
  while(button==false)
  {
    timeDiff=millis()-lastTime;
    if (left) {
      left = false;  
      display.setTextSize(1);
      display.setTextColor(BLACK,WHITE);
      display.setCursor(20,30);
      display.println("LEFT");
      display.setTextColor(WHITE,BLACK);
      display.setCursor(20,40);
      display.println("RIGHT");
//      display.display(); 
      stepper.enableOutputs(); 
      stepper.move(-50);
      stepper.setSpeed(1000);
      Serial.println(timeDiff);
      while(timeDiff<1000){
        timeDiff=millis()-lastTime;
        stepper.runSpeed(); 
      }
      lastTime=millis();
      stepper.disableOutputs(); 
    } 
    if (right) {
      right = false;
      display.setTextSize(1);
      display.setTextColor(WHITE,BLACK);
      display.setCursor(20,30);
      display.println("LEFT"); 
      display.setTextColor(BLACK,WHITE);
      display.setCursor(20,40);
      display.println("RIGHT");
//      display.display(); 
      stepper.enableOutputs(); 
      stepper.move(50); 
      stepper.setSpeed(-1000);
      while(timeDiff<1000){
        timeDiff=millis()-lastTime;
        stepper.runSpeed(); 
      }
      lastTime=millis();
      stepper.disableOutputs(); 
    }
    display.display();     
  }
  delay(500);
}

//homes the system to the limit switch
void zeroSystem()
{
  delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("Zeroing...");
  display.display(); 
  boolean state = false;
  stepper.enableOutputs();
  stepper.setSpeed(-2000);
  while(state==false)
  {
    state=digitalRead(8);
    stepper.runSpeed();
  }
  stepper.disableOutputs();  
}

//function to create user programmable time slides
void createSlide()
{
  zeroSystem();
  boolean state = true;
  int hours=0;
  int minutes=0;
  int seconds=0;
  int duration=0;
  
  while(state)
  {
//    define menu size
    menuCounter(5);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(40,0);
    display.println("Time");
    display.drawLine(0,15,127,15,WHITE);
//    If statements to handle a 5 item menu
//    there is probably a better way to code this as well
//    values will update on the display as the user defines them
    if(menuitem==5)
    {
      String timeMenu[] = {">Min: "+String(minutes),
          ">Sec: "+String(seconds),">Back",">Start"};
      menuGeneration(4,timeMenu);

    } else {
      String timeMenu[] = {">Hrs: "+String(hours),">Min: "+String(minutes),
          ">Sec: "+String(seconds),">Back"};    
      menuGeneration(4,timeMenu);  
    }
    if(button == true)
    {
      delay(500);
      button=false;
      switch(menuitem){
        case 1:
          hours=timeLimit(0,120,"Hrs"); //limit is 120 hours 
          break;
        case 2:
          minutes=timeLimit(0,59,"Min"); //limit is 59 minutes 
          break;
        case 3:
          if(hours==0 &&minutes==0)
          {
            seconds=timeLimit(10,59,"Sec"); //minute is 10 seconds if 0 hours and minutes  
          } else {
            seconds=timeLimit(0,59,"Sec"); //limit is 59 seconds    
          }   
          break;
        case 4:
          state = false;
          display.clearDisplay();
          break;
        case 5:
          duration=hours*3600+minutes*60+seconds;
          display.clearDisplay();
          durationSlide(duration);
          state=false;
          break;       
      }   
      menuitem=1;   
    }
        
  }  
}

//runs the stepper to move a certain distance in a specified time limit
void durationSlide(int duration)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.println("Running");
  display.drawLine(0,15,127,15,WHITE);
  display.display();
  float chassisLength = 22500;
  int actualSteps=0;
  float moveSpeed = chassisLength/duration;  //steps per second
  stepper.enableOutputs();//enable motor
  int pos = stepper.currentPosition();
  stepper.moveTo(pos+chassisLength);
  stepper.setSpeed(moveSpeed);
  while(stepper.distanceToGo()>0){
    stepper.runSpeed(); 
  }
  stepper.disableOutputs();  //disable motor
  delay(2000);
  zeroSystem();
}

//creates the menu on the oled display
void menuGeneration(int numItems,String str[])
{
  display.setTextSize(1);
//  generates and displays a list of menu items
//~~~~~~~~~~~~TO-DO~~~~~~~~~
//limit vertical display output
  for(int i=1;i<numItems+1;i++)
  {
    display.setCursor(0, 10+i*10);    
    if (menuitem==i){display.setTextColor(BLACK,WHITE);}
    else if (i==4 && menuitem==5){display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE, BLACK);}
    
    display.print(str[i-1]);    
  }
  display.display(); //update display
}


int timeLimit(int low,int high, char *str)
{
  numCount=low;
  boolean state = true;
  int time;
  while(state)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20,0);
    display.println("Press to Confirm");    
    display.drawLine(0,15,127,15,WHITE);
    time = numCounter(low,high);
    display.setCursor(25, 20);
    display.setTextSize(4);
    display.print(time);  
    display.setCursor(30, 50);
    display.setTextSize(2);
    display.println(str);
    display.display();
    if(button==true){state=false;};    
  }
  delay(500);
  button=false;
  return time;  
}
