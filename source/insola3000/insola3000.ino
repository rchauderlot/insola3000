
#define LCD_TM1637
//#define LCD_74HC595



#ifdef LCD_74HC595
#include <lcd.h>
#endif
#ifdef LCD_TM1637
#include <TM1637.h>
#endif

#include <button.h>
#include "config.h"

#define LCD_DIGITS 4

// Inputs
Button * upButton;
Button * downButton;
Button * startStopButton;
// Outputs
#ifdef LCD_74HC595
Lcd * lcd = new Lcd(LCD_UPDATE_PIN,LCD_CLOCK_PIN,LCD_DATA_PIN);
#endif
#ifdef LCD_TM1637
TM1637 * lcd = new TM1637(LCD_CLOCK_PIN, LCD_DATA_PIN);
#endif
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

#ifdef LCD_74HC595
  char buffer[LCD_DIGITS+1];
  buffer[0]='0'+minutesMSD;
  buffer[1]='0'+minutesLSD;
  buffer[2]='0'+secondsMSD;
  buffer[3]='0'+secondsLSD;
  buffer[4]=0;
  lcd->sendCharString(buffer, true);
#endif
#ifdef LCD_TM1637
  int buffer[LCD_DIGITS];
  buffer[0]=minutesMSD;
  buffer[1]=minutesLSD;
  buffer[2]=secondsMSD;
  buffer[3]=secondsLSD;
  for (int i= LCD_DIGITS - 1; i>=0; i--) {
    lcd->display(i,buffer[i]);
 }
#endif
  
}

void setup() {
#ifdef _INSOLA_3000_DEBUG_
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("Insola 3000");
#endif

  if (LCD_VCC_PIN >= 0) {
    pinMode(LCD_VCC_PIN, OUTPUT);
    digitalWrite(LCD_VCC_PIN, HIGH);
  }
  if (LCD_GND_PIN >= 0) {
    pinMode(LCD_GND_PIN, OUTPUT);
    digitalWrite(LCD_GND_PIN, LOW);
  }
  // ALready init when created the class
  //lcd = new Lcd(LCD_UPDATE_PIN,LCD_CLOCK_PIN,LCD_DATA_PIN);
  
//  lcd->sendCharString("Insola 3000", 500);
//  lcd->sendCharString("0000", 0);

#ifdef LCD_TM1637
  lcd->init();
  lcd->set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
#endif


  // INIT BUTTONS
  upButton = new Button(UP_BUTTON_PIN, upButtonPressed, DEBOUNCE_DELAY, upButtonLongPressed, LONGPRESS_DELAY, LONGPRESS_REPETITION, LOW, true);
  downButton = new Button(DOWN_BUTTON_PIN, downButtonPressed, DEBOUNCE_DELAY, downButtonLongPressed, LONGPRESS_DELAY, LONGPRESS_REPETITION, LOW, true);
  startStopButton = new Button(STARTSTOP_BUTTON_PIN, startStopButtonPressed, DEBOUNCE_DELAY, LOW, true);
  if (BUTTONS_COMMON_PIN >= 0) {  // key board common...cathode
    pinMode(BUTTONS_COMMON_PIN, OUTPUT);
    digitalWrite(BUTTONS_COMMON_PIN, BUTTONS_COMMON_VALUE);
  }
  


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
