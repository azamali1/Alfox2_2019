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
#define DUREE_LOOP_SENDING_MESSAGE 45000
#define T_MSG_NORMAL 720000/8 //12 minutes en ms
#define T_MSG_ECO 3600000 //1h en ms
#define T_MSG_GPS 720000/8
#define T_MSG_MAINTENANCE 720000
#define T_MSG_DORMIR 3600000

byte messageEncode[12];
byte reponseDecode[8];

Etat etat;

unsigned long dureeCumulee = 0;
unsigned long heureDebut;
unsigned long tempoMessage;

bool chgtModeSrv;
bool fromStandard = true;
bool messageEnvoye = false;

SigfoxArduino* sigfoxArduino;
HTR* htr;
Message* message;
Bluetooth* bluetooth;
OBD2* obd2;
GPS* gps;
DonneesTR* donneesTR;
CarteSD* sd;
LedTri* led;

void majDataTR();
void nouvelEtat(Etat e);
void traiterEvenement(Event ev);
void traiterEtat(ModeG mode);
void keepWatchSerial(); //Les keepWatch sont les surveillances de certains evenements
void keepWatchOBD2();

void traiterMessage(bool askForResponse);

void afficherGPS();
void afficherHeure();

void SERCOM3_Handler();
void TC4_Handler();	// Trois fonctions indispensables pour l'utilisation de la carte et de ses modules
void configureInterrupt_timer4_1ms();

void setup() {
	Serial.begin(115200);
	Serial1.begin(9600);
	led = LedTri::getInstance(redLedPin, greenLedPin, blueLedPin);
	led->setCouleur(255, 255, 255);
	delay(10000);
	message = new Message();
	htr = HTR::getInstance();
	sigfoxArduino = SigfoxArduino::getInstance();
	bluetooth = Bluetooth::getInstance(PINALIM, PINEN);

	//Commenter dans OBD2.h le #define SIMU pour ne pas utiliser le simulateur

#ifdef SIMU
	Serial.println("Connexion Bluetooth au simulateur OBD2 ...");
	//bluetooth->connexion("780C,B8,46F54"); // PC Commenge simulateur
	bluetooth->connexion("C0CB,38,D768D5"); // PC Mr. Commenge simulateur SONY
#else
			Serial.println("Connexion Bluetooth à l'OBD2 de  la voiture ...");
			//OBD2 noir KONNWEI
			bluetooth->connexion("B22B,1C,70EA6");
#endif

	delay(2000);
	Serial.println(bluetooth->isActif());
	obd2 = OBD2::getInstance(bluetooth);

	//Acquisition datation par GPS
	gps = GPS::getInstance();
	configureInterrupt_timer4_1ms();
	gps->maj();
	delay(500);
	htr->setDatation(gps->getDatation());
	led = LedTri::getInstance(redLedPin, greenLedPin, blueLedPin);
	donneesTR = new DonneesTR();
	sd = CarteSD::getInstance();
	nouvelEtat(STANDARD);
	traiterEtat(ENTRY);
	delay(10000);
}

void loop() {

	heureDebut = millis();
	Serial.println();
	Serial.println();
	Serial.println("#############################");
	Serial.println();
	Serial.println("Entrée dans la loop");
	messageEnvoye = false;
	keepWatchOBD2();
	//keepWatchSerial(); //Peut être bloquant

	// -------------- TRAITEMENTS COURANTS ---------------

	/*/
	 * Lorsque la classe reception de message sera opérationelle
	 * il faudra placer la lecture de message juste après un envoi avec un delai de 30s
	 * et traiter l'évenement que l'on placera dans une variable globale de type Event
	 * Par conséquant, il faudra créer de nouvelles fonctions KeepWatch et ensuite faire :
	 * traiterEtat(EXIT);
	 * nouvelEtat(etat);
	 /*/

	traiterEtat(DO);
	//sd->ecrire(donneesTR);

	Serial.print("Programme traité en : ");

	//Duree de loop contrôlée

	if (messageEnvoye == true) { //On prends plus de temps pour laisser la carte envoyer le message
		Serial.println(millis() - heureDebut);
		dureeCumulee += DUREE_LOOP_SENDING_MESSAGE - (millis() - heureDebut)
				+ 1; //Decalage volontaire pour compenser le temps d'execution de ce calcul

		delay(DUREE_LOOP_SENDING_MESSAGE - (millis() - heureDebut));
	} else { //Duree standard de la loop sans messages
		Serial.println(millis() - heureDebut);
		dureeCumulee += DUREE_LOOP - (millis() - heureDebut);

		delay(DUREE_LOOP - (millis() - heureDebut));
	}
	//fin
}

