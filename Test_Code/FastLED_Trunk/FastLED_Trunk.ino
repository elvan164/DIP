#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 79

#define DATA_PIN 6
#define FORWARD 0
#define BACKWARD 1
#define SLOW 250
#define MEDIUM 50
#define FAST 5

CRGB leds[NUM_LEDS];

boolean direction = FORWARD;

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop() { 

  delay(3000);
  colorWipe(CRGB::Black,FORWARD,SLOW);

  for(int i=0; i<2; i++){ 
    colorWipe(randomColor(),FAST,direction);
    direction = !direction;
  }


}

void colorWipe(CRGB c, int speed, int direction){
  for(int i=0; i<NUM_LEDS; i++){
    if(direction == FORWARD){
      leds[i] = c;
    }
    else{
      leds[NUM_LEDS-1-i] = c;
    }
    FastLED.show();
    delay(speed);
  }
}

CRGB Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

CRGB randomColor(){
  return Wheel(random(256)); 
}
