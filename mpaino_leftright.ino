//office adafruit: bueno
//tested with two strips connected to one GPIO
#include <FastLED.h>

#define NUM_LEDS  32
#define LED_PIN   11

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(180);

  Serial.begin(115200);
}

void loop() {

  uint16_t sinBeat = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);

  leds[sinBeat] = CRGB::Green;
  
  fadeToBlackBy(leds, NUM_LEDS, 10);
  //fill_solid(leds, NUM_LEDS, CRGB::Red);

  EVERY_N_MILLISECONDS(10){
    Serial.println(sinBeat);
  }

  FastLED.show();
}

/*
uint16_t sinBeat: Declares an unsigned 16-bit integer variable named sinBeat.
beatsin16(30, 0, NUM_LEDS - 1, 0, 0): Calls a function beatsin16 from the FastLED library.
30: Frequency of the sine wave.
0: Starting value for the sine wave.
NUM_LEDS - 1: Ending value for the sine wave (assumes NUM_LEDS is a defined constant).
0: Phase offset.
0: Beats per minute (BPM).
*/
