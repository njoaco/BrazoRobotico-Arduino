#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
char a;
String readString;
void setup() {
 pinMode(13,OUTPUT);
 servo1.attach(8);  //PINZA
 servo5.attach(12); //MUÑECA
 servo2.attach(9);  //ANTEBRAZO
 servo3.attach(10); //BRAZO
 servo4.attach(11); //BASE (Hay que cambiarlo a un NEMA)
 Serial.begin(9600);
servo1.write(90);   //servo1.write(90);
servo2.write(90);  //servo2.write(100);
servo3.write(90);  //servo3.write(164);
servo4.write(90);   //servo4.write(90);
servo5.write(90);   //servo5.write(90);
delay(10);
}
void loop() {
if (Serial.available()) {
 a = Serial.read();

 if(a=='A'){
 motor1();
 }

 if(a=='B'){
 motor2();
 }

 if(a=='C'){
 motor3();
 }
 if(a=='D'){
 motor4();
 }
 if(a=='E'){
 digitalWrite(13,HIGH);
 delay(10);
 }
 if(a=='F'){
 digitalWrite(13,LOW);
 delay(10);
 }
 if(a=='G'){
 motor5();
 }
 }
}

void motor1(){
 delay(10);
 while (Serial.available()) {

 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 Serial.println(readString.toInt());
 servo1.write(readString.toInt());
 readString=""; // Clear string
 }
}
void motor2(){
 delay(10);
 while (Serial.available()) {
 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 Serial.println(readString.toInt());
 servo2.write(readString.toInt());
 readString="";
 }
}
void motor3(){
 delay(10);
 while (Serial.available()) {
 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 Serial.println(readString.toInt());
 servo3.write(readString.toInt());
 readString="";
 }
}
void motor4(){
 delay(10);
 while (Serial.available()) {
 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 Serial.println(readString.toInt());
 servo4.write(readString.toInt());
 readString="";
 }
}
void motor5(){
 delay(10);
 while (Serial.available()) {
 char b = Serial.read();
 readString += b;
 }
 if (readString.length() >0) {
 Serial.println(readString.toInt());
 servo5.write(readString.toInt());
 readString="";
 }
}
