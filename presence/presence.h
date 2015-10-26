/*
    presence.cpp -  presence sensor library
    Developed by Andrea Corrado & Eric Gowland

    Connect to a hardware device that is boolean present/not present. Such as PIR or Rangefinder with appropriate signalling.
    Also drives LED as presence indicator.
*/

#ifndef MBED_PIR_H
#define MBED_PIR_H

#include "mbed-drivers/mbed.h"

class presence{

public:

    presence(PinName pin, bool true_on_rise, int debounce_time_ms);
    bool isPresent();

private:
    InterruptIn _myint;
    DigitalOut _led1;
    bool _detection;
    bool _true_on_rise;
    int debounce_ms;
    Timer debounce_timer;
    void presence_interrupt_on();
    void presence_interrupt_off();

};

#endif
