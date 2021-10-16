#include "Function.hpp"

namespace FunctionalInterrupts {

void nothing(void) {}

Function::Function(void (*funcPtr)()) : funcPtr{funcPtr} {}
void Function::operator()() const { funcPtr(); }

const Function Function::Nothing{nothing};

} // namespace FunctionalInterrupts
