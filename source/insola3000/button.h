#ifndef _BUTTON_
#define _BUTTON_


#include "Arduino.h"

class Button {

public:

  Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay);
  void update();
    
private:

  void (*_buttonPressedCallback)(void);
  int  _pin;
  long _debounceDelay;
  int  _buttonState; // Debounced state
  int  _lastButtonState; // transitory state
  long _lastDebounceTime;

};

#endif /* _BUTTON_ */
