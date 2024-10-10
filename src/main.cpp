#include <Arduino.h>

#define LED_PIN 12
#define KRATCE '.'
#define DLOUZE '-'

#define TRV_KRATCE 50
#define TRV_DLOUZE 100
#define PAUZA_DELSI 400
#define PAUZA 200
/* Pole, které obsahuje písmena morseovy abecedy (bez diakritiky) */
const char *morseovka[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."};

bool text_vypsan = false;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}
/* Funkce, která blikne LED diodou */
void led_blikni(int pin, int trvani)
{
  digitalWrite(pin, HIGH);
  delay(trvani);
  digitalWrite(pin, LOW);
}
/* Funkce, která zjišťuje, jestli je znak krátký nebo dlouhý */
void morseovka_blikni(const char *vstupni_text)
{
  while (*vstupni_text)
  {
    if (*vstupni_text == KRATCE)
    {
      led_blikni(LED_PIN, TRV_KRATCE);
    }
    else if (*vstupni_text == DLOUZE)
    {
      led_blikni(LED_PIN, TRV_DLOUZE);
    }
    vstupni_text++;
    delay(PAUZA);
  }
}

void loop()
{
  /* Vypíše výzvu pro zadání, pokud nebyla ještě zobrazena */
  if (!text_vypsan)
  {
    Serial.print("Zadejte text (a-z): ");
    text_vypsan = true;
  }

  if (Serial.available())
  {
    /* Načte jednotlivé znaky */
    String vstupni_text = Serial.readString();
    /* Zpracovává načtené znaky */
    for (int i = 0; i < (int)vstupni_text.length(); i++)
    {
      char znak = toupper(vstupni_text[i]);

      if (znak >= 'A' && znak <= 'Z')
      {
        int index = znak - 'A';
        morseovka_blikni(morseovka[index]);
      }
      delay(PAUZA_DELSI);
    }
    /* Enter pro odřádkování */
    text_vypsan = false;
    Serial.println();
  }
}