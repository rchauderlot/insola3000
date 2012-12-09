#ifndef _BUTTON_
#define _BUTTON_


#include "Arduino.h"

class Button {

public:

  Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay);
  Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay, void(*buttonLongPressedCallback)(void), long longPressRepetitionDelay);
  void update();
    
    
private:

  void (*_buttonPressedCallback)(void);
  void (*_buttonLongPressedCallback)(void);
  long _longPressRepetitionDelay;
  int  _pin;
  long _debounceDelay;
  int  _buttonState; // Debounced state
  int  _lastButtonState; // transitory state
  long _lastDebounceTime;
  long _lastLongPressTime;
  
  
};

#endif /* _BUTTON_ */
