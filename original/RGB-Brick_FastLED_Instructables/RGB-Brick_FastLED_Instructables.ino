#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontMatrise.h>
#include <LEDSprites.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Audio.h>
//dht -> 16 (A2)



// GUItool: begin automatically generated code
AudioPlaySdWav           wavEffects;
AudioInputI2S            audioInput;
AudioOutputI2S           audioOutput;
AudioMixer4              mixerInput;
AudioAnalyzeFFT1024      fft;
AudioAnalyzePeak         peak1;

AudioConnection          patchCord5(wavEffects, 0, audioOutput, 1);
AudioConnection          patchCord6(wavEffects, 1, audioOutput, 0);

AudioConnection          patchCord7(audioInput, 0, mixerInput, 0);
AudioConnection          patchCord8(audioInput, 1, mixerInput, 1);
AudioConnection          patchCord9(mixerInput, fft);
AudioConnection          patchCord10(mixerInput, peak1);

AudioControlSGTL5000     audioShield;

const int nSoundeffects = 10;
const char * soundeffects[10] = { "COIN.WAV", "COIN2.WAV", "BOSSFIGHT.WAV", "BONUS.WAV", "JUMP.WAV",
                                  "PITCH.WAV",  "GAMEOVER.WAV", "HUNGERGAMES.WAV", "LEVELUP.WAV", "SUCCESS.WAV"
                                };
boolean playeffects = false;

float fft_values[40];
int fft_show[40];
float peak;
int peak_show;
byte xx1, yy1, bb1;
float vol = 0.5;

uint16_t gradient = 0;
uint8_t volume = 0, last = 0;
float maxVol = 15;
float avgVol = 0;
float avgBump = 0;
bool bump = false;
#define LED_TOTAL 15
#define LED_HALF  7

const int nMusicVisualiser = 2;
int musicVisualiser = 1;


#define esp Serial1

#define COLOR_ORDER            GRB
#define CHIPSET                WS2812B

#define LED_PIN_TOP            3
#define MATRIX_WIDTH_TOP       10
#define MATRIX_HEIGHT_TOP      10
#define MATRIX_TYPE_TOP        HORIZONTAL_ZIGZAG_MATRIX

#define LED_PIN_BOTTOM         5
#define MATRIX_WIDTH_BOTTOM    40
#define MATRIX_HEIGHT_BOTTOM   10
#define MATRIX_TYPE_BOTTOM     HORIZONTAL_MATRIX

cLEDMatrix < MATRIX_WIDTH_TOP, MATRIX_HEIGHT_TOP, MATRIX_TYPE_TOP > matrix_top;
cLEDMatrix < MATRIX_WIDTH_BOTTOM, MATRIX_HEIGHT_BOTTOM, MATRIX_TYPE_BOTTOM > matrix_bottom;


//SNAKE
//wie lang kann die Snake maximal werden
const int anzahlPixel = 500;
byte SnakeItems = 0;
byte oldSnakeItems = 0;
//groesse des Spielfeldes
#define BaneGridXmax 50
#define BaneGridYmax 10
//Snakeitems
byte oldSnakeItemPosX[anzahlPixel];
byte oldSnakeItemPosY[anzahlPixel];
byte SnakeItemPosX[anzahlPixel];
byte SnakeItemPosY[anzahlPixel];
//Position des Apples
byte ApplePosX;
byte ApplePosY;
//Farben der 3 Arten
#define BLANK 0
#define SNAKE 1
#define APPLE 2
//Spielfeld
byte Playfield[BaneGridXmax + 1][BaneGridYmax + 1];
byte SnakeHeadID = 0;
byte SnakeBackID = 0;
byte AppleCount = 0;
//define Richtungen
#define SNAKE_RIGHT 0
#define SNAKE_LEFT 1
#define SNAKE_UP 2
#define SNAKE_DOWN 3
//Laufrichtungen
byte movingDirection = SNAKE_RIGHT;
byte snakeDirection = SNAKE_RIGHT;
byte AddSnakeItem = 0;
//eins addieren wenn apple gefunden
byte SnakeItemsToAddAtApple = 1;
//snakespeed
#define SNAKESPEED_BEGIN 200
int snakespeed = SNAKESPEED_BEGIN;
int snakespeedmax = 20;
//spiel laeuft
boolean snakerun = false;
boolean snakeOntop = false;
unsigned long SnakeScore = 0;
unsigned long SnakeHighscore = 0;
const unsigned int ScoreEEPROMaddress = 100;



//Tetris
#define TETRIS_WIDTH 10
#define TETRIS_HIGHT 20
boolean tetrisrun = false;
int tetrisspeed = 400;
byte PlayfieldTetris[TETRIS_WIDTH][TETRIS_HIGHT];
byte Block[TETRIS_WIDTH][TETRIS_HIGHT + 2];
byte Pile[TETRIS_WIDTH][TETRIS_HIGHT];

int currentblock = 0;
int currentrotation = 0;

boolean blockflying = false;

const struct CRGB TetrisColor[] = {CRGB(0, 0, 0), CRGB(0, 255, 255), CRGB(0, 0, 255), CRGB(255, 165, 0), CRGB(255, 255, 0),
        CRGB(50, 205, 50), CRGB(255, 0, 255), CRGB(255, 0, 0), CRGB(255, 255, 255)
};
#define TETRIS_BLACK 0
#define TETRIS_WHITE 8
byte blockcolor[] = {0, 1, 2, 3, 4, 5, 6, 7};

int TetrisScore = 0;
int TetrisHighScore = 0;




boolean doSnake = false;
boolean doTetris = false;
boolean doText = false;
boolean doAnimation = false;
boolean doFire = false;
boolean doNoise = false;
boolean doMusic = false;


const int nAnimation = 4;
int animation = 1;

boolean NoisePalette = false;
int paletteH[4] = {0};
int paletteS[4] = {0};
int paletteV[4] = {0};

int wait = 50;
int Brightness = 200, Saturation = 255;

cLEDText scrollingtext;
#define MAX_BUFFER  100
unsigned char TextBuffer[MAX_BUFFER];


static uint16_t x;
static uint16_t y;
static uint16_t z;
uint16_t speed = 20;
uint16_t scale = 30;
uint8_t noise[MATRIX_WIDTH_BOTTOM + MATRIX_WIDTH_TOP][MATRIX_HEIGHT_BOTTOM];
CRGBPalette16 currentPalette( PartyColors_p );
uint8_t colorLoop = 1;
int palette = 0;
int maxpalette = 11;

CRGBPalette16 gPal;


#define SQUARE_WIDTH    7
#define SQUARE_HEIGHT   7
const uint8_t SquareData1[] =
{
  B8_2BIT(11111110),
  B8_2BIT(12222210),
  B8_2BIT(12333210),
  B8_2BIT(12333210),
  B8_2BIT(12333210),
  B8_2BIT(12222210),
  B8_2BIT(11111110)
};
const uint8_t SquareMask1[] =
{
  B8_2BIT(11111110),
  B8_2BIT(11111110),
  B8_2BIT(11111110),
  B8_2BIT(11111110),
  B8_2BIT(11111110),
  B8_2BIT(11111110),
  B8_2BIT(11111110)
};
cLEDSprites Sprites(&matrix_bottom);
#define MAX_SQUARES  8
#define NUM_COLS  3
cSprite Shape1[MAX_SQUARES];
struct CRGB ColTabs[MAX_SQUARES][NUM_COLS];
int NumSquares;


#define SHAPE_WIDTH    5
#define SHAPE_HEIGHT   5
const uint8_t ShapeData2[] =
{
  B8_1BIT(00100000),
  B8_1BIT(01110000),
  B8_1BIT(11111000),
  B8_1BIT(01110000),
  B8_1BIT(00100000),
};
struct CRGB ColTable[1] = { CRGB(64, 128, 255) };
cSprite Shape2(SHAPE_WIDTH, SHAPE_HEIGHT, ShapeData2, 1, _1BIT, ColTable, ShapeData2);

#define COOLING  55
#define SPARKING 120
bool gReverseDirection = false;

uint8_t hue;








void setup() {

  AudioMemory(48);
  Serial.begin(9600);

  delay(500);
  Serial.println("Setup begin");
  FastLED.addLeds<CHIPSET, LED_PIN_TOP, COLOR_ORDER>(matrix_top[0], matrix_top.Size());
  FastLED.addLeds<CHIPSET, LED_PIN_BOTTOM, COLOR_ORDER>(matrix_bottom[0], matrix_bottom.Size());
  FastLED.clear();
  FastLED.show();
  delay(500);

  gPal = HeatColors_p;

  audioShield.enable();
  //audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  
  mixerInput.gain(0, vol);
  mixerInput.gain(1, vol);
  audioShield.volume(0.5);
  fft.windowFunction(AudioWindowHanning1024);

  SPI.setMOSI(7);
  SPI.setSCK(14);

//  if (!(SD.begin(10))) {
//    while (1) {
//      Serial.println("Unable to access the SD card");
//      delay(500);
//    }
//  }
  //eif (!(SD.begin(10))) while (1) delay(500);

  x = random16();
  y = random16();
  z = random16();

  esp.begin(9600);
  esp.setTimeout(100);
  Serial.println("End Setup");
}//END SETUP


