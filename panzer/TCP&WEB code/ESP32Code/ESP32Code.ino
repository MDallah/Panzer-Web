#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>
//#include <analogWrite.h>


#define R1 27
#define R2 26

#define L1 33
#define L2 32

#define Leds 17
#define Fire 16

//static const int RSpeed = 22;
//static const int LSpeed = 5;

const int ledPin1 = 22;  // 16 corresponds to GPIO1
const int ledPin2 = 5;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 5000;
const int ledChannel = 2;
const int ledChannel1 = 3;
const int resolution = 8;


static const int servoRLpin = 19;
static const int servoUDpin = 18;

int minSpeed = 150;
int maxSpeed = 254; //maximal. 255
int noSpeed = 0;

int posRL = 60;
int posUD = 60;
Servo servoRL;
Servo servoUD;

const char* ssid = "DRAGON";
const char* password = "P48palaestina";

// Set your Static IP address
IPAddress local_IP(192, 168, 178, 13);
// Set your Gateway IP address
IPAddress gateway(192, 168, 178, 1);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional



AsyncWebServer server(80);


void setup() {
  Serial.begin(115200);

  pinMode(Leds, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  //  pinMode(RSpeed, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  //  pinMode(LSpeed, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(ledChannel1, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin1, ledChannel);
  ledcAttachPin(ledPin2, ledChannel1);

  servoRL.attach(servoRLpin);
  servoUD.attach(servoUDpin);

  servoRL.write(60);
  servoUD.write(60);

  WiFi.begin(ssid, password);

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {

    int paramsNr = request->params();
    //Serial.println(paramsNr);

    for (int i = 0; i < paramsNr; i++) {

      AsyncWebParameter* p = request->getParam(i);
      Serial.print("Param name: ");
      Serial.println(p->name());
      Serial.print("Param value: ");
      const String value = p->value();
      Serial.println(p->value());
      if ( value == "8" ) {
        forward();
        Serial.println("8");
      }
      if ( value == "2" ) {
        backward();
        Serial.println("2");
      }
      //----------------------------------------------
      if ( value == "9" ) {
        forwardRight();
        Serial.println("9");
      }
      if ( value == "7" ) {
        forwardLeft();
        Serial.println("7");
      }
      //----------------------------------------------
      if ( value == "3" ) {
        backwardRight();
        Serial.println("3");
      }
      if ( value == "1" ) {
        backwardLeft();
        Serial.println("1");
      }
      //----------------------------------------------
      if ( value == "S8" ) {
        ServoUp();
        Serial.println("S8");
      }
      if ( value == "S2" ) {
        ServoDown();
        Serial.println("S2");
      }
      //----------------------------------------------
      if ( value == "S4" ) {
        ServoLeft();
        Serial.println("S4");
      }
      if ( value == "S6" ) {
        ServoRight();
        Serial.println("S6");
      }
      //----------------------------------------------
      if ( value == "5" ) {
        Stop();

        Serial.println("5");
      }
      if ( value == "S5" ) {
        // ServoStop();
        // Serial.println("S5");
      }
      //----------------------------------------------
      if ( value == "L" ) {
        if (digitalRead(Leds) == LOW)
        {
          digitalWrite(Leds, HIGH);
        }
        else
        {
          digitalWrite(Leds, LOW);
        }
      }
      Serial.println("------");
    }

    request->send(200, "text/plain", "message received");
  });

  server.begin();
}

void loop() {}


void forward()
{
  digitalWrite(R1, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L2, LOW);
  //  analogWrite(RSpeed, maxSpeed);
  //  analogWrite(LSpeed, maxSpeed);
  ledcWrite(ledChannel, maxSpeed);
  ledcWrite(ledChannel1, maxSpeed);
}

void backward()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, HIGH);
  //  analogWrite(RSpeed, maxSpeed);
  //  analogWrite(LSpeed, maxSpeed);
  ledcWrite(ledChannel, maxSpeed);
  ledcWrite(ledChannel1, maxSpeed);
}

void left()
{
  digitalWrite(R1, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L2, HIGH);
  //  analogWrite(RSpeed, minSpeed);
  //  analogWrite(LSpeed, minSpeed);
  ledcWrite(ledChannel, minSpeed);
  ledcWrite(ledChannel1, minSpeed);
}

void right()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, LOW);
  //  analogWrite(RSpeed, minSpeed);
  //  analogWrite(LSpeed, minSpeed);
  ledcWrite(ledChannel, minSpeed);
  ledcWrite(ledChannel1, minSpeed);
}

void Stop()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L2, LOW);
  //  analogWrite(RSpeed, noSpeed);
  //  analogWrite(LSpeed, noSpeed);
}

void forwardLeft()
{
  digitalWrite(R1, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L2, LOW);
  //  analogWrite(RSpeed, maxSpeed);
  //  analogWrite(LSpeed, noSpeed);
  ledcWrite(ledChannel, maxSpeed);
  ledcWrite(ledChannel1, noSpeed);
}

void forwardRight()
{
  digitalWrite(R1, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L2, LOW);
  //  analogWrite(RSpeed, noSpeed);
  //  analogWrite(LSpeed, maxSpeed);
  ledcWrite(ledChannel, noSpeed);
  ledcWrite(ledChannel1, maxSpeed);
}

void backwardLeft()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, HIGH);
  //  analogWrite(RSpeed, noSpeed);
  //  analogWrite(LSpeed, maxSpeed);
  ledcWrite(ledChannel, noSpeed);
  ledcWrite(ledChannel1, maxSpeed);
}

void backwardRight()
{
  digitalWrite(R1, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, HIGH);
  //  analogWrite(RSpeed, maxSpeed);
  //  analogWrite(LSpeed, noSpeed);
  ledcWrite(ledChannel, maxSpeed);
  ledcWrite(ledChannel1, noSpeed);
}

void ServoDown()
{
  posUD--;
  if (posUD < 30) {
    posUD = 30;
  }
  servoUD.write(posUD);
  Serial.print("posUD: ");
  Serial.println(posUD);
}

void ServoUp()
{
  posUD++;
  if (posUD > 80) {
    posUD = 80;
  }
  servoUD.write(posUD);
  Serial.print("posUD: ");
  Serial.println(posUD);
}

void ServoLeft()
{
  posRL++;
  if (posRL > 120) {
    posRL = 120;
  }
  servoRL.write(posRL);
  Serial.print("posRL: ");
  Serial.println(posRL);
}

void ServoRight()
{
  posRL--;
  if (posRL < 0) {
    posRL = 0;
  }
  servoRL.write(posRL);
  Serial.print("posRL: ");
  Serial.println(posRL);

}

void ServoStop()
{
  servoUD.write(posUD);
  servoRL.write(posRL);
}
