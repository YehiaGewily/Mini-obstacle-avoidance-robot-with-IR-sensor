#include <Arduino.h>

// Motor pins
int rightMotorEnable = 13;
int rightMotorInput1 = 5;
int rightMotorInput2 = 3;
int leftMotorEnable = 12;
int leftMotorInput3 = 6;
int leftMotorInput4 = 9;

// IR sensor pins
int rightIR = A1;
int middleIR = A2;
int leftIR = A3;

void setup() {
  Serial.begin(9600);
  // Initialize motor pins as outputs
  pinMode(rightMotorEnable, OUTPUT);
  pinMode(rightMotorInput1, OUTPUT);
  pinMode(rightMotorInput2, OUTPUT);
  pinMode(leftMotorEnable, OUTPUT);
  pinMode(leftMotorInput3, OUTPUT);
  pinMode(leftMotorInput4, OUTPUT);

  // Initialize IR sensors as inputs
  pinMode(rightIR, INPUT);
  pinMode(middleIR, INPUT);
  pinMode(leftIR, INPUT);
  digitalWrite(rightMotorEnable, HIGH);
  digitalWrite(leftMotorEnable, HIGH);

}

void loop() {
  int leftIRValue = digitalRead(leftIR);
  int middleIRValue = digitalRead(middleIR);
  int rightIRValue = digitalRead(rightIR);
  
  Serial.print("Left IR: ");
  Serial.print(leftIRValue);
  Serial.print(" | Middle IR: ");
  Serial.print(middleIRValue);
  Serial.print(" | Right IR: ");
  Serial.println(rightIRValue);
  
  // Decide the robot movement based on IR sensor values
  if (leftIRValue == 0 && middleIRValue == 0 && rightIRValue == 0) {
    Serial.println("Obstacle Everywhere: Turning Around");
    turnAround();
  } else if (leftIRValue == 0 && middleIRValue == 0 && rightIRValue == 1) {
    Serial.println("Obstacle Left and Middle: Turning Right");
    turnRight();
  } else if (leftIRValue == 0 && middleIRValue == 1 && rightIRValue == 0) {
    Serial.println("Clear Path: Moving Forward");
    turnAround();
  } else if (leftIRValue == 0 && middleIRValue == 1 && rightIRValue == 1) {
    Serial.println("Obstacle Left: Turning Right");
    turnRight();
  } else if (leftIRValue == 1 && middleIRValue == 0 && rightIRValue == 0) {
    Serial.println("Obstacle Right and Middle: Turning Left");
    turnLeft();
  } else if (leftIRValue == 1 && middleIRValue == 0 && rightIRValue == 1) {
    Serial.println("Obstacle Middle: Moving Slowly or Turn Around");
    turnAround(); // Or implement a slow forward movement if preferred
  } else if (leftIRValue == 1 && middleIRValue == 1 && rightIRValue == 0) {
    Serial.println("Obstacle Right: Turning Left");
    turnLeft();
  } else if (leftIRValue == 1 && middleIRValue == 1 && rightIRValue == 1) {
    Serial.println("No Obstacle: Moving Forward");
    moveForward();
  }

  delay(100); // Short delay to stabilize readings and reduce serial output speed
}
void moveForward() {

  digitalWrite(rightMotorInput1, HIGH);
  digitalWrite(rightMotorInput2, LOW);
  digitalWrite(leftMotorInput3, HIGH);
  digitalWrite(leftMotorInput4, LOW);
}

void turnRight() {

  digitalWrite(rightMotorInput1, LOW);  // Stop right motor
  digitalWrite(rightMotorInput2, HIGH);
  digitalWrite(leftMotorInput3, HIGH);  // Left motor moves forward
  digitalWrite(leftMotorInput4, LOW);
}

void turnLeft() {

  digitalWrite(rightMotorInput1, HIGH);  // Right motor moves forward
  digitalWrite(rightMotorInput2, LOW);
  digitalWrite(leftMotorInput3, LOW);    // Stop left motor
  digitalWrite(leftMotorInput4, HIGH);
}

void turnAround() {

  digitalWrite(rightMotorInput1, HIGH);
  digitalWrite(rightMotorInput2, LOW);  // Right motor reverse
  digitalWrite(leftMotorInput3, LOW);   // Left motor forward
  digitalWrite(leftMotorInput4, HIGH);
}