long movingtime = millis();
long t2 = millis();
long lev = millis();


void loop() {
  random16_add_entropy( random());

  if (doText) Text();
  if (doSnake) Snake();
  if (doAnimation) Animation(animation);
  if (doFire) Fire();
  if (doNoise) Noise();
  if (doMusic) Music();
  if (doTetris) Tetris();

  if (esp.available() > 0) {
    String in = "";
    while (esp.available()) {
      in += char(esp.read());
      delay(10);
    }
    handleIncoming(in);
  }
}//END LOOP


void handleIncoming(String incoming) {
  Serial.print("Incoming: ");
  Serial.println(incoming);

  if (incoming.indexOf("192.") > -1) {
    //ESP has start
      Serial.print("ESP Started: ");
      Serial.print(incoming);
  }

  if (incoming.indexOf("Animation") > -1) {
    if (doAnimation) {
      Sprites.RemoveAllSprites();
      increaseMode(animation, nAnimation);
    }
    else {
      resetDos();
      doAnimation = true;
    }
    InitAnimation(animation);
  }

  if (incoming.indexOf("Fire") > -1) {
    resetDos();
    doFire = true;
  }

  if (incoming.indexOf("Noise") > -1) {
    if (doNoise) {
      ChangePaletteAndSettings();
    }
    else {
      resetDos();
      doNoise = true;
    }
  }
  if (incoming.indexOf("NoisePalette") > -1) {
    if (doNoise) {
      NoisePalette = true;
    }
  }

  if (incoming.indexOf("Music") > -1) {
    if (doMusic) {
      increaseMode(musicVisualiser, nMusicVisualiser);
    }
    else {
      resetDos();
      doMusic = true;
    }
  }

  if (incoming.indexOf("Volume") > -1) {
    int v = map(getValue(incoming), 0, 100, 10, 1);
    vol = 1.0 / ((float) v);
    mixerInput.gain(0, vol);
    mixerInput.gain(1, vol);
    Serial.print("Volume: ");
    Serial.println(vol);
  }

  if (incoming.indexOf("Text") > -1) {
    StringToTextBuffer(getText(incoming), 0);
    resetDos();
    doText = true;
  }

  if (incoming.indexOf("Saturation") > -1) {
    Saturation = map(getValue(incoming), 0, 100, 0, 255);
  }

  if (incoming.indexOf("Brightness") > -1) {
    Brightness = map(getValue(incoming), 0, 100, 0, 255);
    FastLED.setBrightness(Brightness);
    FastLED.show();
  }

  if (incoming.indexOf("Speed") > -1) {
    wait = map(getValue(incoming), 0, 100, 100, 0);
    Serial.print("Speead/wait: ");
    Serial.print(wait);
  }

  if (incoming.indexOf("Aus") > -1) {
    Sprites.RemoveAllSprites();
    resetDos();
  }

  handleNoise(incoming);

  handleGame(incoming);

}//end handleIncoming()

void handleGame(String in) {
  if (doSnake) handleSnake(in);
  else if (doTetris) handleTetris(in);

  if (in.indexOf("SnakeTop") > -1) {
    resetDos();
    doSnake = true;
    NewGameSnake();
  }
  if (in.indexOf("TetrisTop") > -1) {
    resetDos();
    doTetris = true;
    newGameTetris();
  }
}//end handleGame()


void resetDos() {
  FastLED.clear();
  FastLED.show();
  doSnake = false;
  snakerun = false;
  doText = false;
  doAnimation = false;
  doFire = false;
  doNoise = false;
  doMusic = false;
  doTetris = false;
  NoisePalette = false;
}//end resetDos()

String getText(String str) {
  int sep1 = str.indexOf("-");
  int endsep = str.indexOf("-", sep1 + 1);
  return str.substring(sep1 + 1, endsep);
}//end Text()

int getValue(String str) {
  int sep1 = str.indexOf("-");
  int endsep = str.indexOf("-", sep1 + 1);
  return (str.substring(sep1 + 1, endsep)).toInt();
}//end int getValue()

void getValue(String str, int &r, int &g, int &b) {
  int sep1 = str.indexOf("-");
  int sep2 = str.indexOf("-", sep1 + 1);
  int sep3 = str.indexOf("-", sep2 + 1);
  int endsep = str.indexOf("-", sep3 + 1);
  r = (str.substring(sep1 + 1, sep2)).toInt();
  g = (str.substring(sep2 + 1, sep3)).toInt();
  b = (str.substring(sep3 + 1, endsep)).toInt();
}//end getValue()

void increaseMode(int &mode, int max) {
  mode = mode + 1;
  if (mode > max) mode = 1;
}//end increase()

void EEPROMWritelong(int address, long value) {
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}//end EEPROMWritelong()

long EEPROMReadlong(long address) {
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}//end EEPROMReadlong()

void playEffect(int i) {
  if (playeffects && i < nSoundeffects) {
    wavEffects.play(soundeffects[i]);
    delay(10);
  }
}//end playEffects()






void Animation(int animation) {
  int16_t sx, sy, x, y;
  uint8_t h;

  if (millis() > t2 + wait) {
    switch (animation) {
      case 1:
        FastLED.clear();
        Sprites.UpdateSprites();
        for (int i = 0; i < NumSquares; i++) {
          if (Shape1[i].GetFlags() & SPRITE_EDGE_X_MAX)
            Sprites.ChangePriority(&Shape1[i], SPR_BACK);
          else if (Shape1[i].GetFlags() & SPRITE_EDGE_X_MIN)
            Sprites.ChangePriority(&Shape1[i], SPR_FRONT);
        }
        Sprites.RenderSprites();
        FastLED.show();
        break;
      case 2:
        FastLED.clear();
        Sprites.UpdateSprites();
        Sprites.RenderSprites();
        FastLED.show();
        break;
      case 3:
        FastLED.clear();
        h = hue;
        for (x = 0; x < (matrix_bottom.Width() + matrix_bottom.Height()); ++x) {
          matrix_bottom.DrawLine(x - matrix_bottom.Height(), matrix_bottom.Height() - 1, x, 0, CHSV(h, Saturation, Brightness));
          matrix_top.DrawFilledRectangle(0, 0, 9, 9, CHSV(h, Saturation, Brightness));
          h += 16;
        }
        hue += 4;
        FastLED.show();
        break;
      case 4:
        FastLED.clear();
        h = hue;
        for (y = 0; y < matrix_bottom.Height(); ++y) {
          matrix_bottom.DrawLine(0, y, matrix_bottom.Width() - 1, y, CHSV(h, Saturation, Brightness));
          h += 16;
        }
        for (y = 0; y < matrix_top.Width() / 2; ++y) {
          matrix_top.DrawRectangle(y, y, matrix_top.Width() - y - 1, matrix_top.Height() - y - 1, CHSV(h, Saturation, Brightness));
          h += 16;
        }
        hue += 4;
        FastLED.show();
        break;
    }
    t2 = millis();
  }
}//end Animation()

void InitAnimation(int animaiton) {
  if (animation == 1) {
    int16_t x = MATRIX_WIDTH_BOTTOM - SQUARE_WIDTH - 1, y = 0;
    int8_t xc = -1, yc = 1;
    NumSquares = 0;
    while ((NumSquares < MAX_SQUARES) && (x < (MATRIX_WIDTH_BOTTOM - SQUARE_WIDTH))) {
      for (int i = 0; i < NUM_COLS; i++)
        ColTabs[NumSquares][i] = CHSV(NumSquares * 32, 255, 127 + (i * 64));
      Shape1[NumSquares].Setup(SQUARE_WIDTH, SQUARE_HEIGHT, SquareData1, 1, _2BIT, ColTabs[NumSquares], SquareMask1);
      Shape1[NumSquares].SetPositionFrameMotionOptions(x, y, 0, 0, xc, 2, 0, 0, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN);
      Sprites.AddSprite(&Shape1[NumSquares]);
      ++NumSquares;
      x += (((SQUARE_WIDTH * 5) / 3) * xc);
      if (x <= 0) {
        x = abs(x);
        xc = +1;
      }
      y += yc;
      if ( (y == 0) || (y == (MATRIX_HEIGHT_BOTTOM - SQUARE_HEIGHT)) )
        yc = 0 - yc;
    }
  }
  else if (animation == 2) {
    Shape2.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);
    Sprites.AddSprite(&Shape2);
  }
  else if (animation == 3 || animation == 4) {
    hue = 0;
  }
}//end InitAnimation()

void Fire() {
  if (millis() > t2 + wait) {
    Fire2012WithPalette();
    FastLED.show();
    t2 = millis();
  }
}//end Fire()

