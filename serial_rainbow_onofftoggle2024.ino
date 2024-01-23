#include <FastLED.h>
#include <elapsedMillis.h>

#define LED_PIN 12
#define LED_PIN_CUBE 11
#define NUM_LEDS 15
#define NUM_LEDS_CUBE 50

CRGB leds[NUM_LEDS];
CRGB ledscube[NUM_LEDS_CUBE];

bool isLedStripOn = false;  // Track the state of the LED strip

elapsedMillis elapsedTime; // Declare elapsedTime as a static variable

void setup() {
  Serial.begin(115200);
  Serial.println("Starting LED Demo");

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_CUBE, GRB>(ledscube, NUM_LEDS_CUBE);
}

/*
void roundStrip(int speed, int ledState) {
  int runTime = 2000;
  bool stripRunning = true;
  static uint8_t startIndex = 0;
  static uint8_t hue = 0;
  unsigned long startTime = millis();

  while (stripRunning && (millis() - startTime < runTime)) {
    // Fill the entire LED strip with a rainbow gradient
    fill_rainbow(leds, NUM_LEDS, hue, 4);

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
  stripRunning = false; //stop iterations

  // Update the LED strip state
  isLedStripOn = (ledState == 1);
}

*/
void roundStrip(int speed, int ledState) {
  int runTime = 2000;
  bool stripRunning = true;

  if (ledState == 1 && isLedStripOn) {
    // If the LED strip is already on and the command is to turn it on, do nothing
    return;
  } else if (ledState == 0 && !isLedStripOn) {
    // If the LED strip is already off and the command is to turn it off, do nothing
    return;
  }

  // Update the LED strip state
  isLedStripOn = (ledState == 1);

  static uint8_t startIndex = 0;
  static uint8_t hue = 0;
  unsigned long startTime = millis();

  while (stripRunning && (millis() - startTime < runTime)) {
    // Fill the entire LED strip with a rainbow gradient
    fill_rainbow(ledscube, NUM_LEDS_CUBE, hue, 4);

    // Move the rainbow effect from left to right
    for (int i = 0; i < NUM_LEDS_CUBE; i++) {
      ledscube[i] = ledscube[(i + startIndex) % NUM_LEDS_CUBE];
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
  fill_solid(ledscube, NUM_LEDS_CUBE, CRGB::Black); // Set all LEDs to black (off)
  FastLED.show();
  stripRunning = false; //stop iterations
}


void processCommand(String command) {
  char separator = ',';

  int firstBracketIndex = command.indexOf('(');
  int secondBracketIndex = command.indexOf(')', firstBracketIndex + 1);

  if (firstBracketIndex != -1 && secondBracketIndex != -1) {
    // Extract motor type and SID from the first set of brackets
    String motorTypeAndSID = command.substring(firstBracketIndex + 1, secondBracketIndex);
    int spaceIndex = motorTypeAndSID.indexOf(' ');

    if (spaceIndex != -1) {
      String motorType = motorTypeAndSID.substring(0, spaceIndex);
      String SID = motorTypeAndSID.substring(spaceIndex + 1);

      Serial.print("SID: ");
      Serial.println(SID);

      // Relay control logic based on motorType
      if (motorType == "LEDSTRIP_OPERATION") {
        int index = secondBracketIndex + 1;
        int nextBracketIndex = command.indexOf('(', index);
        int endIndex = command.indexOf(')', nextBracketIndex + 1);

        if (nextBracketIndex != -1 && endIndex != -1) {
          String inputData = command.substring(nextBracketIndex + 1, endIndex);

          int commaIndex = inputData.indexOf(separator);
          if (commaIndex != -1) {
            int param1 = inputData.substring(0, commaIndex).toInt();
            int param2 = inputData.substring(commaIndex + 1).toInt();

            Serial.print(motorType);
            Serial.print(": Param1: ");
            Serial.print(param1);
            Serial.print(", Param2: ");
            Serial.println(param2);

            if (isLedStripOn && param2 == 1) {
              // If the LED strip is already ON and the command is to turn it ON, do nothing
            } else if (!isLedStripOn && param2 == 0) {
              // If the LED strip is already OFF and the command is to turn it OFF, do nothing
            } else {
              roundStrip(param1, param2); //param1 = speed, param2 = ledState ON(1) or OFF(0)
            }
          } else {
            Serial.println("Invalid LED strip data format");
          }
        }
      } else {
        Serial.println("Unknown motor type");
      }
    } else {
      Serial.println("Invalid motor type and SID format");
    }
  } else {
    Serial.println("Invalid command format");
  }
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
    processCommand(data);
  }
}

//(LEDSTRIP_OPERATION 1647eba3-a6b0-42a7-8a08-ffef8ab07065),(500,0)