void majDataTR() {

	if (etat == NORMAL) {

		donneesTR->setVitesse(obd2->lireVitesse());
		delay(250);
		donneesTR->setRegime(obd2->lireRegimeMoteur());
		delay(250);
		if (messageEnvoye == true) {
			donneesTR->majDistance(DUREE_LOOP_SENDING_MESSAGE);
		} else {
			donneesTR->majDistance(DUREE_LOOP);
		}
		delay(250);

#ifndef SIMU //En simulation la conso ne peut pas être récupérée (c'est donc bloquant)
		donneesTR->setBatterie(obd2->lireBatterie());
		delay(250);
		donneesTR->setConsommation(obd2->lireConsomation());
		delay(250);
#endif
		Serial.println();
		Serial.println("------------------------------------");
		Serial.println("Données véhicule :");
		Serial.print("Vitesse :");
		Serial.print(donneesTR->getVitesse());
		Serial.println(" km/h");
		Serial.print("Distance :");
		Serial.print((int) donneesTR->getDistanceParcourue());
		Serial.println(" m");
		Serial.print("Régime :");
		Serial.print(donneesTR->getRegime());
		Serial.println(" tours/min");

#ifndef SIMU //En simulation la conso ne peut pas être récupérée (c'est donc bloquant)
		Serial.print("Tension batterie : ");
		Serial.print(donneesTR->getBatterie());
		Serial.println(" V");
		Serial.print("Consomation :");
		Serial.print(donneesTR->getConsommation());
		Serial.println(" l/100km");
#endif
		Serial.println("------------------------------------");
		Serial.println();
		Serial.println("Maj donneesTR done !");

	}
	gps->maj();
	if (gps->isDispo()) {
		donneesTR->setLatitude(gps->getLatitude());
		donneesTR->setLongitude(gps->getLongitude());
		donneesTR->setDatation(gps->getDatation());
		if (etat == DEGRADE) {
			if (messageEnvoye == true) {
				donneesTR->majDistance(true);
			} else {
				donneesTR->majDistance();
			}
			donneesTR->setVitesse(gps->getVitesse());
		}
		htr->setDatation(gps->getDatation());
		afficherGPS();
		afficherHeure();
		Serial.println("Le GPS est actif, Maj GPS done !");
	} else {
		Serial.println("Le GPS est occupé, Maj GPS not done !");
	}
}

