#ifndef CALLBACK_BUTTON_H
#define CALLBACK_BUTTON_H

#include "Button.hpp"
#include "FunctionalInterrupts/A_Function.hpp"

namespace Input {

class CallbackButton : public Button {

protected:
  const FunctionalInterrupts::A_Function *CallbackFunction;

  void Update() override;

public:
  CallbackButton(int inPin, const FunctionalInterrupts::A_Function &callback);
};

} // namespace Input

#endif
