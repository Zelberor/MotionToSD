#ifndef A_FUNCTION_H
#define A_FUNCTION_H

namespace FunctionalInterrupts {

class A_Function {
public:
  virtual void operator()() const = 0;
};

} // namespace FunctionalInterrupts

#endif
