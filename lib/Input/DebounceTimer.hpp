#ifndef DEBOUNCE_TIMER_H
#define DEBOUNCE_TIMER_H

namespace Input {

class DebounceTimer {
private:
#ifndef INPUT_DEBOUNCE
  const static unsigned long debounce = 2500;
#else
  const static unsigned long debounce = INPUT_DEBOUNCE;
#endif

  volatile unsigned long lastTime = 0;

public:
  DebounceTimer();
  bool Blocked() const;
  void Set();
  void Reset();
};

} // namespace Input

#endif
