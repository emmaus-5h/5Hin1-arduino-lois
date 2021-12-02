  /*****************************************
   Game Startcode
   met toestansdiagrammen
   Emmauscollege
   v20201114GEE
 *****************************************/

/*****************************************
   libraries die je gebruikt 

   LCD met 2 regels van 16 karakters 
   (de RGB backlit kan niet van kleur worden veranderd)
   https://www.arduino.cc/reference/en/libraries/grove-lcd-rgb-backlight/

 *****************************************/
#include <Wire.h>
#include "rgb_lcd.h"

/*****************************************
   variabelen die je gebruikt maken
 *****************************************/
// gebruikte pinnen
const int pinLedA   = 13; // pin van LED voor speler 1
const int pinKnopRood  = 10; // pin van knop voor speler 1
const int pinKnopGroen  = 9; // pin van knop voor speler 2

// variabelen om waarden van sensoren en actuatoren te onthouden
int knopRood = 0;
int knopGroen = 0;

// variabelen voor de toestanden
const int TELAF = 1; // tel af tot spel start
const int SPEEL = 2; // speel het spel
const int WIN   = 3; // laat zien wie de winnaar is
int toestand = TELAF;
unsigned long toestandStartTijd = 0;

/*****************************************
   setup() en loop()
 *****************************************/

void setup() {
  // enable console en stuur opstartbericht
  Serial.begin(9600);
  Serial.println("Game start");

  // zet pinmode voor leds
  pinMode(pinLedA, OUTPUT);

  // zet pinmode voor knoppen
  pinMode(pinKnopRood, INPUT);
  pinMode(pinKnopGroen, INPUT);
}

void loop() {
  // lees sensorwaarden
  knopRood = digitalRead(pinKnopRood);
  knopGroen = digitalRead(pinKnopGroen);

  
  if (knopRood == HIGH || knopGroen == HIGH) {
    digitalWrite(pinLedA, HIGH);
  } else {
    digitalWrite(pinLedA, LOW);
  }

  // kleine vertraging, 100 keer per seconde loopen is genoeg
  delay(10);
}
