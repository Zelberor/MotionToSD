#ifndef ACCURATE_ROTARY_ENCODER_H
#define ACCURATE_ROTARY_ENCODER_H

#include "A_Rotary.hpp"
#include "DebounceTimer.hpp"
#include "MemberFunction.hpp"

namespace Input {

class AccurateRotaryEncoder : public A_Rotary {
protected:
  volatile bool clkLow = false;
  volatile bool cclkLow = false;

  DebounceTimer debounce{};

  const FunctionalInterrupts::MemberFunction<AccurateRotaryEncoder>
      ClkFallFunction;
  const FunctionalInterrupts::MemberFunction<AccurateRotaryEncoder>
      CClkFallFunction;

  void ClkFall();
  void CClkFall();

public:
  AccurateRotaryEncoder(int clkPin, int cclkPin, uint8_t steps);
  ~AccurateRotaryEncoder();

  void Reset() override;
};

} // namespace Input

#endif