void Fire2012WithPalette() {
  // Array of temperature readings at each simulation cell
  static byte heat[MATRIX_WIDTH_BOTTOM][MATRIX_HEIGHT_BOTTOM];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < MATRIX_WIDTH_BOTTOM; i++) {
    for ( int j = 0; j < MATRIX_HEIGHT_BOTTOM; j++) {
      heat[i][j] = qsub8( heat[i][j],  random8(0, ((COOLING * 10) / MATRIX_HEIGHT_BOTTOM) + 2));
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int i = 0; i < MATRIX_WIDTH_BOTTOM; i++) {
    for ( int k = MATRIX_HEIGHT_BOTTOM - 1; k >= 2; k--) {
      heat[i][k] = (heat[i][k - 1] + heat[i][k - 2] + heat[i][k - 2] ) / 3;
    }
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  for ( int i = 0; i < MATRIX_WIDTH_BOTTOM; i++) {
    if ( random8() < SPARKING ) {
      int x = random8(40);
      int y = random8(2);
      heat[x][y] = qadd8( heat[x][y], random8(160, 255) );
    }
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int i = 0; i < MATRIX_WIDTH_BOTTOM; i++) {
    for ( int j = 0; j < MATRIX_HEIGHT_BOTTOM; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8(heat[i][j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if ( gReverseDirection ) {
        pixelnumber = (MATRIX_WIDTH_BOTTOM - 1) - j;
      } else {
        pixelnumber = j;
      }
      matrix_bottom(i, pixelnumber) = color;
    }
  }
}//end Fire2012WithPalette()


void Noise() {
  if (millis() > t2 + wait) {
    fillnoise8();
    mapNoiseToLEDsUsingPalette();
    FastLED.show();
    t2 = millis();
  }
}//end Noise()

void fillnoise8() {
  //file in NoisePaletteDemo in FastLED examples
  uint8_t dataSmoothing = 0;
  if ( speed < 50) {
    dataSmoothing = 200 - (speed * 4);
  }

  for (int i = 0; i < MATRIX_WIDTH_BOTTOM + MATRIX_WIDTH_TOP; i++) {
    int ioffset = scale * i;
    for (int j = 0; j < MATRIX_HEIGHT_BOTTOM; j++) {
      int joffset = scale * j;

      uint8_t data = inoise8(x + ioffset, y + joffset, z);
      data = qsub8(data, 16);
      data = qadd8(data, scale8(data, 39));

      if ( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }
      noise[i][j] = data;
    }
  }

  z += speed;

  x += speed / 8;
  y -= speed / 16;
}//end fillnoise8()

void mapNoiseToLEDsUsingPalette() {
  static uint8_t ihue = 0;

  for (int i = 0; i < MATRIX_WIDTH_BOTTOM + MATRIX_WIDTH_TOP; i++) {
    for (int j = 0; j < MATRIX_HEIGHT_BOTTOM; j++) {
      uint8_t index = noise[j][i];
      uint8_t bri =   noise[i][j];

      if ( colorLoop) {
        index += ihue;
      }

      if ( bri > 127 ) {
        bri = 255;
      } else {
        bri = dim8_raw( bri * 2);
      }
      CRGB color1 = ColorFromPalette( currentPalette, index, bri);

      if (i < MATRIX_WIDTH_BOTTOM) matrix_bottom(i, j) = color1;
      else matrix_top(i - MATRIX_WIDTH_BOTTOM, j) = color1;
    }
  }
  ihue += 1;
}//end mapNoiseToLEDsUsingPalette()

void ChangePaletteAndSettings() {
  palette++;
  if (palette > maxpalette) palette = 0;

  if (palette ==  0)  {
    currentPalette = RainbowColors_p;
    speed = 20;
    scale = 30;
    colorLoop = 1;
  }
  if (palette == 1) {
    SetupPurpleAndGreenPalette();
    speed = 10;
    scale = 50;
    colorLoop = 1;
  }
  if (palette == 2) {
    SetupBlackAndWhiteStripedPalette();
    speed = 20;
    scale = 30;
    colorLoop = 1;
  }
  if (palette == 3) {
    currentPalette = ForestColors_p;
    speed =  8;
    scale = 120;
    colorLoop = 0;
  }
  if (palette == 4) {
    currentPalette = CloudColors_p;
    speed =  4;
    scale = 30;
    colorLoop = 0;
  }
  if (palette == 5) {
    currentPalette = LavaColors_p;
    speed =  8;
    scale = 50;
    colorLoop = 0;
  }
  if (palette == 6) {
    currentPalette = OceanColors_p;
    speed = 20;
    scale = 90;
    colorLoop = 0;
  }
  if (palette == 7) {
    currentPalette = PartyColors_p;
    speed = 20;
    scale = 30;
    colorLoop = 1;
  }
  if (palette == 8) {
    SetupRandomPalette();
    speed = 20;
    scale = 20;
    colorLoop = 1;
  }
  if (palette == 9) {
    SetupRandomPalette();
    speed = 50;
    scale = 50;
    colorLoop = 1;
  }
  if (palette == 10) {
    SetupRandomPalette();
    speed = 90;
    scale = 90;
    colorLoop = 1;
  }
  if (palette == 11) {
    currentPalette = RainbowStripeColors_p;
    speed = 30;
    scale = 20;
    colorLoop = 1;
  }
}//end ChangePaletteAndSettingsPeriodically()

void SetupRandomPalette() {
  currentPalette = CRGBPalette16(
                     CHSV( random8(), 255, 32),
                     CHSV( random8(), 255, 255),
                     CHSV( random8(), 128, 255),
                     CHSV( random8(), 255, 255));
}//end SetupRandomPalette()

void SetupBlackAndWhiteStripedPalette() {
  fill_solid( currentPalette, 16, CRGB::Black);
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}//end SetupBlackAndWhiteStripedPalette()

void SetupPurpleAndGreenPalette() {
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     green,  green,  black,  black,
                     purple, purple, black,  black,
                     green,  green,  black,  black,
                     purple, purple, black,  black );
}//end SetupPurpleAndGreenPalette()


void handleNoise(String incoming) {
  if (doNoise && NoisePalette) {
    if (incoming.indexOf("PaletteH0") > -1) paletteH[0] = getValue(incoming);
    if (incoming.indexOf("PaletteH1") > -1) paletteH[1] = getValue(incoming);
    if (incoming.indexOf("PaletteH2") > -1) paletteH[2] = getValue(incoming);
    if (incoming.indexOf("PaletteH3") > -1) paletteH[3] = getValue(incoming);
    if (incoming.indexOf("PaletteS0") > -1) paletteS[0] = getValue(incoming);
    if (incoming.indexOf("PaletteS1") > -1) paletteS[1] = getValue(incoming);
    if (incoming.indexOf("PaletteS2") > -1) paletteS[2] = getValue(incoming);
    if (incoming.indexOf("PaletteS3") > -1) paletteS[3] = getValue(incoming);
    if (incoming.indexOf("PaletteV0") > -1) paletteV[0] = getValue(incoming);
    if (incoming.indexOf("PaletteV1") > -1) paletteV[1] = getValue(incoming);
    if (incoming.indexOf("PaletteV2") > -1) paletteV[2] = getValue(incoming);
    if (incoming.indexOf("PaletteV3") > -1) paletteV[3] = getValue(incoming);

    if (incoming.indexOf("PaletteSpeed") > -1) speed = getValue(incoming);
    if (incoming.indexOf("PaletteScale") > -1) scale = getValue(incoming);
    if (incoming.indexOf("PaletteLoop") > -1) colorLoop = (colorLoop ? 0 : 1);

    if (NoisePalette) {
      currentPalette = CRGBPalette16(CHSV(paletteH[0], paletteS[0], paletteV[0]),
                                     CHSV(paletteH[1], paletteS[1], paletteV[1]),
                                     CHSV(paletteH[2], paletteS[2], paletteV[2]),
                                     CHSV(paletteH[3], paletteS[3], paletteV[3]));
    }
  }
}//end handleNoise()

void Music() {
  if (musicVisualiser == 1) Music1();
  if (musicVisualiser == 2) Music2();
}//end Music()

void Music1() {
  if (fft.available()) {
    double a = 2, b = 0;
    fft_values[0] = fft.read(0);
    fft_values[1] = fft.read(1);
    for (int i = 2; i < 40; i++) {
      if (i < 10) b = a + a / 3;
      else if (i < 20) b = a + a / 6;
      else b = a + a / 8;
      fft_values[i] = fft.read((int) a, (int) b);
      a = b;
    }
    //Serial.println("FFT Available !");
  }

  if (peak1.available()) {
    peak = peak1.read() * 25;
  }

  if (millis() > t2 + 30) {
    FastLED.clear();
    for (int i = 0; i < 40; i++) {
      int z = min(db(fft_values[i] * 100.0), 20);
      if (z > fft_show[i]) fft_show[i] = z;
      else if (fft_show[i] > 0) fft_show[i]--;

      for (int x = 0; x < map(fft_show[i], 0, 20, 0, 10); x++) {
        CRGB color = ColorFromPalette(PartyColors_p, x * 12);
        matrix_bottom(i, x) = color;
      }
    }

    if (peak > peak_show + 3 && peak > 5) {
      peak_show = peak;
      xx1 = random(0, 8);
      yy1 = random(0, 8);
      bb1 = random(0, 255);
    }
    else if (peak_show > 0) {
      peak_show--;
    }
    matrix_top.DrawRectangle(xx1, yy1, xx1 + 1, yy1 + 1, CHSV(bb1, 200, peak_show * 20));

    FastLED.show();
    t2 = millis();
    //Serial.println("FFT Available !");

  }
}//end Music1()



void Music2() {
  if (millis() > t2 + wait) {
    if (peak1.available()) {
      volume = peak1.read() * 30.0;
      avgVol = (avgVol + volume) / 2.0;

      if (volume < avgVol / 2.0 || volume < 15) volume = 0;

      if (volume > maxVol) maxVol = volume;

      if (gradient > 1529) {
        gradient %= 1530;
        maxVol = (maxVol + volume) / 2.0;
      }

      if (volume - last > avgVol - last && avgVol - last > 0) avgBump = (avgBump + (volume - last)) / 2.0;
      bump = (volume - last) > avgBump;

      Pulse();

      gradient++;

      last = volume;
    }
    t2 = millis();
  }
}//end Music2()

void Pulse() {
  fade(0.85);

  if (bump) gradient += 64;

  if (volume > 0) {
    CRGB color1 = ColorFromPalette( currentPalette, gradient % 255);

    int start = LED_HALF - (LED_HALF * (volume / maxVol));
    int finish = LED_HALF + (LED_HALF * (volume / maxVol));

    for (int i = start; i < finish; i++) {
      float damp = float(((finish - start) / 2.0) - abs((i - start) - ((finish - start) / 2.0))) / float((finish - start) / 2.0);

      if (i < 10)
        matrix_bottom.DrawLine(0, i, matrix_bottom.Width() - 1, i,
                               CRGB(color1.r * pow(damp, 2.0) * vol, color1.g * pow(damp, 2.0) * vol, color1.b * pow(damp, 2.0) * vol));
      else
        matrix_top.DrawRectangle(i - 10, i - 10, 19 - i, 19 - i,
                                 CRGB(color1.r * pow(damp, 2.0) * vol, color1.g * pow(damp, 2.0) * vol, color1.b * pow(damp, 2.0) * vol));
    }
    FastLED.setBrightness(255.0 * pow(volume / maxVol, 2));
  }

  FastLED.show();
}

void fade(float damper) {
  if (damper >= 1) damper = 0.99;

  for (int i = 0; i < MATRIX_WIDTH_BOTTOM; i++) {
    for (int j = 0; j < MATRIX_HEIGHT_BOTTOM; j++) {
      matrix_bottom(i, j).r = matrix_bottom(i, j).r * damper;
      matrix_bottom(i, j).g = matrix_bottom(i, j).g * damper;
      matrix_bottom(i, j).b = matrix_bottom(i, j).b * damper;
    }
  }

  for (int i = 0; i < MATRIX_WIDTH_TOP; i++) {
    for (int j = 0; j < MATRIX_HEIGHT_TOP; j++) {
      matrix_top(i, j).r = matrix_top(i, j).r * damper;
      matrix_top(i, j).g = matrix_top(i, j).g * damper;
      matrix_top(i, j).b = matrix_top(i, j).b * damper;
    }
  }
}

float db(float n) {
  if (n <= 0) return 0;  // or whatever you consider to be "off"
  return log10f(n) * 20.0f;
}//end db()





void Tetris() {
  if (millis() > movingtime + tetrisspeed && tetrisrun) {
    moveDown();
    movingtime = millis();
  }
}//end Tetris()

void handleTetris(String incoming) {
  if (incoming.indexOf("GameStart") > -1) {
    tetrisrun = true;
  }
  if (incoming.indexOf("GamePause") > -1) {
    tetrisrun = false;
  }
  if (incoming.indexOf("GameRotate") > -1) {
    if (tetrisrun) rotateBlock();
  }
  if (incoming.indexOf("GameLeft") > -1) {
    if (tetrisrun) moveLeft(true);
  }
  if (incoming.indexOf("GameRight") > -1) {
    if (tetrisrun) moveRight(true);
  }
  if (incoming.indexOf("GameDown") > -1) {
    if (tetrisrun) moveDown();
  }
}//end handleTetris()

void newGameTetris() {
  tetrisrun = false;
  removePile();
  newBlock();
  drawBorder();
  updatePlayfield();
}//end newGame()

void removePile() {
  for (int i = 0; i < TETRIS_WIDTH; i++) {
    for (int j = 0; j < TETRIS_HIGHT; j++) {
      Pile[i][j] = TETRIS_BLACK;
    }
  }
}//end removePile()

void newBlock() {

  for (int i = 0; i < TETRIS_WIDTH; i++) {
    for (int j = 0; j < TETRIS_HIGHT; j++) {
      Block[i][j] = TETRIS_BLACK;
    }
  }

  removeFullRow();

  currentblock = random(7);
  currentrotation = 0;

  if (currentblock == 0) {
    //generate I
    Block[3][0] = blockcolor[currentblock + 1];
    Block[4][0] = blockcolor[currentblock + 1];
    Block[5][0] = blockcolor[currentblock + 1];
    Block[6][0] = blockcolor[currentblock + 1];
  }
  if (currentblock == 1) {
    //generate J
    Block[3][0] = blockcolor[currentblock + 1];
    Block[3][1] = blockcolor[currentblock + 1];
    Block[4][1] = blockcolor[currentblock + 1];
    Block[5][1] = blockcolor[currentblock + 1];
  }
  if (currentblock == 2) {
    //generate L
    Block[5][0] = blockcolor[currentblock + 1];
    Block[5][1] = blockcolor[currentblock + 1];
    Block[4][1] = blockcolor[currentblock + 1];
    Block[3][1] = blockcolor[currentblock + 1];
  }
  if (currentblock == 3) {
    //generate O
    Block[3][0] = blockcolor[currentblock + 1];
    Block[4][0] = blockcolor[currentblock + 1];
    Block[3][1] = blockcolor[currentblock + 1];
    Block[4][1] = blockcolor[currentblock + 1];
  }
  if (currentblock == 4) {
    //generate S
    Block[4][0] = blockcolor[currentblock + 1];
    Block[5][0] = blockcolor[currentblock + 1];
    Block[4][1] = blockcolor[currentblock + 1];
    Block[3][1] = blockcolor[currentblock + 1];
  }
  if (currentblock == 5) {
    //generate Z
    Block[3][0] = blockcolor[currentblock + 1];
    Block[4][0] = blockcolor[currentblock + 1];
    Block[4][1] = blockcolor[currentblock + 1];
    Block[5][1] = blockcolor[currentblock + 1];
  }
  if (currentblock == 6) {
    //generate T
    Block[4][0] = blockcolor[currentblock + 1];
    Block[3][1] = blockcolor[currentblock + 1];
    Block[4][1] = blockcolor[currentblock + 1];
    Block[5][1] = blockcolor[currentblock + 1];
  }

  for (int j = 0; j < TETRIS_HIGHT; j++) {
    for (int i = 0; i < TETRIS_WIDTH - 1; i++) {
      if (Block[i][j] != TETRIS_BLACK && Pile[i][j] != TETRIS_BLACK) {
        GameOverTetris();
        return;
      }
    }
  }

}//end newBlock()

void rotateBlock() {
  if (currentblock == 3) return;

  int xx, yy;

  for (int i = TETRIS_WIDTH - 1; i >= 0; i--) {
    for (int j = 0; j < TETRIS_HIGHT; j++) {
      if (Block[i][j] != TETRIS_BLACK) xx = i;
    }
  }

  for (int j = TETRIS_HIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != TETRIS_BLACK) yy = j;
    }
  }

  if (currentblock == 0) {
    if (currentrotation == 0 || currentrotation == 2) {
      Block[xx][yy] = TETRIS_BLACK;
      Block[xx + 2][yy] = TETRIS_BLACK;
      Block[xx + 3][yy] = TETRIS_BLACK;

      Block[xx + 1][yy - 1] = blockcolor[currentblock + 1];
      Block[xx + 1][yy + 1] = blockcolor[currentblock + 1];
      Block[xx + 1][yy + 2] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 1 || currentrotation == 3) {
      if (!spaceLeft()) {
        if (spaceRight3()) {
          if (!moveRight(false))
            return;
          xx++;;
        }
        else {
          return;
        }
      }
      else if (!spaceRight()) {
        if (spaceLeft3()) {
          if (!moveLeft(false))
            return;
          if (!moveLeft(false))
            return;
          xx--;
          xx--;
        }
        else {
          return;
        }
      }
      else if (!spaceRight2()) {
        if (spaceLeft2()) {
          if (!moveLeft(false))
            return;
          xx--;
        }
        else {
          return;
        }
      }
      Block[xx][yy] = TETRIS_BLACK;
      Block[xx][yy + 2] = TETRIS_BLACK;
      Block[xx][yy + 3] = TETRIS_BLACK;

      Block[xx - 1][yy + 1] = blockcolor[currentblock + 1];
      Block[xx + 1][yy + 1] = blockcolor[currentblock + 1];
      Block[xx + 2][yy + 1] = blockcolor[currentblock + 1];
    }
  }

  xx++;
  yy++;

  if (currentblock == 1) {
    if (currentrotation == 0) {
      Block[xx - 1][yy - 1] = TETRIS_BLACK;
      Block[xx - 1][yy] = TETRIS_BLACK;
      Block[xx + 1][yy] = TETRIS_BLACK;

      Block[xx][yy - 1] = blockcolor[currentblock + 1];
      Block[xx + 1][yy - 1] = blockcolor[currentblock + 1];
      Block[xx][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 1) {
      if (!spaceLeft()) {
        if (!moveRight(false))
          return;
        xx++;
      }
      xx--;

      Block[xx][yy - 1] = TETRIS_BLACK;
      Block[xx + 1][yy - 1] = TETRIS_BLACK;
      Block[xx][yy + 1] = TETRIS_BLACK;

      Block[xx - 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 2) {
      yy--;

      Block[xx - 1][yy] = TETRIS_BLACK;
      Block[xx + 1][yy] = TETRIS_BLACK;
      Block[xx + 1][yy + 1] = TETRIS_BLACK;

      Block[xx][yy - 1] = blockcolor[currentblock + 1];
      Block[xx][yy + 1] = blockcolor[currentblock + 1];
      Block[xx - 1][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 3) {
      if (!spaceRight()) {
        if (!moveLeft(false))
          return;
        xx--;
      }
      Block[xx][yy - 1] = TETRIS_BLACK;
      Block[xx][yy + 1] = TETRIS_BLACK;
      Block[xx - 1][yy + 1] = TETRIS_BLACK;

      Block[xx - 1][yy - 1] = blockcolor[currentblock + 1];
      Block[xx - 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy] = blockcolor[currentblock + 1];
    }
  }

  if (currentblock == 2) {
    if (currentrotation == 0) {
      Block[xx + 1][yy - 1] = TETRIS_BLACK;
      Block[xx - 1][yy] = TETRIS_BLACK;
      Block[xx + 1][yy] = TETRIS_BLACK;

      Block[xx][yy - 1] = blockcolor[currentblock + 1];
      Block[xx + 1][yy + 1] = blockcolor[currentblock + 1];
      Block[xx][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 1) {
      if (!spaceLeft()) {
        if (!moveRight(false))
          return;
        xx++;
      }
      xx--;

      Block[xx][yy - 1] = TETRIS_BLACK;
      Block[xx + 1][yy + 1] = TETRIS_BLACK;
      Block[xx][yy + 1] = TETRIS_BLACK;

      Block[xx - 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy] = blockcolor[currentblock + 1];
      Block[xx - 1][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 2) {
      yy--;

      Block[xx - 1][yy] = TETRIS_BLACK;
      Block[xx + 1][yy] = TETRIS_BLACK;
      Block[xx - 1][yy + 1] = TETRIS_BLACK;

      Block[xx][yy - 1] = blockcolor[currentblock + 1];
      Block[xx][yy + 1] = blockcolor[currentblock + 1];
      Block[xx - 1][yy - 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 3) {
      if (!spaceRight()) {
        if (!moveLeft(false))
          return;
        xx--;
      }
      Block[xx][yy - 1] = TETRIS_BLACK;
      Block[xx][yy + 1] = TETRIS_BLACK;
      Block[xx - 1][yy - 1] = TETRIS_BLACK;

      Block[xx + 1][yy - 1] = blockcolor[currentblock + 1];
      Block[xx - 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy] = blockcolor[currentblock + 1];
    }
  }

  if (currentblock == 4) {
    if (currentrotation == 0 || currentrotation == 2) {
      Block[xx + 1][yy - 1] = TETRIS_BLACK;
      Block[xx - 1][yy] = TETRIS_BLACK;

      Block[xx + 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 1 || currentrotation == 3) {
      if (!spaceLeft()) {
        if (!moveRight(false))
          return;
        xx++;
      }
      xx--;

      Block[xx + 1][yy] = TETRIS_BLACK;
      Block[xx + 1][yy + 1] = TETRIS_BLACK;

      Block[xx - 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy - 1] = blockcolor[currentblock + 1];
    }
  }

  if (currentblock == 5) {
    if (currentrotation == 0 || currentrotation == 2) {
      Block[xx - 1][yy - 1] = TETRIS_BLACK;
      Block[xx][yy - 1] = TETRIS_BLACK;

      Block[xx + 1][yy - 1] = blockcolor[currentblock + 1];
      Block[xx][yy + 1] = blockcolor[currentblock + 1];

    }
    if (currentrotation == 1 || currentrotation == 3) {
      if (!spaceLeft()) {
        if (!moveRight(false))
          return;
        xx++;
      }
      xx--;

      Block[xx + 1][yy - 1] = TETRIS_BLACK;
      Block[xx][yy + 1] = TETRIS_BLACK;

      Block[xx - 1][yy - 1] = blockcolor[currentblock + 1];
      Block[xx][yy - 1] = blockcolor[currentblock + 1];
    }
  }

  if (currentblock == 6) {
    if (currentrotation == 0) {
      Block[xx][yy - 1] = TETRIS_BLACK;
      Block[xx - 1][yy] = TETRIS_BLACK;
      Block[xx + 1][yy] = TETRIS_BLACK;

      Block[xx][yy - 1] = blockcolor[currentblock + 1];
      Block[xx + 1][yy] = blockcolor[currentblock + 1];
      Block[xx][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 1) {
      if (!spaceLeft()) {
        if (!moveRight(false))
          return;
        xx++;
      }
      xx--;

      Block[xx][yy - 1] = TETRIS_BLACK;
      Block[xx + 1][yy] = TETRIS_BLACK;
      Block[xx][yy + 1] = TETRIS_BLACK;

      Block[xx - 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy] = blockcolor[currentblock + 1];
      Block[xx][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 2) {
      yy--;

      Block[xx - 1][yy] = TETRIS_BLACK;
      Block[xx + 1][yy] = TETRIS_BLACK;
      Block[xx][yy + 1] = TETRIS_BLACK;

      Block[xx][yy - 1] = blockcolor[currentblock + 1];
      Block[xx - 1][yy] = blockcolor[currentblock + 1];
      Block[xx][yy + 1] = blockcolor[currentblock + 1];
    }
    if (currentrotation == 3) {
      if (!spaceRight()) {
        if (!moveLeft(false))
          return;
        xx--;
      }
      Block[xx][yy - 1] = TETRIS_BLACK;
      Block[xx - 1][yy] = TETRIS_BLACK;
      Block[xx][yy + 1] = TETRIS_BLACK;

      Block[xx][yy - 1] = blockcolor[currentblock + 1];
      Block[xx - 1][yy] = blockcolor[currentblock + 1];
      Block[xx + 1][yy] = blockcolor[currentblock + 1];
    }
  }

  while (!checkOverlap())
  {
    for (int j = 0; j < TETRIS_HIGHT; j++)
    {
      for (int i = 0; i < TETRIS_WIDTH; i++)
      {
        Block[i][j] = Block[i][j + 1];
      }
    }
    movingtime = millis() + tetrisspeed;
  }

  currentrotation++;
  if (currentrotation == 4) currentrotation = 0;

  updatePlayfield();

}//end rotateBlock()

void moveDown() {
  if (spaceBelow()) {
    byte copyBlock[TETRIS_WIDTH][TETRIS_HIGHT];
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      for (int j = 0; j < TETRIS_HIGHT; j++) {
        copyBlock[i][j] = Block[i][j];
        Block[i][j] = TETRIS_BLACK;
      }
    }

    for (int j = TETRIS_HIGHT - 1; j > 0; j--) {
      for (int i = 0; i < TETRIS_WIDTH; i++) {
        Block[i][j] = copyBlock[i][j - 1];
      }
    }
  }
  else {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      for (int j = 0; j < TETRIS_HIGHT; j++) {
        if (Block[i][j] != TETRIS_BLACK)
          Pile[i][j] = Block[i][j];
      }
    }
    newBlock();
  }
  updatePlayfield();
}//end moveDown

boolean moveRight(boolean refresh) {
  if (spaceRight()) {
    byte copyBlock[TETRIS_WIDTH][TETRIS_HIGHT];
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      for (int j = 0; j < TETRIS_HIGHT; j++) {
        copyBlock[i][j] = Block[i][j];
        Block[i][j] = TETRIS_BLACK;
      }
    }

    for (int i = 1; i < TETRIS_WIDTH; i++) {
      for (int j = 0; j < TETRIS_HIGHT; j++) {
        Block[i][j] = copyBlock[i - 1][j];
      }
    }
    if (refresh) updatePlayfield();
    return true;
  }
  return false;
}//end moveRight()

boolean moveLeft(boolean refresh) {
  if (spaceLeft()) {
    byte copyBlock[TETRIS_WIDTH][TETRIS_HIGHT];
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      for (int j = 0; j < TETRIS_HIGHT; j++) {
        copyBlock[i][j] = Block[i][j];
        Block[i][j] = TETRIS_BLACK;
      }
    }

    for (int i = 0; i < TETRIS_WIDTH - 1; i++) {
      for (int j = 0; j < TETRIS_HIGHT; j++) {

        Block[i][j] = copyBlock[i + 1][j];
      }
    }
    if (refresh) updatePlayfield();
    return true;
  }
  return false;
}//end moveLeft()



boolean spaceBelow() {
  for (int j = TETRIS_HIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != TETRIS_BLACK) {
        if (j == TETRIS_HIGHT - 1)
          return false;
        if (Pile[i][j + 1] != TETRIS_BLACK)
          return false;
      }
    }
  }
  return true;
}//end spaceBelow()

boolean spaceLeft() {
  for (int j = TETRIS_HIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != TETRIS_BLACK) {
        if (i == 0)
          return false;
        if (Pile[i - 1][j] != TETRIS_BLACK)
          return false;
      }
    }
  }
  return true;
}//end spaceLeft()

boolean spaceLeft2() {
  for (int j = TETRIS_HIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != TETRIS_BLACK) {
        if (i == 0 || i == 1)
          return false;
        if (Pile[i - 1][j] != TETRIS_BLACK || Pile[i - 2][j] != TETRIS_BLACK)
          return false;
      }
    }
  }
  return true;
}//end spaceLeft2()

