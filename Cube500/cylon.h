#include "common.h"

//CRGB leds[NB_LEDS_TOTAL];

void setup_cylon() {
  Serial.println("Cylon setup done");

}

void fadeall() {
  for (int i = 0; i < NB_LEDS_TOTAL; i++) {
    getLeds(i)->nscale8(250);
  }
}


void loop_cylon() {
  Serial.println("Run Cylon");
  static uint8_t hue = 0;
  Serial.println("   go");
  // First slide theled in one direction
  for (int i = 0; i < NB_LEDS_TOTAL; i++) {
    // Set the i'th led to red
    setLeds(i, CHSV(hue++, 255, 255));
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  Serial.println("  back");

  for (int i = (NB_LEDS_TOTAL) - 1; i >= 0; i--) {
    // Set the i'th led to red
    setLeds(i, CHSV(hue++, 255, 255));
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }

}
