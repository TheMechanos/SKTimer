#pragma once


#if defined(ARDUINO)

#include <Arduino.h>


typedef unsigned long Tick_t;
inline Tick_t getTick() { return millis(); }


#elif defined(ESP_PLATFORM)

#include <esp_timer.h>


typedef uint32_t Tick_t;
inline Tick_t getTick() { return esp_timer_get_time() / 1000; }



#elif defined(STM32C0)

#include <stm32c0xx_hal.h>

typedef uint32_t Tick_t;
inline Tick_t getTick() { return HAL_GetTick(); }


#endif