boolean spaceLeft3() {
  for (int j = TETRIS_HIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != TETRIS_BLACK) {
        if (i == 0 || i == 1 || i == 2)
          return false;
        if (Pile[i - 1][j] != TETRIS_BLACK || Pile[i - 2][j] != TETRIS_BLACK || Pile[i - 3][j] != TETRIS_BLACK)
          return false;
      }
    }
  }
  return true;
}//end spaceLeft3()

boolean spaceRight() {
  for (int j = TETRIS_HIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != TETRIS_BLACK) {
        if (i == TETRIS_WIDTH - 1)
          return false;
        if (Pile[i + 1][j] != TETRIS_BLACK)
          return false;
      }
    }
  }
  return true;
}//end spaceRight()

boolean spaceRight2() {
  for (int j = TETRIS_HIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != TETRIS_BLACK) {
        if (i == TETRIS_WIDTH - 1 || i == TETRIS_WIDTH - 2)
          return false;
        if (Pile[i + 1][j] != TETRIS_BLACK || Pile[i + 2][j] != TETRIS_BLACK)
          return false;
      }
    }
  }
  return true;
}//end spaceRight2()

boolean spaceRight3() {
  for (int j = TETRIS_HIGHT - 1; j >= 0; j--) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != TETRIS_BLACK) {
        if (i == TETRIS_WIDTH - 1 || i == TETRIS_WIDTH - 2 || i == TETRIS_WIDTH - 3)
          return false;
        if (Pile[i + 1][j] != TETRIS_BLACK || Pile[i + 2][j] != TETRIS_BLACK || Pile[i + 3][j] != TETRIS_BLACK)
          return false;
      }
    }
  }
  return true;
}//end spaceRight3()

