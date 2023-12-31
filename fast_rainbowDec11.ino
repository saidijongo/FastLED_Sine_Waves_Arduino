#include<FastLED.h>

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

  for(int fragment = 0; fragment < FRAGMENT_AMOUNT; fragment++){
    midpoints[fragment] = FRAGMENT_MIDPOINT + (fragment * FRAGMENT_SIZE);
  }
}

void loop() {

  FastLED.clear();

  float spread = FRAGMENT_MIDPOINT * ((sin(move) + 1) / 2);
  float step = PI / spread;

  for(int fragment = 0; fragment < FRAGMENT_AMOUNT; fragment++){
    midpoints[fragment] += 0.05;

    if(midpoints[fragment] > LED_AMOUNT) midpoints[fragment] = 0;
    
    int pos = midpoints[fragment];

    for(int i=0; i<= spread; ++i){
      
      float brightness = cos(i * step);
      brightness = (brightness + 1) / 2;
      brightness *= 255;

      // Replace the white color with Rainbow color
      leds[(pos+i) % LED_AMOUNT] = CHSV(i * 255 / spread, 255, brightness);

      if( pos - i < 0) {
        leds[pos - i + LED_AMOUNT] = CHSV(i * 255 / spread, 255, brightness);
      }
      else leds[pos - i] = CHSV(i * 255 / spread, 255, brightness);
    }
  }

  FastLED.show();

  move += 0.005;
}
