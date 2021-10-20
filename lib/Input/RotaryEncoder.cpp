#include "RotaryEncoder.hpp"
#include "FunctionalInterrupts.hpp"
#ifdef DIRECT_DIGITAL
#include "DirectDigital.hpp"
#endif
#include <Arduino.h>
#include <assert.h>

namespace Input {

void RotaryEncoder::Update() {
#ifdef DIRECT_DIGITAL
  int cclkState = DirectDigital::Read(cclkPin);
  int clkState = DirectDigital::Read(clkPin);
#else
  int cclkState = digitalRead(cclkPin);
  int clkState = digitalRead(clkPin);
#endif

  if (!debounce.Blocked() && clkState != previousClkReading) {
    if (cclkState != clkState)
      Increment();
    else
      Decrement();
    debounce.Set();
    previousClkReading = clkState;
  }
}

RotaryEncoder::RotaryEncoder(int clkPin, int cclkPin, uint8_t steps)
    : A_Rotary(clkPin, cclkPin, steps), UpdateFunction{&RotaryEncoder::Update,
                                                       *this} {
  assert(digitalPinToInterrupt(clkPin) != NOT_AN_INTERRUPT &&
         "Clk pin has to support external interrupts.");
  pinMode(clkPin, INPUT);
  pinMode(cclkPin, INPUT);
  FunctionalInterrupts::attachFunctionalInterrupt(digitalPinToInterrupt(clkPin),
                                                  &UpdateFunction, CHANGE);
}
RotaryEncoder::~RotaryEncoder() {
  FunctionalInterrupts::detachFunctionalInterrupt(
      digitalPinToInterrupt(clkPin));
}

void RotaryEncoder::Reset() {
  position = 0;
  delta = 0;
  debounce.Set();
}

} // namespace Input