boolean checkOverlap() {
  for (int j = 0; j < TETRIS_HIGHT; j++) {
    for (int i = 0; i < TETRIS_WIDTH - 1; i++) {
      if (Block[i][j]) {
        if (Pile[i][j]) return false;
      }
    }
  }
  for (int j = TETRIS_HIGHT; j < TETRIS_HIGHT + 2; j++) {
    for (int i = 0; i < 7; i++) {
      if (Block[i][j]) return false;
    }
  }
  return true;
}//end checkOverlap()


void removeFullRow() {
  while (checkFullRow() != -1) {
    int fullrow = checkFullRow();

    playEffect(9);

    for (int i = 0; i < TETRIS_WIDTH; i++) {
      Pile[i][fullrow] = TETRIS_WHITE;
    }
    updatePlayfield();
    delay(100);
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      Pile[i][fullrow] = TETRIS_BLACK;
    }
    updatePlayfield();
    delay(100);
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      Pile[i][fullrow] = TETRIS_WHITE;
    }
    updatePlayfield();
    delay(100);
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      Pile[i][fullrow] = TETRIS_BLACK;
    }

    for (int j = fullrow; j >= 0; j--) {
      for (int i = 0; i < TETRIS_WIDTH; i++) {
        Pile[i][j] = Pile[i][j - 1];
      }
    }
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      Pile[i][0] = TETRIS_BLACK;
    }
  }
}//end removeFullRow()


