// Arduino get signal from Rpi and control motor
// Stepper Motor with A4988
#include <Wire.h>

const int dirPin = 2; // step motor dirPin
const int stepPin = 3; // step motor stepPin
const int rstPin = 4;
const int stepsPerMove = 100; 
char signal; // from Serial, 'L' for left, 'R' for right

void turn() {
	for(int x = 0; x < stepsPerMove; x++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(1500); // longer -> slower
		digitalWrite(stepPin, LOW);
		delayMicroseconds(1500);
	}
}

void turnRight() {
	digitalWrite(dirPin, HIGH);
	turn();
}

void turnLeft() {
	digitalWrite(dirPin, LOW);
	turn();
}

void setup() {
	Serial.begin(9600);
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
  pinMode(rstPin, OUTPUT);
  Wire.begin(3);
  Wire.onReceive(receiveEvent);
}

void loop() {
  digitalWrite(stepPin, LOW);
  digitalWrite(rstPin, LOW);  
  delay(100);
}

void receiveEvent(int numBytes) {
  while(Wire.available()) { 
    char c = Wire.read();
    Serial.print(c);
    digitalWrite(rstPin, HIGH);
    if(c == 'R') {
      // motor rotate left
      turnLeft();
      delay(2000);
      turnRight();
      Serial.write('F');
    }
    else if(c == 'L') {
      // motor rotate right
      turnRight();
      delay(2000);
      turnLeft();
      Serial.write('F');
    }
    else {
      digitalWrite(stepPin, LOW);
    }
  }
}