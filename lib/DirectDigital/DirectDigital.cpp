#include "DirectDigital.hpp"
#include "DigitalMapping.hpp"
#include <Arduino.h>

namespace DirectDigital {

void Setup() {
  for (uint8_t i = 0; i < pinInfos_size; ++i) {
    uint8_t port = digitalPinToPort(i);
    if (port == NOT_A_PIN)
      continue;
    pinInfos[i].portInputRegister = portInputRegister(port);
    pinInfos[i].portOutputRegister = portOutputRegister(port);
    pinInfos[i].bitMask = digitalPinToBitMask(i);
  }
}

void PinInit(uint8_t pin) {
  uint8_t timer = digitalPinToTimer(pin);
  if (timer != NOT_ON_TIMER)
    digitalRead(pin);
}

uint8_t Read(uint8_t pin) {
  return (*(pinInfos[pin].portInputRegister) & pinInfos[pin].bitMask) ? HIGH
                                                                      : LOW;
}

void Write(uint8_t pin, uint8_t val) {
  uint8_t oldSREG = SREG;
  cli();

  if (val == LOW) {
    *(pinInfos[pin].portOutputRegister) &= ~pinInfos[pin].bitMask;
  } else {
    *(pinInfos[pin].portOutputRegister) |= pinInfos[pin].bitMask;
  }

  SREG = oldSREG;
}

} // namespace DirectDigital
