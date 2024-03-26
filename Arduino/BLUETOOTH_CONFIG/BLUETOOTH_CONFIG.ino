#include <SoftwareSerial.h>

char NOMBRE[21] = "BrazoRobotico";

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(7, HIGH);
  delay(4000);

  digitalWrite(13, LOW);
  digitalWrite(7, LOW );

  Serial.print("AT");
  delay(1000);

  Serial.print("AT+NAME");
  Serial.print(NOMBRE);
  delay(1000);

/*  
  Serial.print("AT+BAUD");
  Serial.print(BPS);
  delay(1000);

  Serial.print("AT+PIN");
  Serial.print(PASS);
  delay(1000);
*/
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  digitalWrite(7, !digitalRead(7));
  delay(300);

}
