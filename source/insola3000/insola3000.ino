
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

// Clock variables
boolean clockActive = false;
long startTimeMilis = 0;

long programmedTime = 0;

// Planificator configuration
long previousMillis = 0;        // will store last time LCD was updated
long interval = 1000;           // interval at which to upload (milliseconds) 



void startStopButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("StartStop button pressed");
#endif

  if (clockActive) {
    
    clockActive=false;
    digitalWrite(outputPin, LOW);
    
  } else if (programmedTime > 0) {
    clockActive=true;
    digitalWrite(outputPin, HIGH);
  }


}

void upButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Up button pressed");
#endif

  if (!clockActive) {
    programmedTime += 5;
    programmedTime %= MAX_PROGRAMMABLE_TIME;
    updateDisplay();
  }

}


void upButtonLongPressed() {
#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Up button looong pressed");
#endif

  if (!clockActive) {
    programmedTime += 60;
    programmedTime %= MAX_PROGRAMMABLE_TIME;
    updateDisplay();
  }
  
}


void downButtonPressed() {

#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Down button pressed");
#endif

  if (!clockActive) {
    programmedTime -= 5;
    programmedTime %= MAX_PROGRAMMABLE_TIME;
    updateDisplay();
  }

}


void downButtonLongPressed() {
 
#ifdef _INSOLA_3000_DEBUG_
  Serial.println("Down button looong pressed");
#endif

  if (!clockActive) {
    programmedTime -= 60;
    programmedTime %= MAX_PROGRAMMABLE_TIME;
    updateDisplay();
  }
  
}

void updateDisplay() {

  int minutes = programmedTime / 60;
  int seconds = programmedTime % 60;
  
  int minutesMSD = (minutes / 10) % 10;
  int minutesLSD = minutes % 10;
  int secondsMSD = seconds / 10; 
  int secondsLSD = seconds % 10;
  
  lcd->sendDigit(secondsLSD);
  lcd->sendDigit(secondsMSD);
  lcd->sendDigit(minutesLSD);
  lcd->sendDigit(minutesMSD);
  
}

void setup() {
#ifdef _INSOLA_3000_DEBUG_
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Insola 3000");
#endif
  lcd = new Lcd(LCD_UPDATE_PIN,LCD_CLOCK_PIN,LCD_DATA_PIN);
  //lcd->sendCharString("Insola 3000", 500);
  //lcd->sendCharString("0000", 0);

  upButton = new Button(UP_BUTTON_PIN, upButtonPressed, DEBOUNCE_DELAY);
  downButton = new Button(DOWN_BUTTON_PIN, downButtonPressed, DEBOUNCE_DELAY);
//  upButton = new Button(UP_BUTTON_PIN, upButtonPressed, DEBOUNCE_DELAY, upButtonLongPressed, LONGPRESS_DELAY);
//  downButton = new Button(DOWN_BUTTON_PIN, downButtonPressed, DEBOUNCE_DELAY, downButtonLongPressed, LONGPRESS_DELAY);
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
  
  if (clockActive) {
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
