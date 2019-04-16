#include <Arduino.h>
#include "../../src/GPS.h"
#include "../../src/DonneesTR.h"
#include "../../src/Bluetooth.h"
#include "../../src/CarteSD.h"
#include "../../src/OBD2.h"
#include "../../src/Global.h"
#include "../../src/Message.h"
#include "../../src/HTR.h"
#include "../../src/SigfoxArduino.h"

#define DUREE_LOOP 5000 //en millisecondes
#define DUREE_LOOP_SENDING_MESSAGE 10000
#define T_MSG_STND 720000 //12 minutes en ms
#define T_MSG_GPS 3600000 //1h en ms

byte messageEncode[12];

unsigned long dureeCumulee = 0;
unsigned long dureeCumuleeGPS = 0;
unsigned long heureDebut;
unsigned long tempoMessage;

SigfoxArduino* sigfoxArduino;
HTR* htr;
Message* message;
Bluetooth* bluetooth;
OBD2* obd2;
GPS* gps;
DonneesTR* donneesTR;
CarteSD* sd;

void sendMessageNormal();
void sendMessageGPS();
void majDataTR();
void afficherHeure();
void SERCOM3_Handler();
void TC4_Handler();
void configureInterrupt_timer4_1ms();

void setup() {
	Serial.begin(115200);
	delay(10000);
	message = new Message();
	htr = HTR::getInstance();
	sigfoxArduino = SigfoxArduino::getInstance();
	bluetooth = Bluetooth::getInstance(PINALIM, PINEN);
	Serial.println("Test de la classe Bluetooth");
	bluetooth->connexion("780C,B8,46F54"); // PC Commenge simulateur
	delay(2000);
	Serial.println(bluetooth->isActif());
	obd2 = OBD2::getInstance(bluetooth);

	//Acquisition datation par GPS
	gps = GPS::getInstance();
	configureInterrupt_timer4_1ms();
	gps->maj();
	delay(500);
	htr->setDatation(gps->getDatation());

	donneesTR = new DonneesTR();
	sd = CarteSD::getInstance();
	delay(10000);

}

void loop() {

	heureDebut = millis();

	bool messageEnvoye = false;

	gps->maj();

	majDataTR();

	afficherHeure();

	sd->ecrire(donneesTR);

	if (dureeCumulee >= T_MSG_STND) {

		for (int i = 0; i < 3; i++) {
			Serial.println("! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !");
		}

		sendMessageNormal();
		dureeCumulee = 0;
		messageEnvoye = true;

	}
	if (dureeCumuleeGPS >= T_MSG_GPS) {

		for (int i = 0; i < 3; i++) {
			Serial.println("# # # # # # # # # # # # # # # # # # # # # # #");
		}

		sendMessageGPS();
		dureeCumuleeGPS = 0;
		messageEnvoye = true;

	}

	//Durée constante de la loop avec cas des loop où les messages sont envoyés

	if (messageEnvoye == true) { //On prends plus de temps pour laisser la carte envoyer le message
		dureeCumulee += DUREE_LOOP_SENDING_MESSAGE - (millis() - heureDebut)
				+ 1; //Decalage volontaire pour compenser le temps d'execution
		dureeCumuleeGPS += DUREE_LOOP_SENDING_MESSAGE - (millis() - heureDebut)
				+ 1; //Decalage volontaire pour compenser le temps d'execution
		delay(DUREE_LOOP_SENDING_MESSAGE - (millis() - heureDebut));
	} else { //Duree standard de la loop sans messages
		dureeCumulee += DUREE_LOOP - (millis() - heureDebut) + 1;
		dureeCumuleeGPS += DUREE_LOOP - (millis() - heureDebut) + 1;
		delay(DUREE_LOOP - (millis() - heureDebut));
	}

	Serial.println("\n-----------------------------------------------------\n");

	//fin

}

void majDataTR() {
	Serial.println("entrée dans majDAtaTR");
	if (obd2->isConnected() == true) {
		Serial.println("Le bluetooth est actif");

		donneesTR->setVitesse(obd2->lireVitesse());

		Serial.println("0");

		delay(250);
		donneesTR->setRegime(obd2->lireRegimeMoteur());

		Serial.println("1");

		delay(250);
		//donneesTR->setConsommation(obd2->lireConsomation());

		Serial.println("2");

		delay(250);

	} else {
		Serial.println("OBD2 est injoignable");
	}
	if (gps->isDispo()) {

		gps->maj();
		donneesTR->setLatitude(gps->getLatitude());
		donneesTR->setLongitude(gps->getLongitude());
		donneesTR->setDatation(gps->getDatation());
		Serial.println("Le GPS est actif");
	} else {
		Serial.println("Le gps est occupé");
	}
}

