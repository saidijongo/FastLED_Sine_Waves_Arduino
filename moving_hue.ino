#include <FastLED.h>

#define NUM_LEDS  8
#define LED_PIN   8

CRGB leds[NUM_LEDS];

uint8_t hue = 0;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10); //0-255

  Serial.begin(115200);
}

void loop() {

  uint8_t pos = map(beat16(40, 0), 0, 65535, 0, NUM_LEDS -1);
  leds[pos] = CHSV( hue, 200, 250);

  fadeToBlackBy(leds, NUM_LEDS, 2);

  EVERY_N_MILLISECONDS( 10 ) {
    hue++;
  }

  EVERY_N_MILLISECONDS(10) {
    Serial.println(pos);
  }
  
  FastLED.show();

}
