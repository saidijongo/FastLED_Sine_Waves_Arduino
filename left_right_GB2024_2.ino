#include <FastLED.h>

#define NUM_LEDS 32  

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDS); 
  Serial.begin(115200);
}

void loop() {
  movingGreenLeds();
}

void movingGreenLeds() {
  static uint8_t startIndex = 0;  // Starting index of the green LED group
  static bool moveRight = true;   // Direction flag

  // Set the background color to blue
  fill_solid(leds, NUM_LEDS, CRGB::Blue);

  // Set the color of the moving green LEDs
  for (int i = 0; i < 5; ++i) {
    leds[(startIndex + i) % NUM_LEDS] = CRGB::Green;
  }

  FastLED.show();
  FastLED.delay(100);  

  // Clear the LEDs at the current position
  for (int i = 0; i < 5; ++i) {
    leds[(startIndex + i) % NUM_LEDS] = CRGB::Black;
  }

  // Move the green LED group
  if (moveRight) {
    startIndex = (startIndex + 1) % NUM_LEDS;
  } else {
    startIndex = (startIndex + NUM_LEDS - 1) % NUM_LEDS;
  }

  //EVERY_N_MILLISECONDS(100) {
  //  Serial.println(startIndex);}

  // Change direction when reaching the end
  if (startIndex == 0 || startIndex == NUM_LEDS - 5) {
    moveRight = !moveRight;
  }
}
