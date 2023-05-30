#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button {
  public:
    Button(int pin) {
      _pin = pin;
      pinMode(_pin, INPUT_PULLUP);
      _state = digitalRead(_pin);
      _lastState = _state;
      _lastDebounceTime = 0;
      _debounceDelay = 50;
    }
    bool quick_pressed(){
      if(digitalRead(_pin)== HIGH){
        return true;
      } else {
        return false;
      }

    };



    bool is_pressed() {
      int reading = digitalRead(_pin);
      if (reading != _lastState) {
        _lastDebounceTime = millis();
      }

      if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _state) {
          _state = reading;

          if (_state == LOW) {
            return true;
          }
        }
      }
      _lastState = reading;
      return false;
    }

  private:
    int _pin;
    int _state;
    int _lastState;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
};

#endif