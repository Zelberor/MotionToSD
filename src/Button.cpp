#include "Button.h"
#include "ArrayFind.h"

namespace MotionToSD {

long Button::debounce = 200;
long Button::pressedTimeOut = 500;

Array<Button *, BUTTON_MAX_INTERRUPT_BUTTONS> Button::interruptInstances{};

void Button::OnInterruptChange() {
  for (size_t i = 0; i < interruptInstances.size(); ++i) {
    interruptInstances[i]->Update();
  }
}

Button::Button(int inPin)
    : interruptBased{digitalPinToInterrupt(inPin) != NOT_AN_INTERRUPT} {
  if (interruptBased) {
    attachInterrupt(digitalPinToInterrupt(inPin), Button::OnInterruptChange,
                    CHANGE);
    interruptInstances.push_back(this);
  }
  this->inPin = inPin;
  pinMode(inPin, INPUT);
  previousReading = digitalRead(inPin);
  Update();
}
Button::~Button() {
  if (interruptBased) {
    detachInterrupt(digitalPinToInterrupt(inPin));
    interruptInstances.remove(ArrayFind(interruptInstances, this));
  }
}

void Button::Update() {
  int currentReading = digitalRead(inPin);

  if (millis() - lastTime < debounce) {
    if (previousReading == LOW && currentReading == HIGH)
      pressed = true;

    lastTime = millis();
  }
  previousReading = currentReading;
}

bool Button::Pressed() {
  if (!interruptBased)
    Update();
  bool pressedState = pressed;
  pressed = false;
  return pressedState;
}

bool Button::Hold() { return (digitalRead(inPin) == LOW); }

} // namespace MotionToSD
