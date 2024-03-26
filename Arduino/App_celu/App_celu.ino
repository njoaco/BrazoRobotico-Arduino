//Proyecto Brazo Robotico
//Codigo para controlar la app del celular
//Creado por: Joaquín Nieto - Ignacio Noé - Mateo Bellone - Santiago Rodriguez

#include <Servo.h>
#include <Stepper.h>
#include <SoftwareSerial.h>

#define dir 2
#define stepp 3
#define MS1 6
#define MS2 5
#define MS3 4

Stepper stepper(200, dir, stepp);  // 200 steps por vuelta, DIR en pin 3, STEP en pin 4
//SoftwareSerial bt(6, 7); //RX, TX - (NO USAR)

//GUÍA DE LETRAS (Control a voz)
//A - Pinza
//G - Muñeca
//B - Antebrazo
//C - Brazo
//D - Base
//H - Rutina 1
//J - Rutina 2
//E - Rutina 3
//Y - Rutina 4
//N - Voz 1 - Brazo a la derecha
//M - Voz 2 - Brazo Recto
//Q - Voz 3 - Brazo a la izquierda
//P - Voz 4 - Antebrazo a la derecha
//O - Voz 5 - Antebrazo a la izquierda
//W - Voz 6 - Abrir garra
//I - Voz 7 - Cerrar garra
//Z - Voz 8 - Mover muñeca
//16 - Velocidad NEMA 1/16
//8 - Velocidad NEMA 1/8
//4 - Velocidad NEMA 1/4
  
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int rutina = 0;
int voz = 0;
int datos_pinza = 90;
int datos_muneca = 90;
int datos_antebrazo = 80;
int datos_brazo = 57;
int nema_speed = 100;
int nema_state = 0;
int datos_base;

char BT_Name[21] = "BrazoRobotico";
char a;
char lastChar;
String readString;

void setup() {

pinMode(LED_BUILTIN, OUTPUT);
rutina = 0;

servo1.attach(10);  //PINZA - GARRA
servo2.attach(8);  //ANTEBRAZO
servo3.attach(7); //BRAZO
servo4.attach(9); //MUÑECA

//bt.begin(9600);
Serial.begin(9600);
Serial.print("AT");       //Inicializar comando AT
delay(50);

Serial.print("AT+NAME");  //Configura el nombre de BT
Serial.print(BT_Name);    
delay(50);

Serial.println("");
Serial.println("");

stepper.setSpeed(nema_speed);  // Velocidad del motor en RPM
servo1.write(datos_pinza);  
servo2.write(datos_antebrazo);
servo3.write(datos_brazo);
servo4.write(datos_muneca);
digitalWrite(MS1, HIGH);
digitalWrite(MS2, HIGH);
digitalWrite(MS3, HIGH);

//pinMode(13,OUTPUT);  //LED de prueba

pinMode(MS1,OUTPUT);
pinMode(MS2,OUTPUT);
pinMode(MS2,OUTPUT);
pinMode(dir, OUTPUT);  // Configuración del pin DIR
pinMode(stepp, OUTPUT);  // Configuración del pin STEP

  
digitalWrite(dir, LOW);  // Establecer DIR en bajo (sentido positivo)
digitalWrite(stepp, LOW);  // Mantener STEP en bajo

Serial.println("Control Brazo Robotico");
Serial.println("");
Serial.println("Datos Pinza: ");
Serial.print(datos_pinza);
Serial.println("");
Serial.println("Datos Muñeca: ");
Serial.print(datos_muneca);
Serial.println("");
Serial.println("Datos Antebrazo: ");
Serial.print(datos_antebrazo);
Serial.println("");
Serial.println("Datos Brazo: ");
Serial.print(datos_brazo);
Serial.println("");
Serial.println("");

delay(10);

}

