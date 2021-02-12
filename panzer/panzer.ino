#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define a1 26
#define a2 25
#define aSpeed 27
#define b1 33
#define b2 32
#define bSpeed 35

char auth[] = "qbOwS1e6ZyWH49HYNchxHtK1CkfiiXJD";
char ssid[] = "DRAGON";
char pass[] = "P48palaestina";

int minRange = 312;
int maxRange = 712;

int minspeed = 450;
int maxspeed = 1020;
int nospeed = 0;


BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
  moveControl(x, y);
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
    right();
  }

  //Move Forward Left
  else if (x <= minRange && y >= maxRange)
  {
    Serial.print("left");
    left();
  }

  //No Move
  else if (y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
    Serial.print("stop");
    stop();
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
    right();
  }

  //Move Backward Left
  else if (y <= minRange && x >= maxRange)
  {
    Serial.print("left");
    left();
  }
}

void setup()
{
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);

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
  digitalWrite(a1, HIGH);
  digitalWrite(b1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
}

void backward()
{
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b2, HIGH);
}

void left()
{
  digitalWrite(a1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b2, HIGH);
}

void right()
{
  digitalWrite(a1, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(a2, HIGH);
  digitalWrite(b2, LOW);
}

void stop()
{
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
}

void forwardLeft()
{
  digitalWrite(a1, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
}

void forwardRight()
{
  digitalWrite(a1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b2, LOW);
}

void backwardLeft()
{
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b2, LOW);
}

void backwardRight()
{
  digitalWrite(a1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b2, HIGH);
}

void rotateRight()
{
  digitalWrite(a1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b2, HIGH);
}

void rotateLeft()
{
  digitalWrite(a1, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(a2, HIGH);
  digitalWrite(b2, LOW);
}
