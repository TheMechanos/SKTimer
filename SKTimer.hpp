/*
 * Timer.hpp
 *
 *  Created on: 30.11.2020
 *      Author: SHON
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "SKTimerPlatform.hpp"

namespace SK {

class TimerInterval {
public:
    TimerInterval(Tick_t interval)
        : interval(interval)
        , lastInterval(0) { }


    Tick_t getRemaining() { return interval - (getTick() - lastInterval); }

    uint8_t getRemainingPercent() { return getRemaining() * 100 / interval; }

    void reset() { lastInterval = getTick(); }

    bool is() {
        if (getTick() - lastInterval > interval) {
            lastInterval = getTick();
            return true;
        }
        return false;
    }


private:
    Tick_t interval;
    Tick_t lastInterval;
};


class TimerOneShot {
public:
    TimerOneShot(Tick_t oneShot, bool start = false)
        : oneShot(oneShot)
        , starts(NOT_SET) {
        if (start)
            this->start();
    }

    Tick_t getRemaining() {
        if (starts == NOT_SET)
            return 0;
        else
            return oneShot - (getTick() - starts);
    }

    uint8_t getRemainingPercent() { return getRemaining() * 100 / oneShot; }


    void start() {
        if (starts == NOT_SET)
            starts = getTick();
    }

    bool is(bool returnOnceTime = false) {

        if (starts != NOT_SET && getTick() > starts + oneShot) {

            if (returnOnceTime) {
                static bool returned = false;
                if (returned)
                    return false;
                else {
                    returned = true;
                    return true;
                }
            } else
                return true;
        }


        return false;
    }

private:
    constexpr static const Tick_t NOT_SET = -1;
    Tick_t oneShot;
    Tick_t starts;
};

}



#endif /* TIMER_HPP_ */
