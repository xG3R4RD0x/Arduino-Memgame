#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button {
  public:
    Button(int pin) {
      _pin = pin;
      pinMode(_pin, INPUT_PULLUP);
      _lastButtonState = HIGH;
      _lastDebounceTime = 0;
      _debounceDelay = 50;
    }

    bool is_pressed() {
      int buttonState = digitalRead(_pin);
      if (buttonState != _lastButtonState) {
        _lastDebounceTime = millis();
      }

      if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (buttonState != _buttonState) {
          _buttonState = buttonState;

          if (_buttonState == LOW) {
            return true;
          }
        }
      }
      _lastButtonState = buttonState;
      return false;
    }

  private:
    int _pin;
    int _buttonState;
    int _lastButtonState;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
};

#endif
