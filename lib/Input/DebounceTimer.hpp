#ifndef DEBOUNCE_TIMER_H
#define DEBOUNCE_TIMER_H

namespace Input {

class DebounceTimer {
private:
  const unsigned long debounce;

  volatile unsigned long lastTime = 0;

public:
  DebounceTimer(unsigned long debounce = 500);
  bool Blocked() const;
  void Set();
  void Reset();
};

} // namespace Input

#endif
