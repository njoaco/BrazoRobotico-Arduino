// Definición de pines
const int dirPin = 2;
const int stepPin = 3;

// Variables de control
const float degreesPerStep = 1.8;  // Grados por paso para un motor NEMA 17 (1.8° por paso)
const int stepsPerRevolution = 360 / degreesPerStep;

void setup() {
  // Configurar pines como salidas
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  
  // Inicializar dirección (sentido de giro)
  digitalWrite(dirPin, HIGH);  // Cambia a LOW si quieres que el motor gire en sentido contrario
  
  // Iniciar comunicación serial (opcional)
  Serial.begin(9600);
}

void loop() {
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
  Serial.println("Giro completado");

  // Detenerse por un momento antes de repetir
  delay(1000);
}
