// @RoboTecs: programa para recibir comandos vía BT y accionar servomotores
// El servo 1 se selecciona con la letra d (base)
// El servo 2 se selecciona con la letra c (brazo)
// El servo 3 se selecciona con la letra b (antebrazo)
// El servo 4 se selecciona con la letra a (pinza)
// Ejemplo de código recibido vía BT: a180x --> Pinza a posición de 180°
// Ejemplo de código recibido vía BT: c90x --> Brazo a posición de 90°

#include <Servo.h>
#include <SoftwareSerial.h>
Servo servo1; //base
Servo servo2; //brazo
Servo servo3; //antebrazo
Servo servo4; //pinza
SoftwareSerial miBT(6, 7); // rx, tx
int pinservo1 = 8;
int pinservo2 = 12;
int pinservo3 = 10;
int pinservo4 = 11;
char car; //caracter recibido vía BT
String incode = ""; //código recibido
boolean encode = false; //fin del recepción

long num1 = 0; //centena 100 grados
long num2 = 0; //decena 10-90 grados
long num3 = 0; //unidad 0-9 grados
long num = 0; //numero recibido 0-180 grados: num1+mun2+num3

void setup() {
  servo1.attach(pinservo1);
  servo2.attach(pinservo2);
  servo3.attach(pinservo3);
  servo4.attach(pinservo4);
  pinMode(pinservo1, OUTPUT); //0 pinza cerrada - 180 pinza abierta
  pinMode(pinservo2, OUTPUT);
  pinMode(pinservo3, OUTPUT);
  pinMode(pinservo4, OUTPUT);
  miBT.begin(9600);
  delay(2000);

  servo1.write(90);
  delay(450);
  servo2.write(120);
  delay(450);
  servo3.write(180);
  delay(450);
  servo4.write(0);
  delay(450);
}

void loop() {
  {
    int longitud = 0;
    if (miBT.available())
    {
      car = miBT.read();
      if (car == 'x') { //x marca el fin del numero enviado via BT
        encode = true;
      }
      else
      {
        incode = (incode + car);
      }
    }

    if (encode) {
      longitud = incode.length();
      char sel = incode.charAt(0); // a, b, c ó d
      num1 = incode.charAt(1); // centena de los grados
      num2 = incode.charAt(2); // decena de los grados
      num3 = incode.charAt(3); // unidad de los grados

      if (longitud == 4) { // p.e. a180, se resta 48 para ajustar el ASCII a un numero
        num = (num1 - 48) * 100 + (num2 - 48) * 10 + num3 - 48;
      }
      if (longitud == 3) { // p.e. c94
        num = (num1 - 48) * 10 + num2 - 48;
      }
      if (longitud == 2) { // p.e. d5
        num = num1 - 48;
      }

      switch (sel) //incode.charAt(0); // a, b, c ó d
      {
        case 'a':
          servo4.write(num); //mueva servo 4 los grados recibidos
          car = '0';
          incode = "";
          encode = false;
          delay(200);
          break;
        case 'b':
          servo3.write(num); //mueva servo 3 los grados recibidos
          car = '0';
          incode = "";
          encode = false;
          delay(200);
          break;
        case 'c':
          servo2.write(num); //mueva servo 2 los grados recibidos
          car = '0';
          incode = "";
          encode = false;
          delay(200);
          break;
        case 'd':
          servo1.write(num); //mueva servo 1 los grados recibidos
          car = '0';
          incode = "";
          encode = false;
          delay(200);
          break;
      }
    }
  }
}
