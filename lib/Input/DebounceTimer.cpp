#include "DebounceTimer.hpp"
#include "Arduino.h"
#include "limits.h"

namespace Input {

DebounceTimer::DebounceTimer() {}

bool DebounceTimer::Blocked() const {
  unsigned long currentTime = micros();
  if (lastTime > currentTime) {
    if (ULONG_MAX - lastTime + currentTime > debounce)
      return false;
  } else {
    if (currentTime - lastTime > debounce)
      return false;
  }
  return true;
}

void DebounceTimer::Set() { lastTime = micros(); }

void DebounceTimer::Reset() { lastTime = 0; }

} // namespace Input
