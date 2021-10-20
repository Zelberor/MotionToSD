#ifndef MULTI_FUNCTION_H
#define MULTI_FUNCTION_H

#include "A_Function.hpp"
#include <assert.h>
#include <stdarg.h>

namespace FunctionalInterrupts {

template <int size> class MultiFunction : public A_Function {
private:
  const A_Function *functions[size];

public:
  MultiFunction<size>(const A_Function *function, ...) {
    assert(size > 0 && "MultiFunction size must be greater 0.");
    this->functions[0] = function;
    va_list vl;
    va_start(vl, function);
    for (int i = 1; i < size; ++i) {
      this->functions[i] = va_arg(vl, const A_Function *);
    }
    va_end(vl);
  }
  void operator()() const override {
    for (int i = 0; i < size; ++i) {
      (*functions[i])();
    }
  }
};

} // namespace FunctionalInterrupts

#endif
