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
#include "../../src/LedTri.h"

#define DUREE_LOOP 5000 //en millisecondes
#define DUREE_LOOP_SENDING_MESSAGE 10000
#define T_MSG_STND 720000 //12 minutes en ms
#define T_MSG_ECO 3600000 //1h en ms
#define T_MSG_GPS 720000
#define T_MSG_MAINTENANCE 720000
#define T_MSG_DORMIR 3600000

byte messageEncode[12];

Etat etat;

unsigned long dureeCumulee = 0;
unsigned long heureDebut;
unsigned long tempoMessage;

bool chgtModeSrv;

SigfoxArduino* sigfoxArduino;
HTR* htr;
Message* message;
Bluetooth* bluetooth;
OBD2* obd2;
GPS* gps;
DonneesTR* donneesTR;
CarteSD* sd;
LedTri* led = LedTri::getInstance(0, 0, 0);

void majDataTR();
void nouvelEtat(Etat e);
void traiterEvenement(Event ev);
void traiterEtat(ModeG mode);

//Les keepWatch sont les surveillances des evenements

void keepWatchSerial();
void keepWatchOBD2();

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
	keepWatchOBD2();
	keepWatchSerial(); //Peut être bloquant

	// ---------------------------------------------------
	// -------------- TRAITEMENTS COURANTS ---------------

	traiterEtat(DO);
	sd->ecrire(donneesTR);

///////////////////////////////////////////////////////////////////////////

	//Duree de loop contrôlée

	if (messageEnvoye == true) { //On prends plus de temps pour laisser la carte envoyer le message
		dureeCumulee += DUREE_LOOP_SENDING_MESSAGE - (millis() - heureDebut)
				+ 1; //Decalage volontaire pour compenser le temps d'execution

		delay(DUREE_LOOP_SENDING_MESSAGE - (millis() - heureDebut));
	} else { //Duree standard de la loop sans messages
		dureeCumulee += DUREE_LOOP - (millis() - heureDebut) + 1;

		delay(DUREE_LOOP - (millis() - heureDebut));
	}
	//fin
}

void majDataTR() {

	if (etat == STANDARD) {

		donneesTR->setVitesse(obd2->lireVitesse());
		delay(250);
		donneesTR->setRegime(obd2->lireRegimeMoteur());
		delay(250);
		donneesTR->setConsommation(obd2->lireConsomation());
		delay(250);

		if (gps->isDispo()) {

			gps->maj();
			donneesTR->setLatitude(gps->getLatitude());
			donneesTR->setLongitude(gps->getLongitude());
			donneesTR->setDatation(gps->getDatation());
			Serial.println("Le GPS est actif");
		} else {
			Serial.println("Le GPS est occupé");
		}
	}
}

void nouvelEtat(Etat e) {

	if (e != etat) {
		traiterEtat(EXIT);
		// on doit toujours revenir à un état de suivi normal
		if (e == STANDARD) {
			if (obd2->isConnected() == true) {
				etat = STANDARD;
			} else {
				etat = DEGRADE;
			}
		} else
			etat = e;
		traiterEtat(ENTRY);
		traiterEtat(DO);
		chgtModeSrv = false;
	}
}

void traiterEvenement(Event ev) {

	switch (etat) {
	case INIT:
		nouvelEtat(INIT);
		break;
	case STANDARD:
		switch (ev) {
		case MODE_DMD_GPS:
			nouvelEtat(DMD_GPS);
			break;
		case MODE_GPS:
			nouvelEtat(GPS_SEUL);
			break;
		case OBD2_OFF:
			nouvelEtat(DEGRADE);
			break;
		case MODE_DORMIR:
			nouvelEtat(DORMIR);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		}
		break;
	case DEGRADE:
		switch (ev) {
		case MODE_DMD_GPS:
			nouvelEtat(DMD_GPS);
			break;
		case MODE_GPS:
			nouvelEtat(GPS_SEUL);
			break;
		case OBD2_ON:
			nouvelEtat(STANDARD);
			break;
		case MODE_DORMIR:
			nouvelEtat(DORMIR);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		}
		break;
	case DMD_GPS:
		nouvelEtat(DMD_GPS);
		break;
	case GPS_SEUL:
		switch (ev) {
		case MODE_STANDARD:
			nouvelEtat(STANDARD);
			break;
		case MODE_DORMIR:
			nouvelEtat(DORMIR);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		}
		break;
	case DORMIR:
		switch (ev) {
		case MODE_STANDARD:
			nouvelEtat(STANDARD);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		}
		break;
	case MAINTENANCE:
		switch (ev) {
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		case MODE_STANDARD:
			nouvelEtat(STANDARD);
			break;
		}
		break;
	}

}

