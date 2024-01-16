#include <FastLED.h>
#include <elapsedMillis.h>

#define NUM_LEDS 32
#define LED_PIN 11
#define BRIGHTNESS 100

CRGB leds[NUM_LEDS];
elapsedMillis elapsedTime; // Declare elapsedTime as a static variable

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(115200);
}

void roundStrip(int speed, int runTime) {
  static uint8_t startIndex = 0;
  static uint8_t hue = 0;
  unsigned long startTime = millis();

  while (millis() - startTime < runTime) {
    // Fill the entire LED strip with a rainbow gradient
    fill_rainbow(leds, NUM_LEDS, hue, 2);

    // Move the rainbow effect from left to right
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = leds[(i + startIndex) % NUM_LEDS];
    }

    FastLED.show();
    FastLED.delay(speed);

    // Increment the rainbow hue to change colors
    hue++;

    // Move the rainbow gradient index
    startIndex++;
    if (startIndex >= NUM_LEDS) {
      startIndex = 0;
    }
  }

  // Turn off LEDs after the runTime
  fill_solid(leds, NUM_LEDS, CRGB::Black); // Set all LEDs to black (off)
  FastLED.show();
  FastLED.delay(1000); // Delay for one second to observe the off state
}

void loop() {
  roundStrip(100, 2000);
}
