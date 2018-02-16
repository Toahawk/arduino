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
		if (movingUp && moveDown) {
			movingUp = false;
			movingDown = true;
			digitalWrite (directionPin, LOW);
			digitalWrite (phasePin, HIGH);
		}
		if (movingDown && moveUp) {
			movingUp = true;
			movingDown = false;
			digitalWrite (directionPin, HIGH);
			digitalWrite (phasePin, HIGH);
		}		
	} else {
		digitalWrite (directionPin, LOW);
		digitalWrite (phasePin, LOW);
		isStopButtonPressedOrEndStop = false;
	}
	
	if (wasAlreadyStop && moveUp) {
		digitalWrite (directionPin, HIGH);
		digitalWrite (phasePin, HIGH);
		delay (5);
		digitalWrite (directionPin, LOW);
		digitalWrite (phasePin, LOW);	
		wasAlreadyStop = false;
	}	
	delay(10);
}

void stopChange() {
	isStopButtonPressedOrEndStop = true;
	wasAlreadyStop = true;
	movingDown = false;
	movingUp = false;
}
