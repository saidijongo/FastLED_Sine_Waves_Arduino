#include <FastLED.h>
#include <elapsedMillis.h>

#define LED_PIN 11
#define NUM_LEDS 32
CRGB leds[NUM_LEDS];

#define CUBE_LED_PIN 12
#define NUM_LEDS_CUBE 15
CRGB cube_leds[NUM_LEDS_CUBE];

elapsedMillis elapsedTime; 

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, CUBE_LED_PIN, GRB>(cube_leds, NUM_LEDS_CUBE);
}

void roundStrip(int speed, int runTime) {
  bool stripRunning = true;
  static uint8_t startIndex = 0;
  static uint8_t hue = 0;
  unsigned long startTime = millis();

  while (stripRunning && (millis() - startTime < runTime)) {
    // Fill the entire LED strip with a rainbow gradient
    fill_rainbow(cube_leds, NUM_LEDS_CUBE, hue, 4);

    // Move the rainbow effect from left to right
    for (int i = 0; i < NUM_LEDS_CUBE; i++) {
      cube_leds[i] = cube_leds[(i + startIndex) % NUM_LEDS_CUBE];
    }

    FastLED.show();
    FastLED.delay(speed);

    // Increment the rainbow hue to change colors
    hue++;

    // Move the rainbow gradient index
    startIndex++;
    if (startIndex >= NUM_LEDS_CUBE) {
      startIndex = 0;
    }
  }

  // Turn off LEDs after the runTime
  fill_solid(cube_leds, NUM_LEDS_CUBE, CRGB::Black); // Set all LEDs to black (off)
  FastLED.show();
  stripRunning = false; // stop iterations
}

void ledStrip(int speed, int runTime) {
  unsigned long startTime = millis();
  unsigned long currentTime;

  // Set the background color to blue
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  while (elapsedTime < runTime) {
    currentTime = millis(); // Update currentTime

    // Move the group of 5 green LEDs from left to right
    for (int i = 0; i <= NUM_LEDS - 5; ++i) {
      fill_solid(leds + i, 5, CRGB::Green); // Set a group of 5 LEDs to green
      FastLED.show();
      delay(speed);
      fill_solid(leds + i, 5, CRGB::Blue); // Set the same group back to blue
    }

    // Move the group of 5 green LEDs from right to left
    for (int i = NUM_LEDS - 5; i >= 0; --i) {
      fill_solid(leds + i, 5, CRGB::Green); // Set a group of 5 LEDs to green
      FastLED.show();
      delay(speed);
      fill_solid(leds + i, 5, CRGB::Blue); // Set the same group back to blue
    }

    // Check if runtime exceeded
    if (currentTime - startTime >= runTime) {
      break;
    }
  }
  // Turn off LEDs after the runTime
  fill_solid(leds, NUM_LEDS, CRGB::Black); // Set all LEDs to black (off)
  FastLED.show();
}

void blinkLEDs() {
  const int blinkDuration = 20000;  // 20 seconds
  const int blinkInterval = 500;   // 500 milliseconds (0.5 seconds)

  static elapsedMillis elapsedTime; // Track elapsed time

  while (elapsedTime < blinkDuration) {
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
  ledStrip(100, 2000);
  //delay(1000);
  //roundStrip(100, 2000);
  delay(1000);
  blinkLEDs();
  //delay(1000);
  //roundStrip(100, 2000);
}
