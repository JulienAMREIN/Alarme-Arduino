#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // 0x27 pour LCD 16*2 caractères

int etatAlarme = 0; // variable qui enregistre l'état de l'alarme
int etatBouton = 0; // variable qui enregistre l'état du bouton
const int relais = 7; // le relais est connecté à la broche X de la carte Adruino
const int bouton = 4; // le bouton est connecté à la broche 4 de la carte Adruino
const int delaisArmement = 10000; // Délais avant armement de l'alarme en milisecondes

void setup()
{
	pinMode(bouton, INPUT_PULLUP); // le bouton est une entrée 
	pinMode(relais, OUTPUT); // le relais est une entrée
	etatBouton = HIGH; // initialise l'état du bouton comme "relaché"  
  
	lcd.init(); // initialisation du lcd 
	lcd.backlight();
	lcd.setCursor(1,0);
	lcd.print("Alarme ARDUINO");
	lcd.setCursor(6,1);
	lcd.print("v0.1");
}

void loop()
{
	etatBouton = digitalRead(bouton); // Lecture de l'état du bouton

	if((etatBouton == LOW) && (etatAlarme == 0)) 
    	{
		lcd.backlight();
		etatAlarme++;
		//delay(1100); // Délais pour avoir le temps de voir l'affichage précédent si lcd.nobacklight();
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Arret du systeme");
		digitalWrite(relais, LOW);
		delay(2000);
		lcd.setCursor(3,1);
		lcd.print("*** OK ***");
		delay(3000);
		lcd.clear();
		lcd.setCursor(1,0);
		lcd.print("Alarme ARDUINO");;
		lcd.setCursor(6,1);
		lcd.print("v0.1");
		//delay(10000);
		//lcd.noBacklight();
	}

	else 
	{
		if((etatBouton == LOW) && (etatAlarme == 1))
		{
		lcd.backlight(); 
		etatAlarme--;
		//delay(1100); // Délais pour avoir le temps de voir l'affichage précédent si lcd.nobacklight();

		// ---------------------------------Début de la temporisation d'allumage--------------------------------------------------------

		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("   Armement du");
		lcd.setCursor(0,1);
		lcd.print("     systeme");
		delay(2000);

		for(int i = 0; i < 16; i++)
		{
		lcd.setCursor(i,0);
		lcd.print("*");
		delay(delaisArmement / 60);
		}

		for(int i = 0; i < 16; i++)
		{
		lcd.setCursor(i,1);
		lcd.print("*");
		delay(delaisArmement / 60);
		}

		for(int i = 0; i < 16; i++)
		{
		lcd.setCursor(i,0);
		lcd.print(" ");
		delay(delaisArmement / 60);
		}

		for(int i = 0; i < 16; i++)
		{
		lcd.setCursor(i,1);
		lcd.print(" ");
		delay(delaisArmement / 60);
		}

		// ---------------------------------Fin de la temporisation d'allumage--------------------------------------------------------

		digitalWrite(relais, HIGH);
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("   Systeme en");;
		lcd.setCursor(0,1);
		lcd.print("     marche");
		delay(2500);
		lcd.clear();
		lcd.setCursor(1,0);
		lcd.print("Alarme ARDUINO");;
		lcd.setCursor(0,1);
		lcd.print("***   v0.1   ***");
		//delay(5000);
		//lcd.noBacklight();    
		}
		else 
		{
	       
		}
    
	}


}