void afficherGPS() {
	Serial.println();
	Serial.println("------------------------------------");
	Serial.println("Données GPS :");
	Serial.print("Latitude :");
	Serial.println(donneesTR->getLatitude(), 6);
	Serial.print("Longitude :");
	Serial.println(donneesTR->getLongitude(), 6);
	Serial.print("Vitesse GPS :");
	Serial.print(donneesTR->getVitesse());
	Serial.println(" km/h");
	Serial.println("------------------------------------");
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

void nouvelEtat(Etat e) {

	if (e != etat) {
		traiterEtat(EXIT);
		etat = e;
		traiterEtat(ENTRY);
		chgtModeSrv = false;
	}
}

void traiterEvenement(Event ev) {

	switch (etat) {
	case INIT:
		nouvelEtat(INIT);
		break;
	case NORMAL:
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
		default:
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
		default:
			break;

		}
		break;
	case DMD_GPS:
		nouvelEtat(DMD_GPS);
		break;
	case GPS_SEUL:
		switch (ev) {
		case MODE_NORMAL:
			nouvelEtat(NORMAL);
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
		default:
			break;
		}
		break;
	case DORMIR:
		switch (ev) {
		case MODE_NORMAL:
			nouvelEtat(NORMAL);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		default:
			break;
		}
		break;
	case MAINTENANCE:
		switch (ev) {
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		case MODE_NORMAL:
			nouvelEtat(NORMAL);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

}

void traiterEtat(ModeG mode) {
	switch (etat) {
	case INIT:
		switch (mode) {
		case ENTRY:
			led->setCouleur(255, 255, 255);
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
			led->setCouleur(255, 255, 255);
			dureeCumulee = 0;
			fromStandard = true;
			if (obd2->isConnected() == true) {
				nouvelEtat(NORMAL);
			} else {
				nouvelEtat(DEGRADE);
			}
			break;
		case DO:
			break;
		case EXIT:
			break;
		}

		break;
	case NORMAL:
		switch (mode) {
		case ENTRY:
			led->setVert(200);
			Serial.print("Entrée dans le mode ");
			Serial.println(etat);

			break;
		case DO:
			led->setVert(200);
			gps->maj();
			if (dureeCumulee >= T_MSG_NORMAL) {
				messageEnvoye = true;
				majDataTR();
				traiterMessage(true);
				dureeCumulee = 0;
			} else {
				majDataTR();
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DEGRADE:
		switch (mode) {
		case ENTRY:
			led->setMagenta(255);
			Serial.print("Entrée dans le mode ");
			Serial.println(etat);
			gps->maj();
			majDataTR();
			break;
		case DO:
			led->setMagenta(255);
			gps->maj();
			majDataTR();
			if (dureeCumulee >= T_MSG_NORMAL) {
				traiterMessage(true);
				/*#ifdef SIMU
				 Serial.println("Connexion Bluetooth au simulateur OBD2 ...");
				 bluetooth->connexion("780C,B8,46F54"); // PC Commenge simulateur
				 #else
				 Serial.println(
				 "Connexion Bluetooth à l'OBD2 de  la voiture ...");
				 //OBD2 noir KONNWEI
				 bluetooth->connexion("B22B,1C,70EA6");
				 #endif*/

				dureeCumulee = 0;
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DMD_GPS:
		switch (mode) {
		case ENTRY:
			led->setCyan(255);
			Serial.print("Entrée dans le mode ");
			Serial.println(etat);
			break;
		case DO:
			led->setCyan(255);
			Serial.println("Envoi d'un message DMD_GPS");
			gps->maj();
			majDataTR();
			traiterMessage(true);
			nouvelEtat(STANDARD);
			break;
		case EXIT:
			break;
		}
		break;
	case GPS_SEUL:
		switch (mode) {
		case ENTRY:
			led->setBleu(255);
			if (messageEnvoye == true) {
				dureeCumulee = 0;
			}
			Serial.print("Entrée dans le mode ");
			Serial.println(etat);
			break;
		case DO:
			led->setBleu(255);
			gps->maj();
			majDataTR();
			if (dureeCumulee >= T_MSG_NORMAL) {
				traiterMessage(true);
				dureeCumulee = 0;
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DORMIR:
		switch (mode) {
		case ENTRY:
			led->resetCouleur();
			Serial.print("Entrée dans le mode ");
			Serial.println(etat);

			break;
		case DO:
			led->resetCouleur();
			Serial.println("Envoi d'un message DORMIR");
			gps->maj();
			majDataTR();
			if (dureeCumulee >= T_MSG_DORMIR) {
				traiterMessage(true);
				dureeCumulee = 0;
			}
			break;
		}
		break;
	case MAINTENANCE:
		switch (mode) {
		case ENTRY:
			led->setRouge(255);
			Serial.print("Entrée dans le mode ");
			Serial.println(etat);

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
			led->resetCouleur();
			traiterMessage(true);
			dureeCumulee = 0;
			break;
		case DO:
			break;
		}
	}
}

void keepWatchSerial() { // Surveille la voie série pour passage en maintenance
// Surveillance de la voie série
	Serial.print("KeepWatchSerial status : ");
	String car;
	int donneesAlire = Serial.available(); //lecture du nombre de caractères disponibles dans le buffer
	if (car != NULL && donneesAlire > 0) { //si le serial a reçu un caractère // si le buffer n'est pas vide
		car = Serial.readString(); //lecture du caractère reçu
		//while(Serial.read(donneesAlire) != -1);  Permet de lire et vider tout le buffer; à voir si à utiliser?

		if (car == "#") {
			Serial.println("# reçu, passage en maintenance");
			traiterEvenement(MODE_MAINTENANCE);

		} else {
			Serial.println("# non reçu, mode actuel conservé");
		}
	} else {
		Serial.println("Aucun caractère reçu sur la voie série");
	}

}

void keepWatchOBD2() {
// Surveillance du Bluetooth
	Serial.print("KeepWatchOBD2 status : ");
	if (obd2->testerConnexion()) {
		Serial.println("OBD2 connecté");
		traiterEvenement(OBD2_ON);
	} else {
		Serial.println("OBD2 déconnecté");
		traiterEvenement(OBD2_OFF);
	}

}

void traiterMessage(bool askForResponse) {
	Serial.println("Création du message SigFox... ");
	message->nouveau(etat, donneesTR, messageEncode);
	messageEnvoye = true;
	Serial.println("Envoi du message à SigFox... ");
	if (askForResponse == false) {
		sigfoxArduino->envoyer(messageEncode);
	} else {
		led->setCouleur(255, 165 / 3, 0);
		if (sigfoxArduino->sendMessageAndGetResponse(messageEncode,
				reponseDecode)) {
			led->setCouleur(cyan, 255);
			delay(1000);
			nouvelEtat(message->decoderEtat(reponseDecode));

		} else {
			led->setMagenta(255);
			nouvelEtat(etat);
		}
	}
	delay(200);
	bluetooth->reinitialiserLiaisonSerie();
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
			GCLK_GENDIV_ID(4);        // Select Generic Clock (GCLK) 4
	while (GCLK->STATUS.bit.SYNCBUSY)
		;        // Wait for synchronization

	REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC | // Set the duty cycle to 50/50 HIGH/LOW
			GCLK_GENCTRL_GENEN |        // Enable GCLK4
			GCLK_GENCTRL_SRC_DFLL48M |        // Set the 48MHz clock source
			GCLK_GENCTRL_ID(4);        // Select GCLK4
	while (GCLK->STATUS.bit.SYNCBUSY)
		;        // Wait for synchronization

// Feed GCLK4 to TC4 and TC5
	REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |      // Enable GCLK4 to TC4 and TC5
			GCLK_CLKCTRL_GEN_GCLK4 |        // Select GCLK4
			GCLK_CLKCTRL_ID_TC4_TC5;        // Feed the GCLK4 to TC4 and TC5
	while (GCLK->STATUS.bit.SYNCBUSY)
		;        // Wait for synchronization

	REG_TC4_COUNT16_CC0 = 47999; // Le timer compte de 0 à 47999 soit 48000/48000000 = 1 ms, puis déclenche une interruption
	while (TC4->COUNT16.STATUS.bit.SYNCBUSY)
		;        // Wait for synchronization

//NVIC_DisableIRQ(TC4_IRQn);
//NVIC_ClearPendingIRQ(TC4_IRQn);
	NVIC_SetPriority(TC4_IRQn, 0); // Set the Nested Vector Interrupt Controller (NVIC) priority for TC4 to 0 (highest)
	NVIC_EnableIRQ(TC4_IRQn); // Connect TC4 to Nested Vector Interrupt Controller (NVIC)

	REG_TC4_INTFLAG |= TC_INTFLAG_OVF;        // Clear the interrupt flags
	REG_TC4_INTENSET = TC_INTENSET_OVF;        // Enable TC4 interrupts
// REG_TC4_INTENCLR = TC_INTENCLR_OVF;          // Disable TC4 interrupts

	REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV1 | // On met le présidviseur à 1. Pourrait valoir DIV2, DIC4, DIV8, DIV16, DIV64, DIV256, DIV1024
			TC_CTRLA_WAVEGEN_MFRQ | // Timer 4 en mode "match frequency" (MFRQ)
			TC_CTRLA_ENABLE;        // Enable TC4
	while (TC4->COUNT16.STATUS.bit.SYNCBUSY)
		;        // Wait for synchronization
}

