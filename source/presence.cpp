/*
    presence.cpp -  presence sensor library
    Developed by Andrea Corrado & Eric Gowland

    Connect to a hardware device that is boolean present/not present. Such as PIR or Rangefinder with appropriate signalling.
    Also drives LED as presence indicator.
*/


#include "mbed-drivers/mbed.h"
#include "presence/presence.h"



presence::presence(PinName pin, bool true_on_rise, int debounce_time_ms):_myint(pin), _led1(LED1)
{
    debounce_ms = debounce_time_ms;
    _true_on_rise = true_on_rise;
//    if(true_on_rise) {
//        _myint.rise(this, &presence::presence_interrupt_off);
//        _myint.fall(this, &presence::presence_interrupt_on);
//    } else {
//        _myint.rise(this, &presence::presence_interrupt_on);
//        _myint.fall(this, &presence::presence_interrupt_off);
//    }
    _detection=false;
    debounce_timer.start();
    _led1=1;

}

void presence::presence_interrupt_off(){
    if(debounce_timer.read_ms() > debounce_ms) {
        _detection=false;
        _led1=1;
    }
}

void presence::presence_interrupt_on() //Detection of motion.
{
    //Always trigger detection..
    _detection=true;
    _led1=0;
    debounce_timer.reset(); // Reset counter to 0...
}


bool presence::isPresent(){
    bool new_detection = (_true_on_rise && _myint == 1) || (!_true_on_rise && _myint == 0);
    if(new_detection)debounce_timer.reset();
    //Poll the pin and update value...
    if(!_detection || debounce_timer.read_ms() > debounce_ms) {
        _detection = new_detection;
        if(_detection) _led1 = 0; else _led1 = 1;
    }
    return _detection;
}
