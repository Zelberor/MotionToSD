#include "Button.hpp"
#include "FunctionalInterrupts.hpp"
#include <Arduino.h>

namespace Input {

void Button::Update() {
  currentReading = digitalRead(inPin);
  unsigned long currentTime = millis();

  if (!debounce.Blocked()) {
    if (previousReading == HIGH && currentReading == LOW) {
      pressed = true;
      pressedTime = currentTime;
      debounce.Set();
    }
    if (previousReading == LOW && currentReading == HIGH) {
      released = true;
      releasedTime = currentTime;
      debounce.Set();
    }
    previousReading = currentReading;
  }
}

Button::Button(int inPin, bool internalPullUp)
    : inPin(inPin), interruptBased{digitalPinToInterrupt(inPin) !=
                                   NOT_AN_INTERRUPT},
      UpdateFunction{&Button::Update, *this} {
  pinMode(inPin, internalPullUp ? INPUT_PULLUP : INPUT);
  previousReading = digitalRead(inPin);
  Update();
  if (interruptBased) {
    FunctionalInterrupts::attachFunctionalInterrupt(
        digitalPinToInterrupt(inPin), &UpdateFunction, CHANGE);
  }
}
Button::~Button() {
  if (interruptBased) {
    FunctionalInterrupts::detachFunctionalInterrupt(
        digitalPinToInterrupt(inPin));
  }
}

void Button::Reset() {
  currentReading = digitalRead(inPin);
  previousReading = currentReading;
  pressedTime = 0;
  releasedTime = 0;
  released = false;
  pressed = false;
  debounce.Reset();
}

bool Button::Pressed() {
  if (!interruptBased) {
    Update();
  }
  unsigned long currentTime = millis();
  if (pressed && currentTime - pressedTime < eventTimeOut) {
    pressed = false;
    return true;
  }
  return false;
}

bool Button::Hold() {
  if (!interruptBased)
    Update();
  return (currentReading == LOW);
}

bool Button::Released() {
  if (!interruptBased)
    Update();
  unsigned long currentTime = millis();
  if (released && currentTime - releasedTime < eventTimeOut) {
    released = false;
    return true;
  }
  return false;
}

} // namespace Input
