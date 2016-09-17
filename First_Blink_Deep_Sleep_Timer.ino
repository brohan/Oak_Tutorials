#include <ESP8266WiFi.h>
#include "stdlib.h"

#define SLEEP_PIN 5
int sleepTimeS = 10;

void setup()
{                
  pinMode(1, OUTPUT); //LED on Oak
  pinMode(5, INPUT);
}

void loop()
{
  digitalWrite(1, HIGH);
  delay(1000);
  digitalWrite(1, LOW);
  delay(1000);

  // Check to see if sleep mode selected
  
  if (digitalRead(SLEEP_PIN) == LOW) {
     Particle.publish("Oak Setup", "Entering Deep Sleep", 60, PRIVATE);
     ESP.deepSleep(sleepTimeS*1000000, WAKE_RF_DEFAULT); // Sleep
  }
  else
  {
     Particle.publish("Oak Setup","Entering Non Sleep Mode",60,PRIVATE);
  }
}

