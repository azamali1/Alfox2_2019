#include "../../src/LiaisonSimulateur.h"
#include "../../src/Bluetooth.h"
#include "../../src/OBD2.h"

#define PERIODE_ECH 5000 //en millisecondes

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
	//bluetooth->connexion("780C,B8,46F54"); // pc prof HP
	//bluetooth->connexion("C0CB,38,D768D5"); // pc prof SONY
	delay(2000);
	Serial.println(bluetooth->isActif());
	obd2 = OBD2::getInstance(bluetooth);
	delay(2000);
	Serial.print("La connexion à l'OBD2 est-elle opérationnelle ? ");
	Serial.println(obd2->testerConnexion());

}

void loop() {

	periode = millis() - initial;

	if (periode >= PERIODE_ECH) {

		if (obd2->isConnected()) {
			Serial.println("Acquisitions des données OBD2");
			delay(500);

			int heureDebut = millis();
			Serial.print("La connexion à l'OBD2 est-elle opérationnelle ? ");
			Serial.println(obd2->testerConnexion());
			int heureFin = millis();
			int duree = heureFin - heureDebut;
			Serial.print("Durée d'exécution du test de connexion : ");
			Serial.println(duree);

			Serial.print("Vitesse : ");
			Serial.print(obd2->lireVitesse());
			Serial.println(" Km/h");
			delay(500);
			Serial.print("Regime moteur : ");
			Serial.print(obd2->lireRegimeMoteur());
			Serial.println(" tr/min");
			delay(500);
			Serial.print("Pression : ");
			Serial.print(obd2->lirePression());
			Serial.println(" Kpa");
			delay(500);
			Serial.print("Température : ");
			Serial.print(obd2->lireTemprerature());
			Serial.println("°C");
			delay(500);
			Serial.print("Débit d'air : ");
			 Serial.print(obd2->lireDair());
			 Serial.println(" g/s");
			 delay(500);
			Serial.print("Sonde : ");
			Serial.print(obd2->lireSonde());
			Serial.println("V");
			delay(500);
			Serial.print("Sonde2 : ");
			Serial.print(obd2->lireSonde2());
			Serial.println("V");
			delay(100);
			Serial.print("Consommation : ");
			Serial.print(obd2->lireConsomation());
			Serial.println(" L/100");
			delay(500);
			Serial.print("Tension batterie : ");
			Serial.print(obd2->lireBatterie());
			Serial.println(" V");
			delay(500);
			Serial.println(
					"-----------------------------------------------------");
			initial = millis();
		}
	}

}

void SERCOM3_Handler() {
	bluetooth->getLiaisonBT()->IrqHandler();
}

