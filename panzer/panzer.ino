#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <analogWrite.h>
#include <Servo.h>

#define R1 25
#define R2 26
#define RSpeed 27
#define L1 33
#define L2 32
#define LSpeed 5
#define Leds 17
#define Fire 16
#define servoRLpin 4
#define servoUDpin 0

char auth[] = "qbOwS1e6ZyWH49HYNchxHtK1CkfiiXJD";
char ssid[] = "DRAGON";
char pass[] = "P48palaestina";

int minRange = 312;
int maxRange = 712;

int minSpeed = 150;
int maxSpeed = 200; //maximal. 255
int noSpeed = 0;

int posRL = 60;
int posUD = 60;
Servo servoRL;
Servo servoUD;

BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
  moveControl(x, y);
}

BLYNK_WRITE(V2)
{
  ServoDown();
}
BLYNK_WRITE(V8)
{
  ServoUp();
}
BLYNK_WRITE(V4)
{
  ServoLeft();
}
BLYNK_WRITE(V6)
{
  ServoRight();
}

void moveControl(int x, int y)
{
  //Move Forward
  if (y >= maxRange && x >= minRange && x <= maxRange)
  {
    Serial.print("forward");
    forward();
  }

  //Move Forward Right
  else if (x >= maxRange && y >= maxRange)
  {
    Serial.print("right");
    forwardRight();
  }

  //Move Forward Left
  else if (x <= minRange && y >= maxRange)
  {
    Serial.print("left");
    forwardLeft();
  }

  //No Move
  else if (y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
    Serial.print("stop");
    Stop();
  }

  //Move Backward
  else if (y <= minRange && x >= minRange && x <= maxRange)
  {
    Serial.print("backward");
    backward();
  }

  //Move Backward Right
  else if (y <= minRange && x <= minRange)
  {
    Serial.print("right");
    backwardRight();
  }

  //Move Backward Left
  else if (y <= minRange && x >= maxRange)
  {
    Serial.print("left");
    backwardLeft();
  }
}

void setup()
{
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(RSpeed, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(LSpeed, OUTPUT);

  servoRL.attach(servoRLpin);
  servoUD.attach(servoUDpin);

  servoRL.write(60);
  servoUD.write(60);

  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
}

void forward()
{
  digitalWrite(R1, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L2, LOW);
  analogWrite(RSpeed, maxSpeed);
  analogWrite(LSpeed, maxSpeed);
}

void backward()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, HIGH);
  analogWrite(RSpeed, maxSpeed);
  analogWrite(LSpeed, maxSpeed);
}

void left()
{
  digitalWrite(R1, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L2, HIGH);
  analogWrite(RSpeed, minSpeed);
  analogWrite(LSpeed, minSpeed);
}

void right()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, LOW);
  analogWrite(RSpeed, minSpeed);
  analogWrite(LSpeed, minSpeed);
}

void Stop()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L2, LOW);
  analogWrite(RSpeed, noSpeed);
  analogWrite(LSpeed, noSpeed);
}

void forwardLeft()
{
  digitalWrite(R1, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L2, LOW);
  analogWrite(RSpeed, maxSpeed);
  analogWrite(LSpeed, noSpeed);
}

void forwardRight()
{
  digitalWrite(R1, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L2, LOW);
  analogWrite(RSpeed, noSpeed);
  analogWrite(LSpeed, maxSpeed);
}

void backwardLeft()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, HIGH);
  analogWrite(RSpeed, noSpeed);
  analogWrite(LSpeed, maxSpeed);
}

void backwardRight()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, HIGH);
  analogWrite(RSpeed, maxSpeed);
  analogWrite(LSpeed, noSpeed);
}

void ServoDown()
{
  posUD--;
  if (posUD < 30) {
    posUD = 30;
  }
  servoUD.write(posUD);
}

void ServoUp()
{
  posUD++;
  if (posUD > 80) {
    posUD = 80;
  }
  servoUD.write(posUD);
}

void ServoLeft()
{
  posRL++;
  if (posRL > 120) {
    posRL = 120;
  }
  servoRL.write(posRL);
}

void ServoRight()
{
  posRL--;
  if (posRL < 0) {
    posRL = 0;
  }
  servoRL.write(posRL);
}
