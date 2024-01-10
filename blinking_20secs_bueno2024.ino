#include <FastLED.h>

#define LED_PIN 11
#define NUM_LEDS 32

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
}

void blinkLEDs() {
  const int blinkDuration = 20000;  // 20 seconds
  const int blinkInterval = 500;    // 500 milliseconds (0.5 seconds)

  unsigned long startTime = millis();
  unsigned long previousMillis = 0;

  while (millis() - startTime < blinkDuration) {
    // Check if 20 seconds have elapsed
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 20000) {
      // Turn off LEDs and exit the function
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      return;
    }

    // Turn on all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    delay(blinkInterval);

    // Turn off all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(blinkInterval);
  }

  // Turn off LEDs after the specified duration
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  blinkLEDs();
}
