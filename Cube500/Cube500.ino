// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FASTLED_FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FASTLED_FORCE_SOFTWARE_SPI
// #define FASTLED_FORCE_SOFTWARE_PINS
#include "common.h"

#include "demo1.h"
#include "cylon.h"
#include "flag.h"

int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status

// This function sets up the ledsand tells the controller about them
void setup() {
  setup_common();

  setup_demo1();
  setup_cylon();
  setup_flag();
  clear_strip();
  pinMode(17,INPUT);

}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
loop_demo1();
// clear_strip();
//
loop_cylon();
// clear_strip();

loop_flag();
//clear_strip();
  buttonState1 = digitalRead(16);
  buttonState2 = digitalRead(17);
  buttonState3 = digitalRead(20);

  if (buttonState1 == HIGH) {     
    // turn LED on:    
    //digitalWrite(17, HIGH); 
    Serial.println("BTN 17"); 
  } 
  if (buttonState2 == HIGH) {     
    // turn LED on:    
    //digitalWrite(17, HIGH); 
    Serial.println("BTN 16"); 
  } 
    if (buttonState3 == HIGH) {     
    // turn LED on:    
    //digitalWrite(17, HIGH); 
    Serial.println("BTN 20"); 
  } 
  delay(10);


}
