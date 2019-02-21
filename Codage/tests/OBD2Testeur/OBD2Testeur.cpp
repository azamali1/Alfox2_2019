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
  //liaison = new LiaisonSimulateur(PINALIM, PINEN);
  bluetooth = new Bluetooth(PINALIM, PINEN);
  //bluetooth->connexion("2017,11,7030A"); // OBD2 bleu
  Serial.println("Test de la classe OBD2");
  bluetooth->connexion("780C,B8,46F54");
  delay(2000);
  if (bluetooth->isActif())
  Serial.println();
  obd2 = new OBD2(bluetooth);
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

	Serial.println(obd2->lireVitesse());
	delay(2000);
	Serial.println(obd2->lireConsomation());
	delay(2000);
	Serial.println(obd2->lireRegimeMoteur());
	delay(2000);



}
void SERCOM3_Handler()
	{
	  bluetooth->getLiaisonBT()->IrqHandler();
	}

