/*************************************************************
  CRAZY INDIANA NodeMcu Wifi Car with Blynk
  Website www.crazyindiana.in
  Youtube www.youtube.com/c/CrazyIndiana
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

 **************************************************************/


#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


const int a1 = 26;
const int a2 = 25;
const int b1 = 33;
const int b2 = 32;



// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "qbOwS1e6ZyWH49HYNchxHtK1CkfiiXJD";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "DRAGON";
char pass[] = "P48palaestina";

BLYNK_WRITE(V1)
{
  // hint: https://www.youtube.com/watch?v=SMOKxWsmi-g&t=386s
  int x = param[0].asInt();
  int y = param[1].asInt();

  moveControl(x, y);
  //  // Do something with x and y
  //  Serial.print("X = ");
  //  Serial.print(x);
  //  Serial.print("; Y = ");
  //  Serial.println(y);
  //
  //  //  int speed =350;
  //  //  analogWrite(EN1, speed);//sets the motors speed
  //  //  analogWrite(EN2, speed);//sets the motors speed
  //  // Joystick Movement
  //  if (y > 350)
  //  {
  //    Serial.print("forward");
  //    forward();
  //  }
  //
  //  if (y < 170)
  //  {
  //    Serial.print("backward");
  //    backward();
  //  }
  //
  //  if (x < 132)
  //  {
  //    Serial.print("left");
  //    left();
  //  }
  //
  //  if (x > 380)
  //  {
  //    Serial.print("right");
  //    right();
  //  }
  //
  //  if ((y == 256) && (x == 256))
  //  {
  //    Serial.print("stop");
  //    stop();
  //  }

}
int minRange = 312;
int maxRange = 712;

int minspeed = 450;
int maxspeed = 1020;
int nospeed = 0;


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


//------------------------
BLYNK_WRITE(V10)
{
  stop();
}
//------------------------
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
