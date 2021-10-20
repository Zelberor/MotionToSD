#ifndef DIGITAL_MAPPING_H
#define DIGITAL_MAPPING_H

#include <inttypes.h>
#include <pins_arduino.h>

#define DIRECT_DIGITAL_PININFOS_SIZE NUM_DIGITAL_PINS

namespace DirectDigital {

struct PinInfo {
public:
  volatile uint8_t *portInputRegister{nullptr};
  volatile uint8_t *portOutputRegister{nullptr};
  uint8_t bitMask{0};
};

extern PinInfo pinInfos[];

extern const uint8_t pinInfos_size;

} // namespace DirectDigital

#endif
