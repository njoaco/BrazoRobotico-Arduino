#include <AccelStepper.h>
#include <Servo.h>


#define DIR_PIN 4
#define STEP_PIN 5
#define STEPS_PER_REVOLUTION 200
#define DEGREES_PER_STEP 360.0 / STEPS_PER_REVOLUTION

AccelStepper stepper(AccelStepper::FULL4WIRE, STEP_PIN, DIR_PIN);

#define SERVO_PIN 7

Servo servoMotor;

void setup() {
  pinMode(SERVO_PIN, OUTPUT);
  servoMotor.attach(SERVO_PIN);

  stepper.setMaxSpeed(200);  // Adjust this value to set the speed of the stepper motor
  stepper.setAcceleration(200);  // Adjust this value to set the acceleration of the stepper motor
}

void loop() {
  // Perform a 45-degree rotation with the stepper motor
  int steps = STEPS_PER_REVOLUTION / 8;

  for (int i = 0; i < steps; i++) {
    stepper.runSpeed();
  }

  // Rotate the servo motor to a specific position (0 degrees)
  servoMotor.write(0);
  delay(1000); // Wait for 1 second

  // Rotate the servo motor to a different position (90 degrees)
  servoMotor.write(90);
  delay(1000); // Wait for 1 second
}
