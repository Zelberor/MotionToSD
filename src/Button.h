#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "Array.h"
#include "pins_arduino.h"

namespace MotionToSD {

class Button {
private:
  int inPin;
  int previousReading;

  bool pressed = false;

  long lastTime = 0;
  const bool interruptBased;

  static long debounce;
  static long pressedTimeOut;

#ifndef BUTTON_MAX_INTERRUPT_BUTTONS
#error "BUTTON_MAX_INTERRUPT_BUTTONS not set!"
#endif
  static Array<Button *, BUTTON_MAX_INTERRUPT_BUTTONS> interruptInstances;

  static void OnInterruptChange();

  void Update();

public:
  Button(int inPin);
  ~Button();

  bool Pressed();
  bool Hold();
};

} // namespace MotionToSD

#endif
