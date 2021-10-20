#ifndef BUTTON_H
#define BUTTON_H

#include "DebounceTimer.hpp"
#include "MemberFunction.hpp"

namespace Input {

class Button {
private:
  volatile int previousReading;
  volatile int currentReading;

  volatile unsigned long pressedTime = 0;
  volatile unsigned long releasedTime = 0;

  DebounceTimer debounce{};

#ifndef BUTTON_EVENT_TIMEOUT
  const static unsigned long eventTimeOut = 1000;
#else
  const static unsigned long eventTimeOut = BUTTON_EVENT_TIMEOUT;
#endif

protected:
  volatile bool pressed = false;
  volatile bool released = false;

  const int inPin;
  const bool interruptBased;
  const FunctionalInterrupts::MemberFunction<Button> UpdateFunction;

  virtual void Update();

public:
  Button(int inPin, bool internalPullUp = true);
  ~Button();

  void Reset();

  bool Pressed();
  bool Hold();
  bool Released();
};

} // namespace Input

#endif
