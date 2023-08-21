// When IR detects people coming, LED turned on
#include <FastLED.h> // using WS2812

const int IRPin = 9;
const int sec = 3; // time for led on after detecting a person
const int ledPin = 5;
const int ledNum = 18; // number of LED
const int ledBrightness = 15;
CRGB leds[ledNum];

void lightOn() {
    for(int i = 0; i < ledNum; i++) {
        leds[i] = 0x777777;
        FastLED.show();
    }
}

void lightOff() {
    for(int i = 0; i < ledNum; i++) {
        leds[i] = CRGB::Black;
        FastLED.show();
    }
}

void setup() {
    pinMode(IRPin, INPUT); // IR Sensor pin INPUT
    FastLED.addLeds<WS2812, ledPin, RGB>(leds, ledNum);  // GRB ordering is typical
    Serial.begin(9600);
}

void loop() {
    if(!digitalRead(IRPin)) {
        lightOn();
        delay(sec * 1000);
    }
    else {
        lightOff();
    }
}