#include <FastLED.h>
#include <elapsedMillis.h>

#define LED_PIN 11
#define NUM_LEDS 32

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
}

void ledStrip(int speed, int runTime) {
  elapsedMillis elapsedTime; // Track elapsed time
  unsigned long startTime = millis();
  unsigned long currentTime;

  // Set the background color to blue
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();

  while (elapsedTime < runTime) {
    currentTime = millis(); // Update currentTime

    // Move the group of 5 green LEDs from left to right
    for (int i = 0; i <= NUM_LEDS - 5; ++i) {
      fill_solid(leds + i, 5, CRGB::Green);
      FastLED.show();
      delay(speed);
      fill_solid(leds + i, 5, CRGB::Blue);

      // Check if runtime exceeded
      if (currentTime - startTime >= runTime) {
        FastLED.clear();
        FastLED.show();
        return;
      }
    }

    // Move the group of 5 green LEDs from right to left
    for (int i = NUM_LEDS - 5; i >= 0; --i) {
      fill_solid(leds + i, 5, CRGB::Green);
      FastLED.show();
      delay(speed);
      fill_solid(leds + i, 5, CRGB::Blue);

      // Check if runtime exceeded
      if (currentTime - startTime >= runTime) {
        FastLED.clear();
        FastLED.show();
        return;
      }
    }
  }

  // Turn off LEDs after the specified duration
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  ledStrip(100, 2000);
}