void loop() {

servo1.write(datos_pinza);
servo2.write(datos_antebrazo);
servo3.write(datos_brazo);
servo4.write(datos_muneca);



if (Serial.available()) {
  
 a = Serial.read();
 lastChar = a;

//MECANICA ========================================================

 if(a=='A' && rutina == 0 && voz == 0){
 pinza();
 }

 if(a=='G'  && rutina == 0 && voz == 0){
 muneca();
 }

 if(a=='B'  && rutina == 0 && voz == 0){
 antebrazo();
 }
 
 if(a=='C' && rutina == 0 && voz == 0){
 brazo();
 }

 if(a=='D' && rutina == 0 && voz == 0){
 base();
 }

//RUTINAS ========================================================

 if(a=='H' && rutina == 0 && voz == 0){    //RUTINA 1
 rutina = 1;
 }

 if(a=='J' && rutina == 0 && voz == 0){    //RUTINA 2
 rutina = 2;
 }

 if(a=='E' && rutina == 0 && voz == 0){    //RUTINA 3
 rutina = 3;
 }

 if(a=='Y' && rutina == 0 && voz == 0){    //RUTINA 4
 rutina = 4;
 }

 if(rutina == 1){
 rutina1();
 }

 if(rutina == 2){
 rutina2();
 }

 if(rutina == 3){
 rutina3();
 }

 if(rutina == 4){
 rutina4();
 }

//VELOCIDAD DE LA BASE ========================================================

 if(a=='1'){
  vel_1_16();
 }
 
 if(a=='2'){
  vel_1_8();
 }

 if(a=='3'){
  vel_1_4();
 }

 if(nema_state == 0){
  vel_1_16();
 }

 if(nema_state == 1){
  vel_1_8();
 }

 if(nema_state == 2){
  vel_1_4();
 }

/*
 if(a=='E'){                  //LED PRUEBA
 digitalWrite(13,HIGH);
 delay(10);
 }
 
 if(digitalRead(2) == LOW){    //LED PRUEBA
 delay(10);
 }
*/

//CONTROL A VOZ ========================================================

 if(a=='N' && rutina == 0){
  voz = 1;
 }

 if(a=='M' && rutina == 0){
  voz = 2;
 }

 if(a=='Q' && rutina == 0){
  voz = 3;
 }

 if(a=='P' && rutina == 0){
  voz = 4;
 }
 
 if(a=='O' && rutina == 0){
  voz = 5;
 }

 if(voz == 1 && rutina == 0){
  voz1();
 }
 
 if(voz == 2 && rutina == 0){
  voz2();
 }

 if(voz == 3 && rutina == 0){
  voz3();
 }

 if(voz == 4 && rutina == 0){
  voz4();
 }

 if(voz == 5 && rutina == 0){
  voz5();
 }
 
}

}




//FUNCIONES DE MECANICA ========================================================

void pinza(){
 delay(10);
 while (Serial.available()) {
 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 datos_pinza = readString.toInt();
 Serial.print("Datos Pinza: ");
 Serial.println(datos_pinza);
 Serial.print("lastChar: ");
 Serial.print(lastChar);
 Serial.println("");
 Serial.println("");
 readString="";
 }
}

void muneca(){
 delay(10);
 while (Serial.available()) {
 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 datos_muneca = readString.toInt();
 Serial.print("Datos Muñeca: ");
 Serial.println(datos_muneca);
 Serial.print("lastChar: ");
 Serial.print(lastChar);
 Serial.println("");
 Serial.println("");
 readString="";
 }
}

void antebrazo(){
 delay(10);
 while (Serial.available()) {
 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 datos_antebrazo = readString.toInt();
 Serial.print("Datos Antebrazo: ");
 Serial.println(datos_antebrazo);
 Serial.print("lastChar: ");
 Serial.print(lastChar);
 Serial.println("");
 Serial.println("");
 readString="";
 }
}

void brazo(){
 delay(10);
 while (Serial.available()) {
 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 datos_brazo = readString.toInt();
 Serial.print("Datos Brazo: ");
 Serial.println(datos_brazo);
 Serial.print("lastChar: ");
 Serial.print(lastChar);
 Serial.println("");
 Serial.println("");
 readString="";
 }
}

