/* Please confgure the Blynk auth key (line 11) and wifi credentials (line 16/17) */

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";


//pin setup

const int mainReadPin = 10; //Also known as SDD3
const int edhReadPin = 12; //Also known as D6
const int genReadPin = 13; //Also known as D7

//declare the global variables

String edhAndGenNotified = "2";
int V10globalButtonValue = 0;
int V11globalButtonValue = 0;
int V12globalButtonValue = 0;


//done declaring the global variables

//Virtual pins definitions

WidgetLED led1(V1);

BLYNK_WRITE(V10) //Main notify button
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
//  Serial.println(globalButtonValue);
  V10buttonPressedFunction(pinValue);
}

BLYNK_WRITE(V11) //Edh notify button
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
//  Serial.println(globalButtonValue);
  V11buttonPressedFunction(pinValue);
}

BLYNK_WRITE(V12) //Generator notify button
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
//  Serial.println(globalButtonValue);
  V12buttonPressedFunction(pinValue);
}



//Done defining the virtual Pins

BlynkTimer timer;


//functions for the notifcator virtual pins
void V10buttonPressedFunction(int rec)
{
//  Serial.println(rec);
  V10globalButtonValue = rec;
}

void V11buttonPressedFunction(int rec)
{
//  Serial.println(rec);
  V11globalButtonValue = rec;
}

void V12buttonPressedFunction(int rec)
{
//  Serial.println(rec);
  V12globalButtonValue = rec;
}

//done with these functions


// V1 LED Widget is blinking
void blinkLedWidget()
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off" + V10globalButtonValue);
  } else {
    led1.on();
    Serial.println("LED on V1: on");
  }

  if (digitalRead(mainReadPin) == HIGH) {
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V2, 0);
        Serial.println("D5 OFF");
  } else {
    Blynk.virtualWrite(V5, 1);
    Blynk.virtualWrite(V2, 255);
        Serial.println("D5 ON");

  }

  if (digitalRead(edhReadPin) == HIGH) {
    Blynk.virtualWrite(V6, 0);
        Serial.println("D6 OFF");
  } else {
    Blynk.virtualWrite(V6, 1);
        Serial.println("D6 ON");

  }

  if (digitalRead(genReadPin) == HIGH) {
    Blynk.virtualWrite(V7, 0);
        Serial.println("D7 OFF");
  } else {
    Blynk.virtualWrite(V7, 1);
        Serial.println("D7 ON");

  }

//NOTIFICATOR CODES

//STANDARD EDH AND GENERATOR NOTIFICATOR CODE

        if (digitalRead(edhReadPin) == LOW && digitalRead(genReadPin) == LOW) {
          Blynk.virtualWrite(V3, 1);
          Serial.println("both on at the same time " + edhAndGenNotified);
          // Notify immediately on startup
            if (edhAndGenNotified == "0") {
                Blynk.notify("EDH just came on, and the generator is running!");
                 Serial.println("Notification sent out");
                 edhAndGenNotified = "1";
                }

          } else {
            Blynk.virtualWrite(V3, 0);
                // Serial.println("Nothing to worry about");
                 edhAndGenNotified = "0" ;

          }

//MANUALLY REQUESTED NOTIFICATION WITH BUTTON

          if (V10globalButtonValue == 1 && digitalRead(mainReadPin) == LOW) {
                Serial.println("V10globalButtonValue is 1");
                  Blynk.virtualWrite(V10, LOW);
                  V10buttonPressedFunction(0);
                  Blynk.notify("Per your request: The mainline just turned on!");
                   Serial.println("Notification sent out");

          } else { }

          if (V11globalButtonValue == 1 && digitalRead(edhReadPin) == LOW) {
                Serial.println("V11globalButtonValue is 1");
                  Blynk.virtualWrite(V11, LOW);
                  V11buttonPressedFunction(0);
                  Blynk.notify("Per your request: EDH just turned on!");
                   Serial.println("Notification sent out");

          } else { }

          if (V12globalButtonValue == 1 && digitalRead(genReadPin) == LOW) {
                Serial.println("V12globalButtonValue is 1");
                  Blynk.virtualWrite(V12, LOW);
                  V12buttonPressedFunction(0);
                  Blynk.notify("Per your request: The generator just turned on!");
                   Serial.println("Notification sent out");

          } else { }

//DONE WITH THE MANUALLY DEFINED NOTIFICATION


}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(mainReadPin, INPUT_PULLUP); //D5
  pinMode(edhReadPin, INPUT_PULLUP); //D6
  pinMode(genReadPin, INPUT_PULLUP); //D7
  WiFi.hostname("blinkNodemcuEdh");

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  Blynk.syncVirtual(V10, V11, V12);

  timer.setInterval(1000L, blinkLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();


}
