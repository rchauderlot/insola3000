
#include "lcd.h"

#define _INSOLA_3000_DEBUG_


Lcd * lcd;
// Planificator configuration
long previousMillis = 0;        // will store last time LCD was updated
long interval = 1000;           // interval at which to upload (milliseconds) 
// main logic variable
int digit = 0;





void setup() {
#ifdef _INSOLA_3000_DEBUG_
  Serial.begin(9600);
  Serial.println("Setup");
#endif

  lcd = new Lcd(2,4,3);
}

void loop() {

  unsigned long currentMillis = millis();
 
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
     previousMillis = currentMillis;   
 
     lcd->sendDigit(digit);
     digit++;
     if (digit > 9) {
       lcd->sendCharString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 \0", 0);
       lcd->sendCharString("Da capo",250);
       digit = 0;
     }
  }

}