void base() {
  delay(10);
  while (Serial.available()) {
    char b = Serial.read();
    readString += b;
  }
  if (readString.length() > 0) {
    int sliderPosition = readString.toInt();
    
    // Asegurar que sliderPosition esté dentro del rango de 10 a 320
    sliderPosition = constrain(sliderPosition, 10, 2000);
    
    Serial.println(sliderPosition);
    
    // Determinar la dirección en función del cambio en la posición del slider
    static int prevSliderPosition = 320;  // Establecer la posición anterior al valor máximo
    int delta = sliderPosition - prevSliderPosition;
    if (delta > 0) {
      digitalWrite(dir, HIGH);  // Incremento en la posición del slider, girar a la derecha
    } else if (delta < 0) {
      digitalWrite(dir, LOW);   // Decremento en la posición del slider, girar a la izquierda
    }
    
    int steps = abs(delta);  // Calcular la cantidad de pasos basados en el cambio en la posición del slider
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepp, HIGH);  // Generar un pulso
      delayMicroseconds(500);  // Ajustar según la velocidad deseada
      digitalWrite(stepp, LOW);
      delayMicroseconds(500);  // Ajustar según la velocidad deseada
    }
    
    prevSliderPosition = sliderPosition;  // Actualizar la posición anterior del slider
    readString = "";  // Limpiar la cadena
  }
}

//FUNCIONES DE RUTINA (NO TERMINADO) ========================================================

void rutina1() {        //Agarrar  (NO TERMINADO)
  //SERVO1 - PINZA
  //SERVO2 - ANTEBRAZO
  //SERVO3 - BRAZO
  //SERVO4 - MUÑECA
  delay(10);
  Serial.println("");
  Serial.println("Rutina 1 - Agarrar.");
  delay(1000);
  Serial.println("Rutina 1 - Posicion inicial");
  datos_pinza = 90; 
  servo1.write(90);     //CAMBIARLO A SERVO.WRITE!!!!!
  datos_muneca = 90; 
  servo4.write(90);
  datos_antebrazo = 80;
  servo2.write(80);
  datos_brazo = 57;
  servo4.write(57);
  delay(1500);
  Serial.println("Rutina 1 - Moviendo brazo...");
  datos_brazo = 160;
  delay(2500);
  Serial.println("Rutina 1 - Moviendo antebrazo...");
  datos_antebrazo = 10;
  delay(2500);
  Serial.println("Rutina 1 - Cerrando Pinza...");
  datos_pinza = 0;
  delay(2500);
  Serial.println("Rutina 1 - Moviendo Brazo y Antebrazo....");
  datos_antebrazo = 80;
  datos_brazo = 57;
  delay(2500);
  Serial.println("Rutina 1 - Rutina terminada.");
  Serial.println("");
  Serial.println(datos_pinza);
  Serial.println(datos_muneca);
  Serial.println(datos_antebrazo);
  Serial.println(datos_brazo);
  Serial.println("lastChar: ");
  Serial.print(lastChar);
  Serial.println("");
  rutina = 0;
  voz = 0;
  a = ' ';
}

void rutina2() {        //Agarre y deje  (NO TERMINADO)
  delay(10);
  Serial.println(""); 
  Serial.println("Rutina 2 - Agarre y deje");
  delay(2500);
  Serial.println("Rutina 2 - Posicion inicial");
  servo3.write(90);
  servo2.write(90);
  delay(2500);
  Serial.println("Rutina 2 - Moviendo brazo...");
  servo3.write(170);
  delay(2500);
  Serial.println("Rutina 2 - Moviendo antebrazo...");
  servo2.write(10);
  delay(2500);
  Serial.println("Rutina 2 - Moviendo brazo...");
  servo3.write(20);
  Serial.println("Rutina 2 - Rutina terminada.");
  Serial.println("");
  Serial.println(datos_pinza);
  Serial.println(datos_muneca);
  Serial.println(datos_antebrazo);
  Serial.println(datos_brazo);
  Serial.println("lastChar: ");
  Serial.print(lastChar);
  Serial.println("");
  rutina = 0;
  voz = 0;
  a = ' ';
}

void rutina3() {        //Abrir/Cerrar garra (NO TERMINADO)
  rutina = 0;
  voz = 0;
  a = ' ';
}

void rutina4() {        //Pos. Inicial      (NO TERMINADO)
  delay(10);
  Serial.println("");
  Serial.println("Rutina 4 - Posicion Inicial.");
  delay(1500);
  datos_pinza = 90;
  datos_muneca = 90;
  datos_antebrazo = 80;
  datos_brazo = 57;
  delay(2500);
  Serial.println("Rutina 4 - Rutina Terminada.");
  Serial.println("");
  Serial.println(datos_pinza);
  Serial.println(datos_muneca);
  Serial.println(datos_antebrazo);
  Serial.println(datos_brazo);
  Serial.println("lastChar: ");
  Serial.print(lastChar);
  Serial.println("");
  rutina = 0;
  voz = 0;
  a = ' ';
}

