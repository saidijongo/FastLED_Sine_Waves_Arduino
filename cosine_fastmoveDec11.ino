#include <FastLED.h>

#define LED_AMOUNT        35
#define DATA_PIN          11
#define GLOBAL_BRIGHTNESS 100

#define FRAGMENT_AMOUNT   5
#define FRAGMENT_SIZE     (LED_AMOUNT / FRAGMENT_AMOUNT)
#define FRAGMENT_MIDPOINT (FRAGMENT_SIZE / 2)

CRGB leds[LED_AMOUNT];

float move = 0;

float midpoints[FRAGMENT_AMOUNT];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, LED_AMOUNT);
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);

  for (int fragment = 0; fragment < FRAGMENT_AMOUNT; fragment++) {
    midpoints[fragment] = FRAGMENT_MIDPOINT + (fragment * FRAGMENT_SIZE);
  }
}

void loop() {
  FastLED.clear();

  float spread = FRAGMENT_MIDPOINT * ((sin(move) + 1) / 2);
  float step = PI / spread;

  for (int fragment = 0; fragment < FRAGMENT_AMOUNT; fragment++) {
    midpoints[fragment] += 0.05;

    if (midpoints[fragment] > LED_AMOUNT) midpoints[fragment] = 0;

    int pos = midpoints[fragment];

    for (int i = 0; i <= spread; ++i) {

      float hue = map(i, 0, spread, 0, 255); // Map the position to the hue spectrum
      leds[(pos + i) % LED_AMOUNT] = CHSV(hue, 255, 255);

      if (pos - i < 0) {
        leds[pos - i + LED_AMOUNT] = CHSV(hue, 255, 255);
      } else
        leds[pos - i] = CHSV(hue, 255, 255);
    }
  }

  FastLED.show();

  move += 0.005;
}