int checkFullRow() {
  int cnt = 0;

  for (int j = 0; j < TETRIS_HIGHT; j++) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Pile[i][j] != TETRIS_BLACK) cnt++;
    }
    if (cnt == 10) return j;
    cnt = 0;
  }
  return -1;
}//end checkFullRow()


void GameOverTetris() {
  tetrisrun = false;

  FastLED.clear();

  playEffect(2);

  StringToTextBuffer("GAME OVER", 1);
  matrix_top.DrawFilledRectangle(0, 0, 9, 9, CRGB::Red);
  while (scrollingtext.UpdateText() != -1) {
    FastLED.show();
    delay(50);
  }

  resetDos();
  doNoise = true;
}//end GameOverTetris()

void drawBorder() {
  matrix_bottom.DrawLine(9, 0, 9, 9, CRGB::Red);
  matrix_bottom.DrawLine(20, 0, 20, 9, CRGB::Red);
  matrix_bottom.DrawLine(20, 9, 29, 9, CRGB::Red);
  matrix_bottom.DrawLine(0, 9, 9, 9, CRGB::Red);
  matrix_bottom.DrawLine(30, 9, 39, 9, CRGB::Red);
}//end drawPlayfield()



void updatePlayfield() {
  FastLED.clear();
  for (int i = 0; i < TETRIS_WIDTH; i++) {
    for (int j = 0; j < TETRIS_HIGHT; j++) {
      if (Block[i][j] != TETRIS_BLACK) setXYPixelTetris(i, j, TetrisColor[Block[i][j]]);
      if (Pile[i][j] != TETRIS_BLACK) setXYPixelTetris(i, j, TetrisColor[Pile[i][j]]);
    }
  }
  drawBorder();
  FastLED.show();
  //PrintToMonitor(); //debug
}//end renderTetris()

void setXYPixelTetris(byte x, byte y, CRGB c) {
  if (y < 10)
    matrix_top(x, y) = c;
  else
    matrix_bottom(x + 10, 19 - y) = c;
}//end setXYPixel()

void PrintToMonitor() {
  for (int j = 0; j < TETRIS_HIGHT; j++) {
    for (int i = 0; i < TETRIS_WIDTH; i++) {
      if (Block[i][j] != 0) Serial.print("x");
      else Serial.print("-");
      Serial.print("\t");
    }
    Serial.println();
  }
  Serial.println();
}




void Text() {
  if (millis() > t2 + wait) {
    if (scrollingtext.UpdateText() == -1) {
      scrollingtext.SetText(TextBuffer, charlength(TextBuffer, MAX_BUFFER));
      setTextColor(0);
    }
    else
      FastLED.show();
    t2 = millis();
  }
}//end Text()

int PrepareText(String &txt) {
  txt = "        " + txt;
  return txt.length();
}//end PrepareText()

int PrepareText2(String &txt) {
  txt = txt;
  return txt.length();
}//end PrepareText2()

void StringToTextBuffer(String str, int mode) {
  clearTextBuffer();
  str.toCharArray((char*) TextBuffer, PrepareText(str) + 1);
  scrollingtext.SetFont(MatriseFontData);
  scrollingtext.Init(&matrix_bottom, matrix_bottom.Width(), scrollingtext.FontHeight() + 1, 0, 1);
  scrollingtext.SetText((unsigned char*) TextBuffer, charlength(TextBuffer, MAX_BUFFER));
  scrollingtext.SetScrollDirection(SCROLL_LEFT);
  scrollingtext.SetTextDirection(CHAR_UP);

  setTextColor(mode);
}//end StringToTextBuffer()

int charlength(unsigned char *chararray, int nmax) {
  int x = 0;
  for (int i = 0; i < nmax; i++) {
    int c = chararray[i];
    if (c != '\0') x++;
  }
  return x;
}//end charlength()

void clearTextBuffer() {
  for (int i = 0; i < MAX_BUFFER; i++)
    TextBuffer[i] = (char) 0 ;
}//end clearTextBuffer()

void setTextColor(int mode) {
  if (mode == 0) scrollingtext.SetTextColrOptions(COLR_HSV | COLR_GRAD | COLR_CHAR | COLR_HORI, random(0, 255), 250, 200, random(0, 255), 250, 200);
  else if (mode == 1) scrollingtext.SetTextColrOptions(COLR_GRAD_CV, 250, 0, 0, 250, 250, 250);
  else scrollingtext.SetTextColrOptions(COLR_GRAD_CH, 0, 0, 200, 250, 250, 250);
}//end setTextColor()





void Snake() {
  if (millis() > movingtime + snakespeed && snakerun) {
    moveSnake();
    movingtime = millis();
  }
}//end Snake

void handleSnake(String incoming) {
  if (incoming.indexOf("GameRight") > -1) {
    setSnakeDirection(1);
  }
  if (incoming.indexOf("GameLeft") > -1) {
    setSnakeDirection(-1);
  }
  if (incoming.indexOf("GameStart") > -1) {
    snakerun = true;
  }
  if (incoming.indexOf("GamePause") > -1) {
    snakerun = false;
  }
  if (incoming.indexOf("GameReset") > -1) {
    EEPROMWritelong(0, ScoreEEPROMaddress);
  }
}//end handleSnake()

void setXYPixel(byte x, byte y, CRGB c) {
  if (x <= 40)
    matrix_bottom(x - 1, y - 1) = c;
  else
    matrix_top(x - 41, y - 1) = c;
}//end setXYPixel()

