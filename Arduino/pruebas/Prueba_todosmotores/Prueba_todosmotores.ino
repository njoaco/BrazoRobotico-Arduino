//Proyecto Brazo Robotico
//Codigo de prueba para testear todos los motores.

#include <Servo.h>
#include <Stepper.h>
#include <SoftwareSerial.h>

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;

int a = 0;
const int dirPin = 3;
const int stepPin = 4;
const float degreesPerStep = 1.8;  // Grados por paso para un motor NEMA 17 (1.8° por paso)
const int stepsPerRevolution = 360 / degreesPerStep;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  servoMotor1.attach(8);
  servoMotor2.attach(9);
  servoMotor3.attach(10);
  servoMotor4.attach(11);

  Serial.begin(9600);
}

void loop() {
  if (a = 0); {
    nema();
    Serial.println("Nema");
    delay(20);
    a++;
  }
   if (a = 1); {
    brazo();
    Serial.println("Brazo");
    delay(20);
    a++;
  }
   if (a = 2); {
    antebrazo();
    Serial.println("Antebrazo");
    delay(20);
    a++;
  }
   if (a = 3); {
    muneca();
    Serial.println("Muñeca");
    delay(20);
    a++;
  }
   if (a = 4); {
    pinza();
    Serial.println("Pinza");
    Serial.println("");
    delay(20);
    a = 0;
  }
}

void nema() {
  delay(10);
  // Girar 360 grados
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);  // Ajusta este valor según la velocidad deseada
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  // Ajusta este valor según la velocidad deseada
  }

  // Esperar 1 segundo
  delay(1000);

  // Mostrar mensaje en la comunicación serial
  //Serial.println("Giro completado");

  // Detenerse por un momento antes de repetir
  delay(1000);
}

void brazo() {
  delay(10);
  servoMotor1.write(180);
  delay(2000);

  servoMotor1.write(0);
  delay(2000);
}

void antebrazo() {
  delay(10);
  servoMotor2.write(180);
  delay(3000);

  servoMotor2.write(0);
  delay(3000);
}

void muneca() {
  delay(10);
  servoMotor3.write(180);
  delay(3500);

  servoMotor3.write(0);
  delay(3500);
}

void pinza() {
  delay(10);
  servoMotor4.write(180);
  delay(4500);

  servoMotor4.write(0);
  delay(4500);
}
