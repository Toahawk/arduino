#include "Arduino.h"

#define stopPins 2
#define moveUpPin 12
#define moveDownPin 13

#define directionPin 4
#define phasePin 7

volatile boolean wasAlreadyStop = false;
volatile boolean isStopButtonPressedOrEndStop = false;
volatile boolean movingUp = false;
volatile boolean movingDown = false;

void setup()
{
	pinMode(stopPins, INPUT);
	attachInterrupt(digitalPinToInterrupt(stopPins), stopChange, CHANGE);

	pinMode(moveUpPin, INPUT);
	pinMode(moveDownPin, INPUT);
	pinMode(directionPin, OUTPUT);
	pinMode(phasePin, OUTPUT);
}

void loop()
{
	boolean moveUp = digitalRead(moveUpPin);
	boolean moveDown = digitalRead(moveDownPin);

	if (!isStopButtonPressedOrEndStop) {
		if (movingUp || moveUp) {
			movingUp = true;
			movingDown = false;
			digitalWrite (directionPin, HIGH);
			digitalWrite (phasePin, HIGH);
		}
		if (movingDown || moveDown) {
			movingUp = false;
			movingDown = true;
			digitalWrite (directionPin, LOW);
			digitalWrite (phasePin, HIGH);
		}
		delay(10);
	} else {
		movingDown = false;
		movingUp = false;
		digitalWrite (directionPin, LOW);
		digitalWrite (phasePin, LOW);
		isStopButtonPressedOrEndStop = false;

		if (moveUp) {
			digitalWrite (directionPin, HIGH);
			digitalWrite (phasePin, HIGH);
			delay (5);
			digitalWrite (directionPin, LOW);
			digitalWrite (phasePin, LOW);	
		}
	}
}

void stopChange() {
	isStopButtonPressedOrEndStop = true;
}