void NewGameSnake() {
  byte x, y;

  SnakeItems = 1;
  SnakeHeadID = 1;
  SnakeItemPosX[1] = 1;
  SnakeItemPosY[1] = 1;
  movingDirection = SNAKE_RIGHT;
  snakeDirection = SNAKE_RIGHT;
  snakeOntop = false;
  snakerun = false;
  SnakeScore = 0;
  snakespeed = SNAKESPEED_BEGIN;

  //Spielfeld ausschalten
  for (y = 1; y <= BaneGridYmax; y++) {
    for (x = 1; x <= BaneGridXmax; x++) {
      Playfield[x][y] = BLANK;
    }
  }

  AddSnakeItem = 0;
  AppleCount = 0;
  placeRandomApple();

  render();
  movingtime = millis();
}//end newgame

void render() {
  byte i, x, y;

  for (i = 1; i <= oldSnakeItems; i++) {
    if (oldSnakeItemPosX[i] > 0 && oldSnakeItemPosY[i] > 0 && oldSnakeItemPosX[i] <= BaneGridXmax && oldSnakeItemPosY[i] <= BaneGridYmax) {
      Playfield[oldSnakeItemPosX[i]][oldSnakeItemPosY[i]] = BLANK;
    }
  }

  for (i = 1; i <= SnakeItems; i++) {
    if (SnakeItemPosX[i] > 0 && SnakeItemPosY[i] > 0 && SnakeItemPosX[i] <= BaneGridXmax && SnakeItemPosY[i] <= BaneGridYmax) {
      Playfield[SnakeItemPosX[i]][SnakeItemPosY[i]] = SNAKE;
      oldSnakeItemPosX[i] = SnakeItemPosX[i];
      oldSnakeItemPosY[i] = SnakeItemPosY[i];
    }
  }

  oldSnakeItems = SnakeItems;

  //schalte die leds auf der matrix
  for (y = 1; y <= BaneGridYmax; y++) {
    for (x = 1; x <= BaneGridXmax; x++) {
      switch (Playfield[x][y]) {
        case BLANK:
          setXYPixel(x, y, CRGB::Black); //Blank
          break;

        case SNAKE:
          if (SnakeItemPosX[SnakeHeadID] == x && SnakeItemPosY[SnakeHeadID] == y)
            setXYPixel(x, y, CRGB::Yellow); // Yellow snake head
          else
            setXYPixel(x, y, CRGB::Green); // Green snake body
          break;

        case APPLE:
          setXYPixel(x, y, CRGB::Red);  //Red Apple
          break;

        default:
          setXYPixel(x, y, CRGB::Black);  //Blank
          break;
      }
    }
  }

  FastLED.show();
}//end render


void moveSnake() {
  byte i;
  movingDirection = snakeDirection;

  if (AddSnakeItem == 0) {
    //wenn er keinen apfel isst
    SnakeBackID = SnakeHeadID - 1;

    if (SnakeBackID == 0) SnakeBackID = SnakeItems;

    SnakeItemPosX[SnakeBackID] = SnakeItemPosX[SnakeHeadID];
    SnakeItemPosY[SnakeBackID] = SnakeItemPosY[SnakeHeadID];

    switch (movingDirection) {
      case SNAKE_RIGHT:
        SnakeItemPosX[SnakeBackID] += 1;
        //damit snake nicht am seitlichen x rand aufhört
        if (SnakeItemPosX[SnakeBackID] == 41 && !snakeOntop) {
          SnakeItemPosX[SnakeBackID] = 1;
        }
        //verhalten der schlange wenn sie von der oberen matrix auf die seite wechselt
        else if (SnakeItemPosX[SnakeBackID] == 51 && snakeOntop) {
          SnakeItemPosX[SnakeBackID] = 31 - SnakeItemPosY[SnakeBackID];
          SnakeItemPosY[SnakeBackID] = 10;
          snakeDirection = SNAKE_DOWN;
          snakeOntop = false;
        }
        break;

      case SNAKE_LEFT:
        SnakeItemPosX[SnakeBackID] -= 1;
        //damit snake nicht am seitlichen x rand aufhört
        if (SnakeItemPosX[SnakeBackID] < 1 && !snakeOntop) {
          SnakeItemPosX[SnakeBackID] = 40;
        }
        //verhalten der schlange wenn sie von der oberen matrix auf die seite wechselt
        else if (SnakeItemPosX[SnakeBackID] == 40 && snakeOntop) {
          SnakeItemPosX[SnakeBackID] = SnakeItemPosY[SnakeBackID];
          SnakeItemPosY[SnakeBackID] = 10;
          snakeDirection = SNAKE_DOWN;
          snakeOntop = false;
        }
        break;

      case SNAKE_DOWN:
        SnakeItemPosY[SnakeBackID] -= 1;

        //verhalten der schlange wenn sie von der oberen matrix auf die seite wechselt
        if (SnakeItemPosY[SnakeBackID] == 0 && SnakeItemPosX[SnakeBackID] > 40 && snakeOntop) {
          SnakeItemPosY[SnakeBackID] = 10;
          SnakeItemPosX[SnakeBackID] = 81 - SnakeItemPosX[SnakeBackID];
          snakeDirection = SNAKE_DOWN;
          snakeOntop = false;
        }
        break;

      case SNAKE_UP:
        SnakeItemPosY[SnakeBackID] += 1;

        //verhalten der schlange wenn sie von der oberen matrix auf die seite wechselt
        if (SnakeItemPosY[SnakeBackID] == 11 && SnakeItemPosX[SnakeBackID] > 40 && snakeOntop) {
          SnakeItemPosY[SnakeBackID] = 10;
          SnakeItemPosX[SnakeBackID] = SnakeItemPosX[SnakeBackID] - 30;
          snakeDirection = SNAKE_DOWN;
          snakeOntop = false;
        }

        //verhalten der schlange wenn sie von der seite auf die obere matrix wechselt
        else if (SnakeItemPosY[SnakeBackID] > 10 && !snakeOntop) {
          if (SnakeItemPosX[SnakeBackID] > 0 && SnakeItemPosX[SnakeBackID] <= 10) {
            SnakeItemPosY[SnakeBackID] = SnakeItemPosX[SnakeBackID];
            SnakeItemPosX[SnakeBackID] = 41;
            snakeDirection = SNAKE_RIGHT;
          }
          else if (SnakeItemPosX[SnakeBackID] > 10 && SnakeItemPosX[SnakeBackID] <= 20) {
            SnakeItemPosY[SnakeBackID] = 10;
            SnakeItemPosX[SnakeBackID] = SnakeItemPosX[SnakeBackID] + 30;
            snakeDirection = SNAKE_DOWN;
          }
          else if (SnakeItemPosX[SnakeBackID] > 20 && SnakeItemPosX[SnakeBackID] <= 30) {
            SnakeItemPosY[SnakeBackID] = 31 - SnakeItemPosX[SnakeBackID];
            SnakeItemPosX[SnakeBackID] = 50;
            snakeDirection = SNAKE_LEFT;
          }
          else if (SnakeItemPosX[SnakeBackID] > 30 && SnakeItemPosX[SnakeBackID] <= 40) {
            SnakeItemPosY[SnakeBackID] = 1;
            SnakeItemPosX[SnakeBackID] = 81 - SnakeItemPosX[SnakeBackID];
            snakeDirection = SNAKE_UP;
          }
          snakeOntop = true;
        }
        break;
    }
    SnakeHeadID = SnakeBackID;
  }
  else {
    //die schlange isst einen apfel
    for (i = SnakeItems; i >= SnakeHeadID; i--) {
      SnakeItemPosX[i + 1] = SnakeItemPosX[i];
      SnakeItemPosY[i + 1] = SnakeItemPosY[i];
    }

    SnakeItemPosX[SnakeHeadID] = SnakeItemPosX[SnakeHeadID + 1];
    SnakeItemPosY[SnakeHeadID] = SnakeItemPosY[SnakeHeadID + 1];

    switch (movingDirection) {
      case SNAKE_RIGHT:
        SnakeItemPosX[SnakeHeadID] += 1;
        //damit snake nicht am seitlichen x rand aufhört
        if (SnakeItemPosX[SnakeHeadID] == 41 && !snakeOntop) {
          SnakeItemPosX[SnakeHeadID] = 1;
        }
        //verhalten der schlange wenn sie von der oberen matrix auf die seite wechselt
        else if (SnakeItemPosX[SnakeHeadID] == 51 && snakeOntop) {
          SnakeItemPosX[SnakeHeadID] = 31 - SnakeItemPosY[SnakeHeadID];
          SnakeItemPosY[SnakeHeadID] = 10;
          snakeDirection = SNAKE_DOWN;
          snakeOntop = false;
        }
        break;

      case SNAKE_LEFT:
        SnakeItemPosX[SnakeHeadID] -= 1;
        //damit snake nicht am seitlichen x rand aufhört
        if (SnakeItemPosX[SnakeHeadID] < 1 && !snakeOntop) {
          SnakeItemPosX[SnakeHeadID] = 40;
        }
        //verhalten der schlange wenn sie von der oberen matrix auf die seite wechselt
        else if (SnakeItemPosX[SnakeHeadID] == 40 && snakeOntop) {
          SnakeItemPosX[SnakeHeadID] = SnakeItemPosY[SnakeHeadID];
          SnakeItemPosY[SnakeHeadID] = 10;
          snakeDirection = SNAKE_DOWN;
          snakeOntop = false;
        }
        break;

      case SNAKE_DOWN:
        SnakeItemPosY[SnakeHeadID] -= 1;

        //verhalten der schlange wenn sie von der oberen matrix auf die seite wechselt
        if (SnakeItemPosY[SnakeHeadID] == 0 && SnakeItemPosX[SnakeHeadID] > 40 && snakeOntop) {
          SnakeItemPosY[SnakeHeadID] = 10;
          SnakeItemPosX[SnakeHeadID] = 81 - SnakeItemPosX[SnakeHeadID];
          snakeDirection = SNAKE_DOWN;
          snakeOntop = false;
        }
        break;

      case SNAKE_UP:
        SnakeItemPosY[SnakeHeadID] += 1;

        //verhalten der schlange wenn sie von der oberen matrix auf die seite wechselt
        if (SnakeItemPosY[SnakeHeadID] == 11 && SnakeItemPosX[SnakeHeadID] > 40 && snakeOntop) {
          SnakeItemPosY[SnakeHeadID] = 10;
          SnakeItemPosX[SnakeHeadID] = SnakeItemPosX[SnakeHeadID] - 30;
          snakeDirection = SNAKE_DOWN;
          snakeOntop = false;
        }

        //verhalten der schlange wenn sie von der seite auf die obere matrix wechselt
        else if (SnakeItemPosY[SnakeHeadID] > 10 && !snakeOntop) {
          if (SnakeItemPosX[SnakeHeadID] > 0 && SnakeItemPosX[SnakeHeadID] <= 10) {
            SnakeItemPosY[SnakeHeadID] = SnakeItemPosX[SnakeHeadID];
            SnakeItemPosX[SnakeHeadID] = 41;
            snakeDirection = SNAKE_RIGHT;
          }
          else if (SnakeItemPosX[SnakeHeadID] > 10 && SnakeItemPosX[SnakeHeadID] <= 20) {
            SnakeItemPosY[SnakeHeadID] = 10;
            SnakeItemPosX[SnakeHeadID] = SnakeItemPosX[SnakeHeadID] + 30;
            snakeDirection = SNAKE_DOWN;
          }
          else if (SnakeItemPosX[SnakeHeadID] > 20 && SnakeItemPosX[SnakeHeadID] <= 30) {
            SnakeItemPosY[SnakeHeadID] = 31 - SnakeItemPosX[SnakeHeadID];
            SnakeItemPosX[SnakeHeadID] = 50;
            snakeDirection = SNAKE_LEFT;
          }
          else if (SnakeItemPosX[SnakeBackID] > 30 && SnakeItemPosX[SnakeHeadID] <= 40) {
            SnakeItemPosY[SnakeHeadID] = 1;
            SnakeItemPosX[SnakeHeadID] = 81 - SnakeItemPosX[SnakeHeadID];
            snakeDirection = SNAKE_UP;
          }
          snakeOntop = true;
        }
        break;
    }

    SnakeItems++;
    AddSnakeItem--;
  }

  //Abbruchbedingungen
  //Snake darf keine wand berühren
  //if (SnakeItemPosX[SnakeHeadID] > 0 && SnakeItemPosX[SnakeHeadID] <= BaneGridXmax && SnakeItemPosY[SnakeHeadID] > 0 && SnakeItemPosY[SnakeHeadID] <= BaneGridYmax) {
  //Snake darf nur oben und unten nicht berühren
  if (SnakeItemPosY[SnakeHeadID] > 0) {
    //Snake kommt nicht an den Rand
    if (Playfield[SnakeItemPosX[SnakeHeadID]][SnakeItemPosY[SnakeHeadID]] != SNAKE) {
      if (Playfield[SnakeItemPosX[SnakeHeadID]][SnakeItemPosY[SnakeHeadID]] == APPLE) {
        //Snake isst einen Apple

        playEffect(0);

        if (snakespeed > snakespeedmax + 10) snakespeed = snakespeed - 10;

        SnakeScore++;
        //add one
        AddSnakeItem += SnakeItemsToAddAtApple;
        AppleCount--;
      }

      if (AppleCount == 0) {
        //falls kein Apple mehr auf dem Spielfeld
        placeRandomApple();
      }
      render();
    }
    else {
      //Snake trifft sich selber
      GameOver();
    }
  }
  else {
    //Snake kommt an den Rand
    GameOver();
  }
}//end moveSnake()

