
#include <Stepper.h>

const int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution, 8, 11, 12, 13);

const int trigPin = 7;
const int echoPin = 6;

const int distanceThreshold = 30;

void setup() {
 
  myStepper.setSpeed(15);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < distanceThreshold)
  {
    
    Serial.println("Obstacle detected! Stopping motor.");
    myStepper.step(stepsPerRevolution / 10);
  } 
  else {
  
    Serial.println("No obstacle. Motor running.");
    myStepper.step(stepsPerRevolution / 100);
  }

  delay(100);
}

long getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  long duration = pulseIn(echoPin, HIGH);
 
  long distance = duration * 0.034 / 2;
 
  return distance;
}
