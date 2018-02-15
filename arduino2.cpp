#include "Arduino.h"

#define stopPins 2
#define moveUpPin 12
#define moveDownPin 13

#define directionPin 4
#define phasePin 7

volatile boolean wasAlreadyStop = false;
volatile boolean isStopButtonPressed = false;

void setup()
{
	pinMode(stopPins, INPUT);
	attachInterrupt(digitalPinToInterrupt(stopPins), stopChange, CHANGE);

	pinMode(moveUpPin, INPUT);
	pinMode(moveDownPin, INPUT);
	pinMode(directionPin, OUTPUT);
	pinMode(phasePin, OUTPUT);
	boolean movingUp = false;
	boolean movingDown = false;
}




void loop()
{
	boolean moveUp = digitalRead(moveUpPin);
	boolean moveDown = digitalRead(moveDownPin);

	if (!isStopButtonPressed) {
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
	} else {

		digitalWrite (directionPin, LOW);
		digitalWrite (phasePin, LOW);
		isStopButtonPressed = false;

		if (movingUp && moveDownPin) {
			movingUp = false;
			movingDown = true;
			digitalWrite (directionPin, LOW);
			digitalWrite (phasePin, HIGH);
		}
		if (movingDown && moveUpPin) {
			movingUp = true;
			movingDown = false;
			digitalWrite (directionPin, HIGH);
			digitalWrite (phasePin, HIGH);
		}		
	}
	
	if (wasAlreadyStop && digitalRead(moveUpPin)) {
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
	isStopButtonPressed = true;
	wasAlreadyStop = true;
}
