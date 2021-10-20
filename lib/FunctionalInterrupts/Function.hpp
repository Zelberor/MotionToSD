#ifndef FUNCTION_H
#define FUNCTION_H

#include "A_Function.hpp"

namespace FunctionalInterrupts {

void nothing(void);

class Function : public A_Function {
private:
  void (*const funcPtr)();

public:
  Function(void (*funPtr)());
  void operator()() const override;

  const static Function Nothing;
};

} // namespace FunctionalInterrupts

#endif
