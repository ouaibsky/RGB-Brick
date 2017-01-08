#ifndef __INC_COMMON_CUBE_H
#define __INC_COMMON_CUBE_H

#include "FastLED.h"
#include <LEDMatrix.h>

// How many leds are in the strip - TOP
#define CUBE_WIDTH 10
#define MATRIX_TOP_WIDTH CUBE_WIDTH
#define MATRIX_TOP_HEIGHT CUBE_WIDTH
#define NUM_LEDS_TOP (MATRIX_TOP_WIDTH * MATRIX_TOP_HEIGHT)

// How many leds are in the strip - SIDE
#define MATRIX_SIDE_WIDTH 40
#define MATRIX_SIDE_HEIGHT CUBE_WIDTH
#define NUM_LEDS_SIDE (MATRIX_SIDE_WIDTH * MATRIX_SIDE_HEIGHT)

#define NB_LEDS_TOTAL (NUM_LEDS_TOP+NUM_LEDS_SIDE)

#define DATA_PIN_TOP 3
#define DATA_PIN_SIDE 5

//#define COLOR_ORDER GRB
//#define CHIPSET     WS2812B

#define MATRIX_TYPE_TOP    HORIZONTAL_ZIGZAG_MATRIX  // See top of LEDMatrix.h for matrix wiring types
#define MATRIX_TYPE_SIDE    HORIZONTAL_MATRIX  // See top of LEDMatrix.h for matrix wiring types

cLEDMatrix<MATRIX_TOP_WIDTH, MATRIX_TOP_HEIGHT, MATRIX_TYPE_TOP> mLeds_top;
cLEDMatrix<MATRIX_SIDE_WIDTH, MATRIX_SIDE_HEIGHT, MATRIX_TYPE_SIDE> mLeds_side;
//
//struct CRGB allLeds[NB_LEDS_TOTAL];


// Params for width and height
//const uint8_t MatricWidthTop = 10;
//const uint8_t MatrixHeight = 10;
//const uint8_t MatricWidthSide = 40;
const bool    MatrixSerpentineLayoutTop = true;
const bool    MatrixSerpentineLayoutSide = false;

void setup_common() {
  Serial.begin(9600);
  delay(1000);
  LEDS.addLeds<WS2812B, DATA_PIN_SIDE, GRB>(mLeds_side[0], NUM_LEDS_SIDE); //.setCorrection(TypicalWS2812B);
  LEDS.addLeds<WS2812B, DATA_PIN_TOP, GRB>(mLeds_top[0], NUM_LEDS_TOP); //.setCorrection(TypicalSMD5050);

//  for (int i = 0 ; i < NUM_LEDS_SIDE; i++) {
//    allLeds[i] = mLeds_side(i);
//  }
//  for (int i = 0 ; i < NUM_LEDS_TOP; i++) {
//    allLeds[NUM_LEDS_SIDE + i] = mLeds_top(i);
//  }

  for (int i = 0 ; i < NUM_LEDS_TOP; i++) {
    mLeds_top(i) = CRGB::Yellow;
  }
  LEDS.setBrightness(128);
  FastLED.show();
  delay(2000);
  Serial.println("Common setup done");
}

void setLeds(int16_t x, struct CRGB color) {
  int16_t xSafe = x % NB_LEDS_TOTAL;
  if (xSafe < NUM_LEDS_SIDE) {
    mLeds_side(xSafe) = color;
  } else {
    mLeds_top(xSafe-NUM_LEDS_SIDE) = color;
  }
}

struct CRGB* getLeds(int x) {
  int16_t xSafe = x % NB_LEDS_TOTAL;

  if (xSafe < NUM_LEDS_SIDE) {
    return mLeds_side[xSafe];
  }
  return mLeds_top[xSafe-NUM_LEDS_SIDE];
}

void clear_top() {
  for (int i = 0 ; i < NUM_LEDS_TOP; i++) {
    mLeds_top(i) = CRGB::Black;
  }
}

void clear_side() {
  for (int i = 0 ; i < NUM_LEDS_SIDE; i++) {
    mLeds_side(i) = CRGB::Black;
  }
}

void clear_strip() {
  FastLED.clear();
  FastLED.show();
}

#endif

