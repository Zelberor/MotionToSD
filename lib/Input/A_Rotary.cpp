#include "A_Rotary.hpp"
#include <limits.h>

namespace Input {

void A_Rotary::Increment() {
  position++;
  if (position == steps)
    position = 0;
  if (delta < INT16_MAX)
    ++delta;
}

void A_Rotary::Decrement() {
  if (position == 0)
    position = steps;
  --position;
  if (delta > INT16_MIN)
    --delta;
}

A_Rotary::A_Rotary(int clkPin, int cclkPin, uint8_t steps)
    : clkPin{clkPin}, cclkPin{cclkPin}, steps{steps} {}

uint8_t A_Rotary::Position() const { return position; }

int16_t A_Rotary::Delta() {
  int16_t result = delta;
  delta = 0;
  return result;
}

} // namespace Input
