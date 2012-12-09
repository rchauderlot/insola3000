
#include "button.h"

Button::Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay) {

  _pin = pin;
  _buttonPressedCallback = buttonPressedCallback;
  _buttonLongPressedCallback = 0;
  _debounceDelay = debounceDelay;
  _lastDebounceTime = 0;
  _buttonState = LOW;
  _lastButtonState = LOW;
  _longPressRepetitionDelay = 0;
  _lastLongPressTime = 0;

  pinMode(_pin, INPUT);
}

Button::Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay, void(*buttonLongPressedCallback)(void), long longPressRepetitionDelay) {
  _pin = pin;
  _buttonPressedCallback = buttonPressedCallback;
  _buttonLongPressedCallback = buttonPressedCallback;
  _debounceDelay = debounceDelay;
  _lastDebounceTime = 0;
  _buttonState = LOW;
  _lastButtonState = LOW;
  _longPressRepetitionDelay = longPressRepetitionDelay;
  _lastLongPressTime = 0;
  pinMode(_pin, INPUT);
}

void Button::update() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(_pin);
  long readingTime = millis();

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != _lastButtonState) {
    // reset the debouncing timer
    _lastDebounceTime = readingTime;
  } 
  
  if ((readingTime - _lastDebounceTime) > _debounceDelay) {
    // If a up to down transition detected call the pressed calback
    if (_buttonState == HIGH && reading == LOW) {
      if (!_buttonLongPressedCallback) {
        _buttonPressedCallback();
      } else if (_longPressRepetitionDelay == 0)  {
        _buttonLongPressedCallback();
      }
    }
    
   // If a up high transition detected call 
   if (_buttonLongPressedCallback && _longPressRepetitionDelay > 0 && _buttonState == LOW && reading == HIGH) {
      _lastLongPressTime = readingTime;
    }
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    _buttonState = reading;
  }
  
  if (_buttonLongPressedCallback && _longPressRepetitionDelay > 0 && (readingTime - _lastLongPressTime) > _longPressRepetitionDelay) {
    _buttonLongPressedCallback();
    _lastLongPressTime = readingTime;
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  _lastButtonState = reading;

}
