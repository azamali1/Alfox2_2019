#include "../../src/LiaisonSimulateur.h"
#include "../../src/Bluetooth.h"
#include "../../src/OBD2.h"

#define PERIODE_ECH 5000 //en millisecondes

//LiaisonSimulateur* liaison;
Bluetooth* bluetooth;
OBD2* obd2;

char c = ' ';
boolean NL = true;

unsigned long periode;
unsigned long initial;

void setup() {
	Serial.begin(9600);
	delay(2500);
	//liaison = new LiaisonSimulateur(PINALIM, PINEN);
	bluetooth = Bluetooth::getInstance(PINALIM, PINEN);
	//bluetooth->connexion("2017,11,7030A"); // OBD2 bleu
	Serial.println("Test de la classe OBD2");
	bluetooth->connexion("B22B,1C,70EA6");// OBD2 noir KONNWEI
	//bluetooth->connexion("E84E,84,CCF54A"); //Portable ZAMALI

	delay(2000);
	if (bluetooth->isActif()) {
		Serial.println();
		obd2 = OBD2::getInstance(bluetooth);
		Serial.println("OBD2 OK");
	}
	delay(2000);

	initial = millis();

}

void loop() {
	periode = millis() - initial;

	if (periode >= PERIODE_ECH) {

		Serial.println("Réalisation des acquisitions");
		if (obd2->isConnected()) {
			delay(500);
			Serial.print("Vitesse : ");
			Serial.print(obd2->lireVitesse());
			Serial.println(" Km/h");
			delay(500);
			/*//ici on lit la Pression en kpa
			Serial.print("Pression : ");
			Serial.print(obd2->lirePression());
			Serial.println(" kpa");
			delay(500);
			//ici on lit la Température d'admission d'air en °C
			Serial.print("Temprérature : ");
			Serial.print(obd2->lireTemprerature());
			Serial.println(" °C");
			delay(500);
			//ici on lit le Ratio carburant/air
			Serial.println(obd2->lireRatio());
			delay(500);*/
			//ici on lit le Regime moteur en tr/min
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
			delay(500);
			//ici on lit grâce a un calcul la consommation du véhicule
			Serial.print("Consommation : ");
			Serial.print(obd2->lireConsomation());
			Serial.println(" L/100");
			delay(500);
			//on lit la Tension de la batterie en V avec une commande AT
			Serial.print("Tension batterie : ");
			Serial.print(obd2->lireBatterie());
			Serial.println(" V");
			initial = millis();
		}

	}
}

void SERCOM3_Handler() {
	bluetooth->getLiaisonBT()->IrqHandler();
}

