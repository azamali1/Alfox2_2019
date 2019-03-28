#include "../../src/LiaisonSimulateur.h"
#include "../../src/Bluetooth.h"
#include "../../src/OBD2.h"

//LiaisonSimulateur* liaison;
Bluetooth* bluetooth;
OBD2* obd2;
char c = ' ';
boolean NL = true;

void setup() {
  Serial.begin(9600);
  delay(2500);
  //liaison = LiaisonSimulateur::getInstance(PINALIM, PINEN);
  bluetooth = Bluetooth::getInstance(PINALIM, PINEN);
  //bluetooth->connexion("2017,11,7030A"); // OBD2 bleu
  Serial.println("Test de la classe OBD2");
  bluetooth->connexion("780C,B8,46F54");
  delay(2000);
  if (bluetooth->isActif())
  Serial.println();
  obd2 = OBD2::getInstance(bluetooth);
  Serial.println("OBD2 OK");


}


void loop() {
	if (bluetooth->getLiaisonBT()->available())
	    {
	      c = bluetooth->getLiaisonBT()->read();
	      Serial.write(c);
	    }

	    // Read from the Serial Monitor and send to the Bluetooth module
	    if (Serial.available())
	    {
	      c = Serial.read();
	      bluetooth->getLiaisonBT()->write(c);
	      if (NL) { Serial.print("\r\n>");  NL = false; }
	      Serial.write(c);
	      if (c==10)
	      {
	        NL = true;
	      }
	  }

	Serial.print(obd2->lireVitesse());
	Serial.println(" Km/h");
	delay(2000);
	//ici on lit la Pression en kpa
	Serial.print(obd2->lirePression());
	Serial.println(" kpa");
	delay(2000);
	//ici on lit la Température d'admission d'air en °C
	Serial.print(obd2->lireTemprerature());
	Serial.println(" °C");
	delay(2000);
	//ici on lit le Ratio carburant/air
	Serial.println(obd2->lireRatio());
	delay(2000);
	//ici on lit grâce a un calcul la consommation du véhicule
	//Serial.print(obd2->calculConsommation());
	Serial.print(obd2->lireConsomation());
	Serial.println(" L/100");
	delay(2000);
	//ici on lit le Regime moteur en tr/min
	Serial.print(obd2->lireRegimeMoteur());
	Serial.println(" tr/min");
	delay(2000);

}
void SERCOM3_Handler()
	{
	  bluetooth->getLiaisonBT()->IrqHandler();
	}

