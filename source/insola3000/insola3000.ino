
#include "lcd.h"
#include "button.h"

//#define _INSOLA_3000_DEBUG_

// Inputs
Button * upButton;
Button * downButton;
Button * startStopButton;
// Outputs
Lcd * lcd;
int outputPin;
int outputState;

// Clock variables
long startTimeMilis = 0;


// Planificator configuration
long previousMillis = 0;        // will store last time LCD was updated
long interval = 1000;           // interval at which to upload (milliseconds) 


void startStopButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("StartStop button pressed");
#endif

}

void upButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Up button pressed");
#endif

}


void downButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Down button pressed");
#endif

}

void setup() {
#ifdef _INSOLA_3000_DEBUG_
  Serial.begin(9600);
  Serial.println("Insola 3000");
#endif
  lcd = new Lcd(2,4,3);
  //lcd->sendCharString("Insola 3000", 500);
  //lcd->sendCharString("0000", 0);
  
  startStopButton = new Button(7, startStopButtonPressed, 20);
  upButton = new Button(5, upButtonPressed, 20);
  downButton = new Button(6, downButtonPressed, 20);
  
  outputPin = 8;
}

void loop() {

  // Updating button states
  startStopButton->update();
  upButton->update();
  downButton->update();
  
  unsigned long currentMillis = millis();
 
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
     previousMillis = currentMillis;   
 
  }

}
