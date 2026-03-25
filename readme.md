# SKTimer

Lightweight, cross-platform C++ timer utility for embedded systems.
Provides simple abstractions for interval-based and one-shot timing using a unified tick interface.

## Features

* Minimal, header-only implementation
* Cross-platform support:

  * Arduino (`millis()`)
  * ESP-IDF (`esp_timer`)
  * STM32 (`HAL_GetTick`)
* No dynamic allocation
* Designed for deterministic embedded environments

## Supported Platforms

Platform is selected automatically via preprocessor:

| Platform | Tick Source                   | Resolution |
| -------- | ----------------------------- | ---------- |
| Arduino  | `millis()`                    | ms         |
| ESP-IDF  | `esp_timer_get_time() / 1000` | ms         |
| STM32    | `HAL_GetTick()`               | ms         |

---

## Installation

### ESP-IDF

Add as a component:

```cmake
idf_component_register(
    INCLUDE_DIRS "."
    REQUIRES esp_timer
)
```

Or via `idf_component.yml`:

```yaml
dependencies:
  sktimer:
    git: https://github.com/TheMechanos/SKTimer.git
```

### PlatformIO / Arduino

Add to `platformio.ini`:

```ini
lib_deps = https://github.com/TheMechanos/SKTimer.git
```

---

## Usage

Include the main header:

```cpp
#include "SKTimer.hpp"
```

---

## TimerInterval

Periodic timer that automatically resets after triggering.

### Example

```cpp
TimerInterval ledTimer(1000); // 1000 ms

void loop() {
    if (ledTimer.is()) {
        toggleLed();
    }
}
```

### API

```cpp
bool is();                      // returns true when interval elapsed
void reset();                   // manually reset timer
Tick_t getRemaining();          // remaining time [ms]
uint8_t getRemainingPercent();  // remaining time [%]
```

---

## TimerOneShot

One-time timer with optional single-return behavior.

### Example

```cpp
TimerOneShot timeout(5000, true); // start immediately

void loop() {
    if (timeout.is(true)) {
        handleTimeout(); // called only once
    }
}
```

### API

```cpp
void start();
void reset();
void restart();

bool is(bool returnOnceTime = false);

Tick_t getRemaining();
uint8_t getRemainingPercent();
```

### Behavior

* `is(false)` → returns `true` continuously after timeout
* `is(true)` → returns `true` only once

---

## Tick Abstraction

All timers rely on:

```cpp
Tick_t getTick();
```

Defined in `SKTimerPlatform.hpp`.

### Custom Platform

To port to another platform, define:

```cpp
typedef <your_type> Tick_t;
inline Tick_t getTick();
```

---

## Design Notes

* `Tick_t` is platform-dependent (`uint32_t` or `unsigned long`)
* No overflow handling abstraction — relies on natural wrap-around behavior of unsigned arithmetic
* Designed for low overhead (inline functions, no virtual dispatch)

---

## Limitations

* Millisecond resolution only
* No hardware timer integration
* No thread-safety guarantees

---

## Author

Sebastian Koczur
📧 [themechanos@gmail.com](mailto:themechanos@gmail.com)

---

## License

MIT
