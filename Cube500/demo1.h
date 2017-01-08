#include "common.h"


#define DELAY 200

CRGB colors[10];
void setup_demo1() {
//  FastLED.addLeds<WS2812B, DATA_PIN_SIDE, GRB>(leds_side, NUM_LEDS_SIDE);
//  FastLED.addLeds<WS2812B, DATA_PIN_TOP, GRB>(leds_top, NUM_LEDS_TOP);

  colors[0] = CRGB::Yellow;
  colors[1] = CRGB::Red;
  colors[2] = CRGB::DeepPink;
  colors[3] = CRGB::Purple;
  colors[4] = CRGB::YellowGreen;
  colors[5] = CRGB::RoyalBlue;
  colors[6] = CRGB::Tomato;
  colors[7] = CRGB::FloralWhite;
  colors[8] = CRGB::Cyan;
  colors[9] = CRGB::Aquamarine;
  Serial.println("Demo 1 setup done");
}


void fill_column_side(int c, const struct CRGB &color) {
  for (int i = 0; i < MATRIX_SIDE_HEIGHT; i++) {
    mLeds_side(c+(40 * i)) = color;
  }
}

void fill_column_top(int c, const struct CRGB &color) {
  for (int i = 0; i < MATRIX_TOP_HEIGHT; i++) {
    mLeds_top(c+(10 * i)) = color;
  }
}

void demo1_1_side() {
  for (int i = 0 ; i < NUM_LEDS_SIDE ; i = i+MATRIX_SIDE_WIDTH) {
    fill_solid(mLeds_side[i], MATRIX_SIDE_WIDTH, colors[i / 40]);
    FastLED.show();
    delay(DELAY);
    fill_solid(mLeds_side[i], MATRIX_SIDE_WIDTH, CRGB::Black);
  }
}

void demo1_1_top() {  
  for (int i = 0 ; i < NUM_LEDS_TOP ; i += MATRIX_TOP_WIDTH) {
    fill_solid(mLeds_top[i], MATRIX_TOP_WIDTH, colors[i / 10]);
    FastLED.show();
    delay(DELAY);
    fill_solid(mLeds_top[i], MATRIX_TOP_WIDTH, CRGB::Black);
  }
}

void demo1_2_side() {
  for (int i = 0 ; i < MATRIX_SIDE_WIDTH ; i++) {
    fill_column_side(i, colors[i % 10]);
    FastLED.show();
    delay(DELAY);
    fill_column_side(i, CRGB::Black);
  }
}


void demo1_2_top() {
  for (int i = 0 ; i < MATRIX_TOP_HEIGHT ; i++) {
    fill_column_top(i, colors[i]);
    FastLED.show();
    delay(DELAY);
    fill_column_top(i, CRGB::Black);
  }
}

void demo1_3_top() {
  for (int i = 0 ; i < MATRIX_TOP_HEIGHT ; i++) {
    fill_column_top(i, colors[i % 10]);
    FastLED.show();
    delay(DELAY);
    fill_column_top(i, CRGB::Black);
  }
}


void loop_demo1() {
  Serial.println("Run demo 1");
  demo1_1_side();
  demo1_1_top();
  demo1_2_side();
  demo1_2_top();
}