//FUNCIONES DE VELOCIDAD DE LA BASE ========================================================

void vel_1_16(){
  delay(10);
  nema_state = 0;
  Serial.println("");
  Serial.println("Velocidad NEMA - 1/16");
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  a = ' ';
}

void vel_1_8(){
  delay(10);
  nema_state = 1;
  Serial.println("");
  Serial.println("Velocidad NEMA - 1/8");
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, LOW);
  a = ' ';
}

void vel_1_4(){
  delay(10);
  nema_state = 2;
  Serial.println("");
  Serial.println("Velocidad NEMA - 1/4");
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, LOW);
  a = ' ';
}

/*
void tx() {        //Datos (TX)
  delay(10);
  Serial.println("Datos (TX)");
  Serial.println("");
  Serial.println(datos_pinza);
  Serial.println(datos_muneca);
  Serial.println(datos_antebrazo);
  Serial.println(datos_brazo);
  Serial.println(rutina);
  Serial.println(voz);
  Serial.println("lastChar: ");
  Serial.print(lastChar);
  Serial.println("");
  a = ' ';
}
*/

//FUNCIONES DE COMANDO DE VOZ (NO TERMINADO) ========================================================

void voz1(){        //Brazo Derecha
  delay(10);
  Serial.println("Ejecutando comando de voz...");
  Serial.print("lastChar: ");
  Serial.println(lastChar);
  Serial.print("Voz: ");
  Serial.println(voz);
  Serial.println("");
  Serial.println("");
  datos_brazo = 180;
  servo3.write(180);
  delay(100);
  voz = 0;
}

void voz2(){    //Brazo Recto
  delay(10);
  Serial.println("Ejecutando comando de voz...");
  Serial.print("lastChar: ");
  Serial.println(lastChar);
  Serial.print("Voz: ");
  Serial.println(voz);
  Serial.println("");
  Serial.println("");
  datos_pinza = 90;
  datos_muneca = 90;
  datos_antebrazo = 80;
  datos_brazo = 57;
  delay(100);
  voz = 0;
}

void voz3(){    //Brazo Izquierda
  delay(10);
  Serial.println("Ejecutando comando de voz...");
  Serial.print("lastChar: ");
  Serial.println(lastChar);
  Serial.print("Voz: ");
  Serial.println(voz);
  Serial.println("");
  Serial.println("");
  datos_brazo = 0;
  delay(100);
  voz = 0;
} 

void voz4(){  //Antebrazo Derecha
  delay(10);
  Serial.println("Ejecutando comando de voz...");
  Serial.print("lastChar: ");
  Serial.println(lastChar);
  Serial.print("Voz: ");
  Serial.println(voz);
  Serial.println("");
  Serial.println("");
  datos_antebrazo = 20;
  delay(100);
  voz = 0;
}

void voz5(){  //Antebrazo Izquierda
  delay(10);
  Serial.println("Ejecutando comando de voz...");
  Serial.print("lastChar: ");
  Serial.println(lastChar);
  Serial.print("Voz: ");
  Serial.println(voz);
  Serial.println("");
  Serial.println("");
  datos_antebrazo = 170;
  delay(100);
  voz = 0;
}

void voz6(){  //Abrir Garra (NO TERMINADO)
  delay(10);
  Serial.println("Ejecutando comando de voz...");
  Serial.print("lastChar: ");
  Serial.println(lastChar);
  Serial.print("Voz: ");
  Serial.println(voz);
  Serial.println("");
  Serial.println("");
  datos_pinza = 0;
  delay(100);
  voz = 0;
}

void voz7(){  //Cerrar Garra (NO TERMINADO)
  delay(10);
  Serial.println("Ejecutando comando de voz...");
  Serial.print("lastChar: ");
  Serial.println(lastChar);
  Serial.print("Voz: ");
  Serial.println(voz);
  Serial.println("");
  Serial.println("");
  datos_pinza = 0;
  delay(100);
  voz = 0;
}

void voz8(){  //Mover muñeca (NO TERMINADO)
}

void voz9(){  //Base a la derecha (NO TERMINADO)
}

void voz10(){  //Base a la izquierda (NO TERMINADO)
}
