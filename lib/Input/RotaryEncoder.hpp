#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include "A_Rotary.hpp"
#include "DebounceTimer.hpp"
#include "MemberFunction.hpp"
#include <Arduino.h>
#include <inttypes.h>

namespace Input {

class RotaryEncoder : public A_Rotary {
private:
  int previousClkReading = HIGH;

protected:
#ifndef ROTARY_DEBOUNCE
  DebounceTimer debounce{500};
#else
  DebounceTimer debounce{ROTARY_DEBOUNCE};
#endif

  const FunctionalInterrupts::MemberFunction<RotaryEncoder> UpdateFunction;

  void Update();

public:
  RotaryEncoder(int clkPin, int cclkPin, uint8_t steps);
  ~RotaryEncoder();

  void Reset() override;
};

} // namespace Input

#endif
