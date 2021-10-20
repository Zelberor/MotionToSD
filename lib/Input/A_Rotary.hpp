#ifndef A_ROTARY_H
#define A_ROTARY_H

#include <inttypes.h>

namespace Input {

class A_Rotary {
protected:
  volatile uint8_t position = 0;
  volatile int16_t delta = 0;

  const int clkPin;
  const int cclkPin;
  const uint8_t steps;

  void Increment();
  void Decrement();

public:
  A_Rotary(int clkPin, int cclkPin, uint8_t steps);
  virtual void Reset() = 0;

  uint8_t Position() const;
  int16_t Delta();
};

} // namespace Input

#endif