void sendMessageNormal() {
	if (obd2->isConnected()) {

		//Si on peut contacter OBD2, on envoi un message STANDARD

		message->nouveau(STANDARD, donneesTR, messageEncode);
		sigfoxArduino->envoyer(messageEncode); //Le serial se déconnecte systématiquement dans SigFox.endpaquet();
		//Les println et les write sont donc inutiles ici, il est donc nécéssaire de vérifier l'envoi du message sur https://backend.sigfox.com/

	} else {
		//Sinon OBD 2 n'est pas connecté, alors on envoi un message dégradé*/

		message->nouveau(DEGRADE, donneesTR, messageEncode);
		sigfoxArduino->envoyer(messageEncode); //Le serial se déconnecte systématiquement dans SigFox.endpaquet();
		//Les println et les write sont donc inutiles ici, il est donc nécéssaire de vérifier l'envoi du message sur https://backend.sigfox.com/

	}

}

void sendMessageGPS() {

	message->nouveau(GPS_SEUL, donneesTR, messageEncode);
	sigfoxArduino->envoyer(messageEncode);

}

void afficherHeure() {
	Serial.print(gps->getDatation().tm_mday);
	Serial.print("/");
	Serial.print(gps->getDatation().tm_mon);
	Serial.print("/");
	Serial.print(gps->getDatation().tm_year);
	Serial.print(" ");
	Serial.print(gps->getDatation().tm_hour);
	Serial.print(":");
	Serial.print(gps->getDatation().tm_min);
	Serial.print(":");
	Serial.println(gps->getDatation().tm_sec);
}

void SERCOM3_Handler() {
	bluetooth->getLiaisonBT()->IrqHandler();
}

void TC4_Handler() {            // Interrupt Service Routine (ISR) for timer TC4

	// Check for overflow (OVF) interrupt
	if (TC4->COUNT16.INTFLAG.bit.OVF && TC4->COUNT16.INTENSET.bit.OVF) {
		char c = gps->readDATA();
		REG_TC4_INTFLAG = TC_INTFLAG_OVF;        // Clear the OVF interrupt flag
	}
}

//Fonction englobant la configuration et le démarrage des interruptions du Timer 4 toutes les 1 ms.
void configureInterrupt_timer4_1ms() {
	// Set up the generic clock (GCLK4) used to clock timers
	REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) | // On divise les 48MHz  par 1: 48MHz/1=48MHz
			GCLK_GENDIV_ID(4);            // Select Generic Clock (GCLK) 4
	while (GCLK->STATUS.bit.SYNCBUSY)
		;              // Wait for synchronization

	REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC | // Set the duty cycle to 50/50 HIGH/LOW
			GCLK_GENCTRL_GENEN |         // Enable GCLK4
			GCLK_GENCTRL_SRC_DFLL48M |   // Set the 48MHz clock source
			GCLK_GENCTRL_ID(4);          // Select GCLK4
	while (GCLK->STATUS.bit.SYNCBUSY)
		;              // Wait for synchronization

	// Feed GCLK4 to TC4 and TC5
	REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |      // Enable GCLK4 to TC4 and TC5
			GCLK_CLKCTRL_GEN_GCLK4 |     // Select GCLK4
			GCLK_CLKCTRL_ID_TC4_TC5;     // Feed the GCLK4 to TC4 and TC5
	while (GCLK->STATUS.bit.SYNCBUSY)
		;              // Wait for synchronization

	REG_TC4_COUNT16_CC0 = 47999; // Le timer compte de 0 à 47999 soit 48000/48000000 = 1 ms, puis déclenche une interruption
	while (TC4->COUNT16.STATUS.bit.SYNCBUSY)
		;       // Wait for synchronization

	//NVIC_DisableIRQ(TC4_IRQn);
	//NVIC_ClearPendingIRQ(TC4_IRQn);
	NVIC_SetPriority(TC4_IRQn, 0); // Set the Nested Vector Interrupt Controller (NVIC) priority for TC4 to 0 (highest)
	NVIC_EnableIRQ(TC4_IRQn); // Connect TC4 to Nested Vector Interrupt Controller (NVIC)

	REG_TC4_INTFLAG |= TC_INTFLAG_OVF;              // Clear the interrupt flags
	REG_TC4_INTENSET = TC_INTENSET_OVF;             // Enable TC4 interrupts
	// REG_TC4_INTENCLR = TC_INTENCLR_OVF;          // Disable TC4 interrupts

	REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV1 | // On met le présidviseur à 1. Pourrait valoir DIV2, DIC4, DIV8, DIV16, DIV64, DIV256, DIV1024
			TC_CTRLA_WAVEGEN_MFRQ | // Timer 4 en mode "match frequency" (MFRQ)
			TC_CTRLA_ENABLE;               // Enable TC4
	while (TC4->COUNT16.STATUS.bit.SYNCBUSY)
		;       // Wait for synchronization
}

