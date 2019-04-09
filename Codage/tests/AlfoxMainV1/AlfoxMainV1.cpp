#include <Arduino.h>
#include "../../src/GPS.h"
#include "../../src/DonneesTR.h"
#include "../../src/Bluetooth.h"
#include "../../src/CarteSD.h"
#include "../../src/OBD2.h"
#include "../../src/Global.h"
#include "../../src/Message.h"
#include "../../src/HTR.h"

#define DUREE_LOOP 5000 //en millisecondes
#define T_MSG_STND 720000 //12 minutes en ms
#define T_MSG_GPS 3600000 //1h en ms

byte bMsg[12];

unsigned long dureeCumulee;
unsigned long heureDebut;
unsigned long tempoMessage;

HTR* htr;
Message* message;
Bluetooth* bluetooth;
OBD2* obd2;
GPS* gps;
DonneesTR* donneesTR;
CarteSD* sd;

void sendMessageStandard();
void sendMessageGPS();
void majDataTR();

void setup() {
	Serial.begin(9600);
	delay(10000);
	htr = HTR::getInstance();
	message = new Message();
	bluetooth = Bluetooth::getInstance(PINALIM, PINEN);
	//obd2 = OBD2::getInstance(bluetooth);
	gps = GPS::getInstance();
	gps->maj();
	delay(500);
	htr->setDatation(gps->getDatation());
	donneesTR = new DonneesTR();
	sd = CarteSD::getInstance();
	delay(500);

}

void loop() {
	Serial.println("Entrée dans la loop");
	heureDebut = millis();

	majDataTR();

	sd->ecrire(donneesTR);

	if (dureeCumulee >= T_MSG_STND) {

		sendMessageStandard();

	} else if (dureeCumulee >= T_MSG_GPS) {

		sendMessageGPS();

	}

	htr->majDatation(millis());

	//Durée constante de la loop

	delay(DUREE_LOOP - (millis() - heureDebut));
	dureeCumulee = DUREE_LOOP - (millis() - heureDebut);

	Serial.println("\n-----------------------------------------------------\n");

	//fin

}

void majDataTR() {
	Serial.println("entrée dans majDAtaTR");
	/*if (obd2->isConnected()== true ) {
	 Serial.println("Le bluetooth est actif");

	 donneesTR->setVitesse(obd2->lireVitesse());
	 delay(250);
	 donneesTR->setRegime(obd2->lireRegimeMoteur());
	 delay(250);
	 donneesTR->setConsommation(obd2->lireConsomation());
	 delay(250);
	 } else {
	 Serial.println("Le bluetooth est inactif");
	 }*/
	if (gps->isDispo()) {
		Serial.println("Le GPS est actif");
		gps->maj();
		donneesTR->setLatitude(gps->getLatitude());
		donneesTR->setLongitude(gps->getLongitude());
		donneesTR->setDatation(htr->getDatation());
	} else {
		Serial.println("Le bluetooth est inactif");
	}
	/* obd2->demande(C_DEFAUT);
	 int defauts = obd2->lire();
	 if (defauts) {
	 nbDefauts = nbDefauts + 1;
	 donneesTR.setDefauts(defauts);
	 }*/
}

void sendMessageStandard() {
	/*if (bluetooth->isActif()) {

	 //Si le bluetooth est actif, on envoi un message STANDARD
	 message->nouveau(STANDARD, donneesTR, bMsg);
	 sigfoxArduino->

	 } else {*/
	//Sinon le bluetooth n'est pas actif on envoi un message dégadé
	message->nouveau(DEGRADE, donneesTR, bMsg);
	Serial.println("message stnd encodé");
	//}
}

void sendMessageGPS() {

	message->nouveau(GPS_SEUL, donneesTR, bMsg);
	Serial.println("message GPS encodé");

}

