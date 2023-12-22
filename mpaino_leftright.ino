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
