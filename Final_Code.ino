#include <BasicStepperDriver.h>
#include <DRV8825.h>
#include <MultiDriver.h>
#include <SyncDriver.h>
#include <AccelStepper.h>
#include <Stepper.h>


#define dirPin 8
#define stepPin 9
#define stepsPerRevolution = 200;
#define motorInterfaceType 1 

long loopNumber;
long randomNumber;
unsigned long previousMillis = 0;
unsigned long interval;
int state = 0; 

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

 void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  randomSeed( analogRead(A0) );
  stepper.setMaxSpeed(4000);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  randomNumber = random(213,426);
  int interval = random(30000,60000);
  stepper.setSpeed(randomNumber);
}

void loop() {
  unsigned long currentMillis = millis();
       stepper.runSpeed();
  if (currentMillis - previousMillis > interval and state == 0) {
    previousMillis = currentMillis;
   stepper.setSpeed(randomNumber);
   stepper.runSpeed();
   interval = random(30000,60000);
   randomNumber = random(213,426);
   state = 1; 
  }  
   if (currentMillis - previousMillis > interval and state == 1) {
    previousMillis = currentMillis;
     stepper.setSpeed(randomNumber);
     stepper.runSpeed();
     interval = random(30000,60000); 
     randomNumber = random(213,426);
     state = 0; 
   } 
}
