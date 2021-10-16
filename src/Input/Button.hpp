#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "FunctionalInterrupts/MemberFunction.hpp"
#include "pins_arduino.h"

namespace Input {

class Button {
private:
  volatile int previousReading;
  volatile int currentReading;

  volatile long lastTime = 0;
  volatile long pressedTime = 0;

  static long debounce;
  static long pressedTimeOut;

protected:
  volatile bool pressed = false;

  const int inPin;
  const bool interruptBased;
  const FunctionalInterrupts::MemberFunction<Button> UpdateFunction;

  virtual void Update();

public:
  Button(int inPin, bool internalPullUp = true);
  ~Button();

  bool Pressed();
  bool Hold();
};

} // namespace Input

#endif
