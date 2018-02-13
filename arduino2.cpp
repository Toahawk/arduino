#include "Arduino.h"

#define emergencyStopPin 2
#define moveUpPin 12
#define moveDownPin 13

#define directionPin 4
#define phasePin 7

volatile boolean isEmergencyButtonPressed = false;

void setup()
{
	pinMode(emergencyStopPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(emergencyStopPin), emergencyStopChange, CHANGE);

	pinMode(moveUpPin, INPUT);
	pinMode(moveDownPin, INPUT);
	pinMode(directionPin, OUTPUT);
	pinMode(phasePin, OUTPUT);
	boolean movingUp = false;
	boolean movingDown = false;
	boolean wasAlreadyStop = false;
}




void loop()
{
	boolean moveUp = digitalRead(moveUpPin);
	boolean moveDown = digitalRead(moveDownPin);

	if (!isEmergencyButtonPressed) {
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
		isEmergencyButtonPressed = false;

		if (movingUp && moveDownPin) {
			# isEmergencyButtonPressed = false;
			movingUp = false;
			movingDown = true;
			digitalWrite (directionPin, LOW);
			digitalWrite (phasePin, HIGH);
		}
		if (movingDown && moveUpPin) {
			# isEmergencyButtonPressed = false;
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

void emergencyStopChange() {
	isEmergencyButtonPressed = true;
	wasAlreadyStop = true;
}
