#include <FastLED.h>

#define NUM_LEDS  50
#define LED_PIN   11

CRGB leds[NUM_LEDS];

void setup() {
  //Adafruit_NeoPixel myLeds = Adafruit_NeoPixel(numPix_2, pinPix_2, NEO_WRGB + NEO_KHZ800);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);

  Serial.begin(115200);

  FastLED.clear(true);
}

void loop () {
  
    uint16_t beatA = beatsin16(50, 0, 255);
    uint16_t beatB = beatsin16(20, 0, 255);
    fill_rainbow(leds, NUM_LEDS, (beatA+beatB)/2, 2);
    
    FastLED.show();
}
