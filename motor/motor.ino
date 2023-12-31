// Arduino get signal from Rpi and control motor
// Stepper Motor with A4988

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
}

void loop() {
  digitalWrite(rstPin, LOW); 
	if(Serial.available() > 0) {
		signal = Serial.read();
    digitalWrite(rstPin, HIGH);
    if(signal == 'L') {
      // motor rotate left
      turnLeft();
      delay(2000);
      turnRight();
      Serial.write('F');
    }
    else if(signal == 'R') {
      // motor rotate right
      turnRight();
      delay(2000);
      turnLeft();
      Serial.write('F');
    }
    // else {
    //   // motor stop
    //   digitalWrite(stepPin, LOW);
    // }
	}
  else {
    digitalWrite(stepPin, LOW);
    digitalWrite(rstPin, LOW);  
  }
}