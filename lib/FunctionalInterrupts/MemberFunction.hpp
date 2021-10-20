#ifndef MEMBER_FUNCTION_H
#define MEMBER_FUNCTION_H

#include "A_Function.hpp"

namespace FunctionalInterrupts {

template <class T> class MemberFunction : public A_Function {
private:
  void (T::*const memberFuncPtr)();
  T &object;

public:
  MemberFunction<T>(void (T::*memberFuncPtr)(), T &object)
      : memberFuncPtr(memberFuncPtr), object(object) {}
  void operator()() const override { (object.*memberFuncPtr)(); }
};

} // namespace FunctionalInterrupts

#endif
