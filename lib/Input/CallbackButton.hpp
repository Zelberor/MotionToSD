#ifndef CALLBACK_BUTTON_H
#define CALLBACK_BUTTON_H

#include "A_Function.hpp"
#include "Button.hpp"

namespace Input {

class CallbackButton : public Button {
private:
  volatile bool callBackExecuted = false;

protected:
  const FunctionalInterrupts::A_Function *CallbackFunction;

  void Update() override;

public:
  CallbackButton(int inPin, const FunctionalInterrupts::A_Function &callback,
                 bool internalPullUp = true);
};

} // namespace Input

#endif
