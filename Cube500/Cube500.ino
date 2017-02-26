// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FASTLED_FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FASTLED_FORCE_SOFTWARE_SPI
// #define FASTLED_FORCE_SOFTWARE_PINS
#include "common.h"

#include "demo1.h"
#include "cylon.h"
#include "flag.h"

// This function sets up the ledsand tells the controller about them
void setup() {
  setup_common();

  setup_demo1();
  setup_cylon();
  setup_flag();
  clear_strip();


}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
//loop_demo1();
// clear_strip();
//
//loop_cylon();
// clear_strip();

loop_flag();
clear_strip();

  read_button();
  //delay(10);


}