void placeRandomApple() {
  byte x, y;
  x = random(1, BaneGridXmax);
  y = random(1, BaneGridYmax);

  //Suche eine Stelle an der noch keine led leuchtet
  while (Playfield[x][y] != BLANK) {
    x = random(1, BaneGridXmax);
    y = random(1, BaneGridYmax);
  }
  placeApple(x, y);
}//placeRandomApple()

void placeApple(byte x, byte y) {
  if (x > 0 && y > 0 && x <= BaneGridXmax && y <= BaneGridYmax) {
    //befinden sich x,y im Spielfeld
    Playfield[x][y] = APPLE;
    ApplePosX = x;
    ApplePosY = y;

    AppleCount++;
  }
}//end placeApple()

void removeApple() {
  Playfield[ApplePosX][ApplePosY] = BLANK;
  AppleCount = 0;
}//end removeapple()

void GameOver() {
  //if (SnakeItemPosX[SnakeHeadID] == 0) SnakeItemPosX[SnakeHeadID]++;
  //else if (SnakeItemPosX[SnakeHeadID] > BaneGridXmax) SnakeItemPosX[SnakeHeadID]--;

  if (SnakeItemPosY[SnakeHeadID] == 0) SnakeItemPosY[SnakeHeadID]++;
  else if (SnakeItemPosY[SnakeHeadID] > BaneGridYmax) SnakeItemPosY[SnakeHeadID]--;

  if (SnakeHeadID < SnakeItems)
    setXYPixel(SnakeItemPosX[SnakeHeadID + 1], SnakeItemPosY[SnakeHeadID + 1], CRGB::Green);
  else
    setXYPixel(SnakeItemPosX[1], SnakeItemPosY[1], CRGB::Green);

  setXYPixel(SnakeItemPosX[SnakeHeadID], SnakeItemPosY[SnakeHeadID], CRGB::Aqua);

  FastLED.show();

  snakerun = false;

  FastLED.clear();
  StringToTextBuffer("GAME OVER", 1);

  playEffect(2);

  matrix_top.DrawFilledRectangle(0, 0, 9, 9, CRGB::Red);
  while (scrollingtext.UpdateText() != -1) {
    FastLED.show();
    delay(50);
  }

  //  if (CheckHighscore(SnakeScore)) {
  //    //new Highscore
  //    InitText(Txt_NewHighscore);
  //    while (scrollingtext.UpdateText() != -1) {
  //      FastLED.show();
  //      delay(50);
  //    }
  //  }

  resetDos();
  doNoise = true;
}//end GameOver()

boolean CheckHighscore(long score) {
  boolean newhighscore = false;
  SnakeHighscore = EEPROMReadlong(ScoreEEPROMaddress);
  if (score > SnakeHighscore) {
    EEPROMWritelong(score, ScoreEEPROMaddress);
    newhighscore = true;
  }
  return newhighscore;
}//end CheckScore()

void setSnakeDirection(int dir) {
  if (dir == 1) {
    if (snakeOntop) {
      if (snakeDirection == SNAKE_RIGHT) snakeDirection = SNAKE_UP;
      else if (snakeDirection == SNAKE_DOWN) snakeDirection = SNAKE_RIGHT;
      else if (snakeDirection == SNAKE_LEFT) snakeDirection = SNAKE_DOWN;
      else if (snakeDirection == SNAKE_UP) snakeDirection = SNAKE_LEFT;
    } else {
      if (snakeDirection == SNAKE_RIGHT) snakeDirection = SNAKE_DOWN;
      else if (snakeDirection == SNAKE_DOWN) snakeDirection = SNAKE_LEFT;
      else if (snakeDirection == SNAKE_LEFT) snakeDirection = SNAKE_UP;
      else if (snakeDirection == SNAKE_UP) snakeDirection = SNAKE_RIGHT;
    }
  }
  else if (dir == -1) {
    if (snakeOntop) {
      if (snakeDirection == SNAKE_RIGHT) snakeDirection = SNAKE_DOWN;
      else if (snakeDirection == SNAKE_DOWN) snakeDirection = SNAKE_LEFT;
      else if (snakeDirection == SNAKE_LEFT) snakeDirection = SNAKE_UP;
      else if (snakeDirection == SNAKE_UP) snakeDirection = SNAKE_RIGHT;
    }
    else {
      if (snakeDirection == SNAKE_RIGHT) snakeDirection = SNAKE_UP;
      else if (snakeDirection == SNAKE_DOWN) snakeDirection = SNAKE_RIGHT;
      else if (snakeDirection == SNAKE_LEFT) snakeDirection = SNAKE_DOWN;
      else if (snakeDirection == SNAKE_UP) snakeDirection = SNAKE_LEFT;
    }
  }
  else {
    snakeDirection = -1;
  }
}//end setSnakeDirection()


