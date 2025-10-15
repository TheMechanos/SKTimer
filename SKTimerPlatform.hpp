#pragma once


#if defined(ARDUINO)

#include <Arduino.h>

namespace SK {
typedef unsigned long Tick_t;
inline Tick_t getTick() { return millis(); }
}

#elif defined(ESP_PLATFORM)

#include <esp_timer.h>

namespace SK {
typedef uint32_t Tick_t;
inline Tick_t getTick() { return esp_timer_get_time() / 1000; }
}


#endif
