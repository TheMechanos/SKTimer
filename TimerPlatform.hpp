#pragma once


#ifdef ARDUINO

#include <Arduino.h>
typedef unsigned long Tick_t;
inline Tick_t getTick() { return millis(); }

#endif