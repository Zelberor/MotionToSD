#ifndef DIRECT_DIGITAL_H
#define DIRECT_DIGITAL_H

#include <inttypes.h>

namespace DirectDigital {

void Setup();

void PinInit(uint8_t pin);

uint8_t Read(uint8_t pin);

void Write(uint8_t pin, uint8_t val);

} // namespace DirectDigital

#endif
