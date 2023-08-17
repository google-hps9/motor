// Arduino get signal from Rpi and control motor
// Stepper Motor with A4988

const int dirPin = 2; // step motor dirPin
const int stepPin = 3; // step motor stepPin
const int stepsPerMove = 40; 
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

void turnLeft() {
	digitalWrite(dirPin, HIGH);
	turn();
}

void turnRight() {
	digitalWrite(dirPin, LOW);
	turn();
}

void setup() {
	Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
	// pinMode(stepPin, OUTPUT);
	// pinMode(dirPin, OUTPUT);
}

void loop() {
	if(Serial.available() > 0) {
		signal = Serial.read();
    if(signal == 'L') {
      // motor rotate left
      // turnLeft();
      digitalWrite(8, HIGH);
      delay(5000);
      digitalWrite(8, LOW);
      Serial.write('F');
    }
    else if(signal == 'R') {
      // motor rotate right
      // turnRight();
      digitalWrite(9, HIGH);
      delay(5000);
      digitalWrite(9, LOW);
      Serial.write('F');
    }
    else {
      // motor stop
      digitalWrite(stepPin, LOW);
    }
	}
  else {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
}