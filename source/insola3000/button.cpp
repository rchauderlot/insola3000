
#include "button.h"

Button::Button(int pin, void(*buttonPressedCallback)(void), long debounceDelay) {

  _pin = pin;
  _buttonPressedCallback = buttonPressedCallback;
  _debounceDelay = debounceDelay;
  _lastDebounceTime = 0;
  _buttonState = LOW;
  _lastButtonState = LOW;
  pinMode(_pin, INPUT);
}

void Button::update() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(_pin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != _lastButtonState) {
    // reset the debouncing timer
    _lastDebounceTime = millis();
  } 
  
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    // If a up to down transition detected call the pressed calback
    if (_buttonState == HIGH && reading == LOW) {
      _buttonPressedCallback();
    }
 
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    _buttonState = reading;
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  _lastButtonState = reading;

}
