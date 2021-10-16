#ifndef FUNCTIONAL_INTERRUPTS_H
#define FUNCTIONAL_INTERRUPTS_H

#include "A_Function.hpp"
#include "inttypes.h"

namespace FunctionalInterrupts {

void attachFunctionalInterrupt(uint8_t interruptNum, const A_Function *function,
                               int mode);
void detachFunctionalInterrupt(uint8_t interruptNum);

} // namespace FunctionalInterrupts

#endif