void traiterEtat(ModeG mode) {
	switch (etat) {
	case INIT:
		switch (mode) {
		case ENTRY:
			break;
		case DO:
			Serial.println("Initialisation");
			nouvelEtat(STANDARD);
			break;
		case EXIT:
			break;
		}
		break;
	case STANDARD:
		switch (mode) {
		case ENTRY:
			majDataTR();
			dureeCumulee = 0;
			break;
		case DO:
			gps->maj();
			majDataTR();
			if (dureeCumulee >= T_MSG_STND) {
				Serial.println("Envoi d'un message STANDARD");
				message->nouveau(etat, donneesTR, messageEncode);
				sigfoxArduino->envoyer(messageEncode); //Le serial se déconnecte systématiquement dans SigFox.endpaquet();
				//Les println et les write sont donc inutiles ici, il est donc nécéssaire de vérifier l'envoi du message sur https://backend.sigfox.com/
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DEGRADE:
		switch (mode) {
		case ENTRY:
			dureeCumulee = 0;
			break;
		case DO:
			gps->maj();
			if (dureeCumulee >= T_MSG_STND) {
				Serial.println("Envoi d'un message DEGRADE");
				message->nouveau(etat, donneesTR, messageEncode);
				sigfoxArduino->envoyer(messageEncode); //Le serial se déconnecte systématiquement dans SigFox.endpaquet();
				//Les println et les write sont donc inutiles ici, il est donc nécéssaire de vérifier l'envoi du message sur https://backend.sigfox.com/
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DMD_GPS:
		switch (mode) {
		case ENTRY:
			break;
		case DO:
			Serial.println("Envoi d'un message DMD_GPS");
			gps->maj();
			majDataTR();
			message->nouveau(etat, donneesTR, messageEncode);
			sigfoxArduino->envoyer(messageEncode); //Le serial se déconnecte systématiquement dans SigFox.endpaquet();
			//Les println et les write sont donc inutiles ici, il est donc nécéssaire de vérifier l'envoi du message sur https://backend.sigfox.com/
			nouvelEtat(STANDARD);
			break;
		case EXIT:
			break;
		}
		break;
	case GPS_SEUL:
		switch (mode) {
		case ENTRY:
			dureeCumulee = 0;
			break;
		case DO:
			gps->maj();
			majDataTR();
			if (dureeCumulee >= T_MSG_STND) {
				Serial.println("Envoi d'un message GPS_SEUL");
				message->nouveau(etat, donneesTR, messageEncode);
				sigfoxArduino->envoyer(messageEncode); //Le serial se déconnecte systématiquement dans SigFox.endpaquet();
				//Les println et les write sont donc inutiles ici, il est donc nécéssaire de vérifier l'envoi du message sur https://backend.sigfox.com/
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DORMIR:
		switch (mode) {
		case ENTRY:
			Serial.println("Envoi d'un message DORMIR");
			gps->maj();
			majDataTR();
			if (dureeCumulee >= T_MSG_DORMIR) {
				Serial.println("Envoi d'un message DORMIR");
				message->nouveau(etat, donneesTR, messageEncode);
				sigfoxArduino->envoyer(messageEncode); //Le serial se déconnecte systématiquement dans SigFox.endpaquet();
				//Les println et les write sont donc inutiles ici, il est donc nécéssaire de vérifier l'envoi du message sur https://backend.sigfox.com/
			}
			break;
		case DO:
			break;
		}
		break;
	case MAINTENANCE:
		switch (mode) {
		case ENTRY:
			// afficher un id sur la console
			Serial.println("Envoi d'un message MAINTENANCE");
			break;
		case DO:
			break;
		case EXIT:
			break;
		}
		break;
	case ECO:
		switch (mode) {
		case ENTRY:

			break;
		case DO:
			break;
		case EXIT:
			break;
		}
	}
}

void keepWatchSerial() { // Surveille la voie série pour passage en maintenance
	// Surveillance de la voie série
	String car;
	int donneesAlire = Serial.available(); //lecture du nombre de caractères disponibles dans le buffer
	if (car != NULL && donneesAlire > 0) { //si le serial a reçu un caractère // si le buffer n'est pas vide
		car = Serial.readString();      //lecture du caractère reçu
		//while(Serial.read(donneesAlire) != -1);  Permet de lire et vider tout le buffer; à voir si à utiliser?

		if (car == "#") {
			traiterEvenement(MODE_MAINTENANCE);
		}
	}

}

void keepWatchOBD2() {
	// Surveillance du Bluetooth
	if (OBD2_ON) {
		if (etat == DEGRADE) {
			traiterEvenement(OBD2_ON);
		} else if (etat == STANDARD)
			traiterEvenement(OBD2_OFF);
	}
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

