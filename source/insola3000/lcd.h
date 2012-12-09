#ifndef _LCD_
#define _LCD_


#include "Arduino.h"

//#define _LCD_DEBUG_

class Lcd {

public:
  Lcd(int updateRegisterPin, int clockSerialPin, int dataSerialPin);
  
  
  void sendByte(char character);
  void sendChar(char character);
  void sendDigit(int zeroToNineDigit);
  void sendCharString(char zeroEndedCharPointer[], int delayBetweenDigits);

private:

  void sendBit(boolean active);
  
  int _updateRegisterPin;
  int _clockSerialPin;
  int _dataSerialPin;
    

};

#endif /* _LCD_ */
