#include "Arduino.h"
 
#define emergencyStopPin 2
#define moveUpPin 12
#define moveDownPin 13
 
#define directionPin 4
#define phasePin 7
 
volatile boolean stopped = false;
 
void setup()
{
                  pinMode(emergencyStopPin, INPUT);
                  attachInterrupt(digitalPinToInterrupt(emergencyStopPin), emergencyStopChange, CHANGE);
 
                  pinMode(moveUpPin, INPUT);
                  pinMode(moveDownPin, INPUT);
                  pinMode(directionPin, OUTPUT);
                  pinMode(phasePin, OUTPUT);
}

void loop()
{
                boolean moveUp = digitalRead(moveUpPin);
                boolean moveDown = digitalRead(moveDownPin);
                boolean movingUp = false;
                boolean movingDown = false;
 
                if (!stopped) {
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
                }
                delay(10);
}
 
void emergencyStopChange() {
                boolean  emergencyButtonPressed = true;
}