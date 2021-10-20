#include "CallbackButton.hpp"

namespace Input {

void CallbackButton::Update() {
  Button::Update();
  if (pressed && !callBackExecuted) {
    (*CallbackFunction)();
    callBackExecuted = true;
  } else if (released) {
    callBackExecuted = false;
  }
}

CallbackButton::CallbackButton(int inPin,
                               const FunctionalInterrupts::A_Function &callback,
                               bool internalPullUp)
    : Button{inPin, internalPullUp}, CallbackFunction{&callback} {}

} // namespace Input
