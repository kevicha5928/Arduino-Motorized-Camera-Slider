
#include <AccelStepper.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "menuStuff.h"
#include "functions.h"

/*
AccelStepper Website:
http://www.airspayce.com/mikem/arduino/AccelStepper/
Direct Download:
http://www.airspayce.com/mikem/arduino/AccelStepper/AccelStepper-1.57.zip

Adafruit GFX:
https://github.com/adafruit/Adafruit-GFX-Library

Adafruit SSD1306:
https://github.com/adafruit/Adafruit_SSD1306
*/


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//~~~~~~~~rotary encoder stuff~~~~~~~~~~//  
volatile byte seqA = 0;
volatile byte seqB = 0;
volatile byte cnt1 = 0;
volatile byte cnt2 = 0;
volatile boolean right = false;
volatile boolean left = false;
volatile boolean button = false;
//~~~~~~~~end of rotary encoder stuff~~~~~~~~~~//  

int menuitem=1;
int numCount=1;

AccelStepper stepper(AccelStepper::DRIVER, 3,2);


void setup()   {
  

//~~~~~~~~rotary encoder stuff~~~~~~~~~~//  
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  
  // Enable internal pull-up resistors
  digitalWrite(A8, HIGH);
  digitalWrite(A9, HIGH);
  digitalWrite(A10, HIGH);
 
  PCICR |= (1 << PCIE2); // 1. PCIE2: Pin Change Interrupt Enable K Group
  PCMSK2 = 0b00000111; // Enable Pin Change Interrupt for A8, A9, A10
//  references
//  https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/
//  https://thewanderingengineer.com/2014/08/11/arduino-pin-change-interrupts/
//  http://forum.arduino.cc/index.php?topic=45239.30

//~~~~~~~~end of rotary encoder stuff~~~~~~~~~~//  

//~~~~~~~~Stepper Stuff~~~~~~~~~

//  defines the pin that enable/disable the motor
  stepper.setEnablePin(7);
//  inverts the enable pin. Change the third variable if your pin is not inverted
  stepper.setPinsInverted(false, false, true);
  stepper.setMaxSpeed(5000);
//  stepper.setAcceleration(1000);
//  deactivates the motor
  stepper.disableOutputs();

//~~~~~~~~end Stepper Stuff~~~~~~~~~

  pinMode(8,INPUT);
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello!");
  display.display();
  delay(1000);

  display.clearDisplay();
}

void loop() {  
  menuSelect(menuCounter(4));  
}

void menuSelect(int menuitem)//main menu
{
  button=false;
  int numItems=4;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40,0);
  display.println("Menu");
  display.drawLine(0,15,127,15,WHITE);
  
  String mainMenu[] = {">Quick Access",">Program",">Manual",">Zero"};
  menuGeneration(numItems,mainMenu);
  if(button == true)//if button is pressed
    {
      delay(500); // time delay to ensure button is released
      button=false;//set button state to false, otherwise it will remain true. it is toggle.
      switch(menuitem){
        case 1:
          quickAccess();
          break;
        case 2:
          createSlide();  
          break;
        case 3:
          manualMove();
          break;
        case 4:
          zeroSystem();
          break;
      }      
    }
}


//Rotary encoder stuff. This will always run in the background allowing you to use the knob 
//as the primary control mechanism
ISR (PCINT2_vect) {

// If interrupt is triggered by the button
  if (!digitalRead(A8)) {
    
    button = true;}

// Else if interrupt is triggered by encoder signals
  else {
    
    // Read A and B signals
    boolean A_val = digitalRead(A9);
    boolean B_val = digitalRead(A10);
    
    // Record the A and B signals in seperate sequences
    seqA <<= 1;
    seqA |= A_val;
    
    seqB <<= 1;
    seqB |= B_val;
    
    // Mask the MSB four bits
    seqA &= 0b00001111;
    seqB &= 0b00001111;
    
    // Compare the recorded sequence with the expected sequence
    if (seqA == 0b00001001 && seqB == 0b00000011) {
      cnt1++;
      left = true;
      }
     
    if (seqA == 0b00000011 && seqB == 0b00001001) {
      cnt2++;
      right = true;
      }
  }

}


