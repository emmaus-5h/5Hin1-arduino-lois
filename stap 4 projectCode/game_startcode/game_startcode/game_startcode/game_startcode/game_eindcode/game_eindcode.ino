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

rgb_lcd lcd;

/*****************************************
   variabelen die je gebruikt maken
 *****************************************/
// gebruikte pinnen
const int pinLedA   = 13; // pin van LED voor speler 1
const int pinKnopRood  = 10; // pin van knop voor start spel
const int pinKnopGroen  = 9; // pin van knop voor speler 2

// variabelen om waarden van sensoren en actuatoren te onthouden
int knopRood = 0;
int knopGroen = 0;

// variabelen voor de toestanden
const int STARTSIGNAAL = 1; // tel af tot spel start
const int WACHT_OP_KNOP_IN = 2; // speel het spel
const int GEEF_PUNT   = 3; // laat zien wie de winnaar is
const int TOON_SCORE = 4; // laat het eind totaal punten zien
int toestand = STARTSIGNAAL;
unsigned long toestandStartTijd = 0;
unsigned long speelStartTijd = 0;

// overige variabelen
int score = 0;

/*****************************************
   functies die je gebruikt maken
 *****************************************/
// code die steeds wordt uitgevoerd in toestand TELAF
void telafLoop() {
  digitalWrite(pinLedA, HIGH);
  // tel af
}

// code die steeds wordt uitgevoerd in toestand SPEEL
void speelLoop() {
  digitalWrite(pinLedA, LOW);
  // speel spel
}

// code die steeds wordt uitgevoerd in toestand SPEEL
void winLoop() {
  // toon wie gewonnen heeft
}
void eindLoop() {

}


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

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //lcd.setRGB(colorR, colorG, colorB);

  // Print a message to the LCD.
  lcd.print("hello, world!");
  delay(1000); // wacht zodat je ziet dat het display werkt
}

void loop() {
  // lees sensorwaarden
  knopRood = digitalRead(pinKnopRood); // ingedrukt is HIGH
  knopGroen = digitalRead(pinKnopGroen);

  // bepaal toestand
  if (toestand == STARTSIGNAAL) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Press red");
    telafLoop();
    if (knopRood == HIGH) { // 2 seconden voorbij
      toestandStartTijd = millis();
      speelStartTijd = millis();
      toestand = WACHT_OP_KNOP_IN;
      Serial.println("Nieuwe toestand: WACHT_OP_KNOP_IN");

    }
  }
  if (toestand == WACHT_OP_KNOP_IN) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Press green");
    lcd.setCursor(0, 0);
    lcd.print(score);
    speelLoop();
    if (knopGroen == HIGH) { // 1 minuut voorbij
      score = score + 1;
      toestandStartTijd = millis();
      toestand = GEEF_PUNT;
      Serial.println("Nieuwe toestand: GEEF_PUNT");
    }
    if (millis() - speelStartTijd > 10000) {
      toestandStartTijd = millis();
      toestand = TOON_SCORE;
      Serial.println("Nieuwe toestand: TOON_SCORE");
    }

  }
  if (toestand == GEEF_PUNT) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("+1");
    winLoop();
    if (knopGroen == LOW) {       // groene knop ingedrukt
      toestandStartTijd = millis();
      toestand = WACHT_OP_KNOP_IN;
      Serial.println("Nieuwe toestand: TOON_SCORE");
    }
    if (millis() - speelStartTijd > 10000) {
      toestandStartTijd = millis();
      toestand = TOON_SCORE;
      Serial.println("Nieuwe toestand: TOON_SCORE");
    }

  }
  if (toestand == TOON_SCORE) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("end of game");
    eindLoop();

    if (knopRood == HIGH) {
      toestandStartTijd = millis();
      toestand = STARTSIGNAAL;
      Serial.println("Nieuwe toestand: STARTSIGNAAL");
    }
  }


// kleine vertraging, 100 keer per seconde loopen is genoeg
delay(10);
}
