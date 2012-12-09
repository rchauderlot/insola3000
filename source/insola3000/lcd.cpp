

#include "lcd.h"


// Variables will change:
// LDC control
//                  0         1         2         3         4         5         6         7         8         9         A         b         C         D         E         F
char lcdDigits[] = {B00111111,B00000110,B01011011,B01001111,B01100110,B01101101,B01111101,B00000111,B01111111,B01101111,B00110111,B01111100,B00111001,B01011110,B01111001,B01110001};
//                   A         b         C         d         E         F         G         H         I         J         K*NO_SUP  L         M*NO_SUP  n         o         p         q         r         S         t         u         v*NO_SUP  w*NO_SUP  x*NO_SUP  y         z
char lcdLetters[] = {B01110111,B01111100,B00111001,B01011110,B01111001,B01110001,B01111101,B01110110,B00000110,B00011111,B00000000,B00111000,B00110111,B01010100,B01011100,B01110011,B01100111,B01010000,B01101101,B01111000,B00011100,B00111110,B00000000,B00000000,B01101110,B01011011};



Lcd::Lcd(int updateRegisterPin, int clockSerialPin, int dataSerialPin) {
  this->_updateRegisterPin = updateRegisterPin;
  this->_clockSerialPin = clockSerialPin;
  this->_dataSerialPin = dataSerialPin;
  
  pinMode(_updateRegisterPin, OUTPUT);
  pinMode(_clockSerialPin   , OUTPUT);
  pinMode(_dataSerialPin    , OUTPUT);

}


void Lcd::sendBit(boolean active) {

    digitalWrite(_clockSerialPin, LOW);
    if (active) { 
      digitalWrite(_dataSerialPin, HIGH);
    }else {
      digitalWrite(_dataSerialPin, LOW);
    }
    digitalWrite(_clockSerialPin, HIGH);
}

void Lcd::sendByte(char character) {
  for (int i=7; i>=0; i--) {
    sendBit(bitRead(character, i));
  }
}


void Lcd::sendChar(char character) {

#ifdef _LCD_DEBUG_
  Serial.print("sendChar ");
  Serial.println(character);
#endif

  char lcdCharacter=0x00;
  
  if (character >= '0' && character <= '9') {
    lcdCharacter=lcdDigits[character-'0'];
  }
  if (character >= 'A' && character <= 'Z') {
    lcdCharacter = lcdLetters[character-'A'];
  }
  if (character >= 'a' && character <= 'z') {
    lcdCharacter = lcdLetters[character-'a'];
  }
  digitalWrite(_updateRegisterPin, LOW);
  sendByte(lcdCharacter);
  digitalWrite(_updateRegisterPin, HIGH);
}

void Lcd::sendDigit(int zeroToNineDigit) {

#ifdef _LCD_DEBUG_
  Serial.print("sendDigit ");
  Serial.println(zeroToNineDigit);
#endif
  digitalWrite(_updateRegisterPin, LOW);
  sendByte(lcdDigits[zeroToNineDigit]);
  digitalWrite(_updateRegisterPin, HIGH);
}

void Lcd::sendCharString(char zeroEndedCharPointer[], int delayBetweenDigits) {
#ifdef _LCD_DEBUG_
  Serial.print("sendCharString ");
  Serial.println(zeroEndedCharPointer);
#endif
  char * currentChar = zeroEndedCharPointer;
  while (*currentChar) {  
    digitalWrite(_updateRegisterPin, LOW);
    sendChar(*currentChar);
    digitalWrite(_updateRegisterPin, HIGH);
    delay(delayBetweenDigits);
    currentChar++;
  }
}
