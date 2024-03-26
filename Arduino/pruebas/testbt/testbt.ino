#include <SoftwareSerial.h>

//SIEMPRE  AL REVEZ
//PIN 2 TX (RX)
//PIN 3 RX (TX)

SoftwareSerial blue (2, 3);

char NOMBRE[21] = "SEGUNDOPISO";
char BPS = '4';
char PASS[5] = "0004";

void setup() {
  blue.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(7, HIGH);
  delay(4000);

  digitalWrite(13, LOW);
  digitalWrite(7, LOW );

  blue.print("AT");
  delay(1000);

  blue.print("AT+NAME");
  blue.print(NOMBRE);
  delay(1000);

  blue.print("AT+BAUD");
  blue.print(BPS);
  delay(1000);

  blue.print("AT+PIN");
  blue.print(PASS);
  delay(1000);

}

void loop() {
  digitalWrite(13, !digitalRead(13));
  digitalWrite(7, !digitalRead(7));
  delay(300);

}
