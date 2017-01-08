#include "common.h"

void setup_flag() {
  Serial.println("Flag setup done");
}

void flag_france_side() {
  for (int x = 0 ; x < CUBE_WIDTH; x++) {
    mLeds_side.DrawFilledRectangle(0, 0, 2, 9, CRGB::Blue);
    mLeds_side.DrawFilledRectangle(3, 0, 6, 9, CRGB::White);
    mLeds_side.DrawFilledRectangle(7, 0, 9, 9, CRGB::Red);
  }
}

void flag_france_top() {
  mLeds_top.DrawFilledRectangle(0, 0, 2, 9, CRGB::Blue);
  mLeds_top.DrawFilledRectangle(3, 0, 6, 9, CRGB::White);
  mLeds_top.DrawFilledRectangle(7, 0, 9, 9, CRGB::Red);
}

void france() {
  Serial.println("  France ");
  flag_france_side();
  flag_france_top();
  FastLED.show();
  delay(1000);
  for (int i = 0; i < MATRIX_SIDE_WIDTH; i++) {
    mLeds_side.ShiftRight();
    //mLeds_top.VerticalMirror();
    FastLED.show();
    delay(200);
  }
}

void loop_flag() {
  Serial.println("Run Flag ");
  france();
}
