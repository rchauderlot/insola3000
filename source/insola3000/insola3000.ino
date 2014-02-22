

#include <lcd.h>
#include <button.h>
#include "config.h"

// Inputs
Button * upButton;
Button * downButton;
Button * startStopButton;
// Outputs
Lcd * lcd;
int outputPin;

// Clock variables
boolean clockActive = false;
long startTimeMilis = 0;

long programmedTime = 0;
long maxProgrammableTime = MAX_PROGRAMMABLE_TIME;
long minProgrammableTime = 0;

// Planificator configuration
unsigned long previousMillis = 0;        // will store last time LCD was updated
unsigned long interval = 1000;           // interval at which to upload (milliseconds) 



void startStopButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("StartStop button pressed");
#endif

  if (clockActive) {
    
    clockActive=false;
    digitalWrite(outputPin, LOW);
    
  } else {
    clockActive=true;
    digitalWrite(outputPin, HIGH);
  }


}

void upButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Up button pressed");
#endif

  programmedTime += 5;
  if (programmedTime > maxProgrammableTime) {
      programmedTime = maxProgrammableTime;
  }
  updateDisplay();

}


void upButtonLongPressed() {
#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Up button looong pressed");
#endif

  programmedTime += 60;
  if (programmedTime > maxProgrammableTime) {
      programmedTime = maxProgrammableTime;
  }
  updateDisplay();
  
}


void downButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Down button pressed");
#endif

  programmedTime -= 5;
  if (programmedTime < minProgrammableTime) {
      programmedTime = minProgrammableTime;
      if (clockActive && programmedTime == 0) {
          clockActive=false;
          digitalWrite(outputPin, LOW);
      }
  }
  updateDisplay();

}


void downButtonLongPressed() {
 
#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Down button looong pressed");
#endif

  programmedTime -= 60;
  if (programmedTime < minProgrammableTime) {
      programmedTime = minProgrammableTime;
      if (clockActive && programmedTime == 0) {
          clockActive=false;
          digitalWrite(outputPin, LOW);
      }
  }
  updateDisplay();
  
}

void updateDisplay() {

  int minutes = programmedTime / 60;
  int seconds = programmedTime % 60;
  
  int minutesMSD = (minutes / 10) % 10;
  int minutesLSD = minutes % 10;
  int secondsMSD = seconds / 10; 
  int secondsLSD = seconds % 10;

  char buffer[5];
  buffer[0]='0'+minutesMSD;
  buffer[1]='0'+minutesLSD;
  buffer[2]='0'+secondsMSD;
  buffer[3]='0'+secondsLSD;
  buffer[4]=0;
  lcd->sendCharString(buffer, true);
}

void setup() {
#ifdef _INSOLA_3000_DEBUG_
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Insola 3000");
#endif
  lcd = new Lcd(LCD_UPDATE_PIN,LCD_CLOCK_PIN,LCD_DATA_PIN);
  //lcd->sendCharString("Insola 3000", 500);
  //lcd->sendCharString("0000", 0);

  upButton = new Button(UP_BUTTON_PIN, upButtonPressed, DEBOUNCE_DELAY, upButtonLongPressed, LONGPRESS_DELAY, LONGPRESS_REPETITION);
  downButton = new Button(DOWN_BUTTON_PIN, downButtonPressed, DEBOUNCE_DELAY, downButtonLongPressed, LONGPRESS_DELAY, LONGPRESS_REPETITION);
  startStopButton = new Button(STARTSTOP_BUTTON_PIN, startStopButtonPressed, DEBOUNCE_DELAY);
  
  outputPin = OUTPUT_PIN;
  pinMode(outputPin, OUTPUT);
    
  updateDisplay();
}

void loop() {

  // Updating button states
  upButton->update();
  downButton->update();
  startStopButton->update();
  
  if (clockActive && programmedTime > 0) {
    unsigned long currentMillis = millis();
 
    if(currentMillis - previousMillis > interval) {
       previousMillis = currentMillis;
       programmedTime -= 1;
       if (programmedTime == 0) {
         clockActive = false;
         digitalWrite(outputPin, LOW);
       }
       updateDisplay();
    }
  }
  

}
