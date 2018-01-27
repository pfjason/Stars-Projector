/*
  LICENSE
  Copyright 2018 Jason Aquino

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
  sell copies of the Software, and to permit persons to whom the Software is 
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice 
  shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS",
  WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
  TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
  FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


/// Arduino Pins
/*
  #define LED_RED 9
  #define LED_GREEN 5
  #define LED_BLUE 3
  #define LED_YELLOW 6
  #define SWITCH 4
  //*/

/// ATTINY85 PINS
/*
  #define LED_RED 0
  #define LED_GREEN 1
  #define LED_BLUE 3 // NOT PWM!
  #define LED_YELLOW 4
  #define SWITCH 2
//*/


/// ATTINY84 PINS
///*
#define LED_RED 7
#define LED_GREEN 8
#define LED_BLUE 6
#define LED_YELLOW 5
#define SWITCH 9
//*/

#define MIN_ON_SECONDS 5
#define MAX_ON_SECONDS 10
#define DIM_DELAY_MIN 10
#define DIM_DELAY_MAX 40

int LEDS[4] = {LED_RED, LED_GREEN, LED_BLUE, LED_YELLOW};

void setup() {
  
  randomSeed(analogRead(2)); // Set this to an analog pin that is not connected

  // To make sure everything is working we light 
  // up all the LEDS to their max brightness and dim them one by one  
  for (int i = 0; i < 4; i++)
  {
    analogWrite(LEDS[i], getMaxBrightness(LEDS[i]));
  }

  for (int i = 0; i < 4; i++)
  {
    for (int level = getMaxBrightness(LEDS[i]); level < 255 ; level++) {
      analogWrite(LEDS[i], level);
      delay(DIM_DELAY_MIN);
    }
    digitalWrite(LEDS[i], HIGH);

  }
}

int getMaxBrightness(int led)
{
  //To compensate for differences in LED brightness, we set the max brightness per LED.
  // Because we're using the pwm pin as a sink, 0 is brightest and 254 is off.
  int maxBright = 0;
  switch (led)
  {
    case LED_BLUE:
      maxBright = 220;
      break;
    case LED_GREEN:
      maxBright = 128;
      break;
    default:
      maxBright = 0;
  }
  return maxBright;
}

void loop() {
  int led = random(0, 4);
  int dimdelay = random(DIM_DELAY_MIN, DIM_DELAY_MAX + 1);
  int timeout = random(MIN_ON_SECONDS, MAX_ON_SECONDS + 1);
  int maxBright = getMaxBrightness(LEDS[led]);

  for (int i = 254; i >= maxBright; i--)
  {
    analogWrite(LEDS[led], i);
    delay(dimdelay);
  }

  delay(timeout * 1000 );
  for (int i = maxBright; i <= 254 ; i++)
  {
    delay(dimdelay);
    analogWrite(LEDS[led], i);
  }
  digitalWrite(LEDS[led], HIGH);
}
