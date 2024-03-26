#include <Servo.h>

// Definición de pines
const int dirPin = 4;
const int stepPin = 5;
const int servoPin = 3;

// Definición de variables
const int stepsPerRevolution = 200;  // Número de pasos por vuelta del motor (para un motor NEMA 17 típico)
const unsigned long motorDelayTime = 2000; // Tiempo de espera entre vueltas del motor en milisegundos
const unsigned long servoDelayTime = 3000; // Tiempo de espera para el servo en milisegundos

Servo myservo;  // Objeto para controlar el servo motor
int servoPos = 0; // Posición inicial del servo

void setup() {
  // Configuración de pines como salidas
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  
  // Inicialmente establecer la dirección del motor (cambiar según sea necesario)
  digitalWrite(dirPin, HIGH); // Sentido horario

  // Inicialización del servo
  myservo.attach(servoPin);
}

void loop() {
  // Control del motor NEMA 17
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500); // Puedes ajustar este valor según la velocidad del motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500); // Puedes ajustar este valor según la velocidad del motor
  }

  // Control del servo motor
  if (servoPos == 0) {
    servoPos = 180;
  } else {
    servoPos = 0;
  }
  myservo.write(servoPos);

  // Esperar antes de iniciar la siguiente vuelta
  delay(motorDelayTime);

  // Esperar para el movimiento del servo
  delay(servoDelayTime);
}
