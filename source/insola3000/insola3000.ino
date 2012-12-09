
#include "lcd.h"
#include "button.h"
#include "config.h"

// Inputs
Button * upButton;
Button * downButton;
Button * startStopButton;
// Outputs
Lcd * lcd;
int outputPin;
int outputState;

// Clock variables
boolean clockActive = false;
long startTimeMilis = 0;


// Planificator configuration
long previousMillis = 0;        // will store last time LCD was updated
long interval = 1000;           // interval at which to upload (milliseconds) 


void startStopButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("StartStop button pressed");
#endif

  if (clockActive) {
    
    clockActive=false;
    
  } else {
  
    clockActive=true;
  }


}

void upButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Up button pressed");
#endif

  if (!clockActive) {
  
  }

}


void downButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Down button pressed");
#endif

  if (!clockActive) {
  
  }

}


void updateDisplay() {

  
  
}

void setup() {
#ifdef _INSOLA_3000_DEBUG_
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Insola 3000");
#endif
  lcd = new Lcd(LCD_UPDATE_PIN,LCD_CLOCK_PIN,LCD_DATA_PIN);
  //lcd->sendCharString("Insola 3000", 500);
  //lcd->sendCharString("0000", 0);
  
  upButton = new Button(UP_BUTTON_PIN, upButtonPressed, 20);
  downButton = new Button(DOWN_BUTTON_PIN, downButtonPressed, 20);
  startStopButton = new Button(STARTSTOP_BUTTON_PIN, startStopButtonPressed, 20);
  
  outputPin = 8;
}

void loop() {

  // Updating button states
  upButton->update();
  downButton->update();
  startStopButton->update();
  
  unsigned long currentMillis = millis();
 
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
     previousMillis = currentMillis;   
 
  }
  

}
