#include "Button.hpp"
#include "Arduino.h"
#include "FunctionalInterrupts/FunctionalInterrupts.hpp"

namespace Input {

long Button::debounce = 100;
long Button::pressedTimeOut = 1000;

void Button::Update() {
  currentReading = digitalRead(inPin);
  long currentTime = millis();

  if (currentTime - lastTime > debounce) {
    if (previousReading == HIGH && currentReading == LOW) {
      pressed = true;
      lastTime = currentTime;
      pressedTime = currentTime;
    }
  }
  if (previousReading == LOW && currentReading == HIGH)
    lastTime = currentTime;
  previousReading = currentReading;
}

Button::Button(int inPin)
    : inPin(inPin), interruptBased{digitalPinToInterrupt(inPin) !=
                                   NOT_AN_INTERRUPT},
      UpdateFunction{&Button::Update, *this} {
  if (interruptBased) {
    FunctionalInterrupts::attachFunctionalInterrupt(
        digitalPinToInterrupt(inPin), &UpdateFunction, CHANGE);
  }
  pinMode(inPin, INPUT);
  previousReading = digitalRead(inPin);
  Update();
}
Button::~Button() {
  if (interruptBased) {
    FunctionalInterrupts::detachFunctionalInterrupt(
        digitalPinToInterrupt(inPin));
  }
}

bool Button::Pressed() {
  if (!interruptBased) {
    Update();
  }
  long currentTime = millis();
  if (pressed && currentTime - pressedTime < pressedTimeOut) {
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

} // namespace Input
