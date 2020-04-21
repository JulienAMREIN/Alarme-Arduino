#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // 0x27 pour LCD 16*2 caractères

int etatAlarme = 0; // variable qui enregistre l'état de l'alarme
int etatBouton = 0; // variable qui enregistre l'état du bouton
const int relais = 13; // le relais est connecté à la broche X de la carte Adruino
const int bouton = 4; // le bouton est connecté à la broche 4 de la carte Adruino

void setup()
{
  pinMode(bouton, INPUT_PULLUP); // le bouton est une entrée 
  pinMode(relais, OUTPUT); // le relais est une entrée
  etatBouton = HIGH; // initialise l'état du bouton comme "relaché"  
  
  lcd.init(); // initialisation du lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" Alarme ARDUINO");
  lcd.setCursor(0,1);
  lcd.print("      v0.1");
  
}

void loop()
{
   etatBouton = digitalRead(bouton); // Lecture de l'état du bouton

   if((etatBouton == LOW) && (etatAlarme == 0)) 
    {
      lcd.backlight();
       etatAlarme++;
     delay(1500);
     lcd.setCursor(0,1);
  lcd.print("OFF");
  digitalWrite(relais, LOW);
     delay(10000);
     lcd.noBacklight();
          
    }
    else 
    {
if((etatBouton == LOW) && (etatAlarme == 1))
    {
     lcd.backlight(); 
     etatAlarme--;
     delay(1500);
     lcd.setCursor(0,1);
  lcd.print("ON ");
  delay(10000);
   digitalWrite(relais, HIGH);
   lcd.noBacklight();
     
          
    }
    else 
    {
       
    }
    
    }


}
