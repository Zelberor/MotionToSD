#include "AccurateRotaryEncoder.hpp"
#include "FunctionalInterrupts.hpp"
#include <Arduino.h>
#include <assert.h>

namespace Input {

void AccurateRotaryEncoder::ClkFall() {
  if (debounce.Blocked())
    return;

  if (cclkLow) {
    Decrement();
    cclkLow = false;
  } else {
    clkLow = true;
  }
  debounce.Set();
}
void AccurateRotaryEncoder::CClkFall() {
  if (debounce.Blocked())
    return;

  if (clkLow) {
    Increment();
    clkLow = false;
  } else {
    cclkLow = true;
  }
  debounce.Set();
}

AccurateRotaryEncoder::AccurateRotaryEncoder(int clkPin, int cclkPin,
                                             uint8_t steps)
    : A_Rotary(clkPin, cclkPin, steps),
      ClkFallFunction{&AccurateRotaryEncoder::ClkFall, *this},
      CClkFallFunction(&AccurateRotaryEncoder::CClkFall, *this) {
  assert(digitalPinToInterrupt(clkPin) != NOT_AN_INTERRUPT &&
         digitalPinToInterrupt(cclkPin) != NOT_AN_INTERRUPT &&
         "Clk and cclk pins have to support external interrupts.");
  pinMode(clkPin, INPUT);
  pinMode(cclkPin, INPUT);
  FunctionalInterrupts::attachFunctionalInterrupt(digitalPinToInterrupt(clkPin),
                                                  &ClkFallFunction, FALLING);
  FunctionalInterrupts::attachFunctionalInterrupt(
      digitalPinToInterrupt(cclkPin), &CClkFallFunction, FALLING);
}
AccurateRotaryEncoder::~AccurateRotaryEncoder() {
  FunctionalInterrupts::detachFunctionalInterrupt(
      digitalPinToInterrupt(clkPin));
  FunctionalInterrupts::detachFunctionalInterrupt(
      digitalPinToInterrupt(cclkPin));
}

void AccurateRotaryEncoder::Reset() {
  clkLow = false;
  cclkLow = false;
  position = 0;
  delta = 0;
  debounce.Reset();
}

} // namespace Input
