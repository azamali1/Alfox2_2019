#include "../../src/LiaisonSimulateur.h"
#include "../../src/Bluetooth.h"
#include "../../src/OBD2.h"




Bluetooth* bluetooth;
OBD2* obd2;

char c = ' ';
boolean NL = true;

unsigned long periode;
unsigned long initial;

void setup() {
	Serial.begin(9600);
	delay(2500);
	bluetooth = Bluetooth::getInstance(PINALIM, PINEN);
	Serial.println("Test de la classe OBD2");
	bluetooth->connexion("B22B,1C,70EA6"); // OBD2 noir KONNWEI

	delay(2000);
	if (bluetooth->isActif()) {
		Serial.println();
		obd2 = OBD2::getInstance(bluetooth);
		Serial.println("OBD2 OK");
	}
	delay(2000);



}

void loop() {




		if (obd2->isConnected()) {
			Serial.println("Acquisitions des données OBD2");
			delay(500);
			Serial.print("Vitesse : ");
			Serial.print(obd2->lireVitesse());
			Serial.println(" Km/h");
			Serial.print("Regime moteur : ");
			Serial.print(obd2->lireRegimeMoteur());
			Serial.println(" tr/min");
			delay(500);
			Serial.print("Débit d'air : ");
			Serial.print(obd2->lireDair());
			Serial.println(" g/s");
			delay(500);
			Serial.print("Sonde : ");
			Serial.print(obd2->lireSonde());
			Serial.println("V");
			delay(1000);
			Serial.print("Consommation : ");
			Serial.print(obd2->lireConsomation());
			Serial.println(" L/100");
			delay(500);
			Serial.print("Tension batterie : ");
			Serial.print(obd2->lireBatterie());
			Serial.println(
					"-----------------------------------------------------");
			delay(2000);
		}


}

void SERCOM3_Handler() {
	bluetooth->getLiaisonBT()->IrqHandler();
}

