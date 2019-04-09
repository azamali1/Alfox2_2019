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
#define T_MSG_STND 720000 //12 minutes en ms
#define T_MSG_GPS 3600000 //1h en ms

byte bMsg[12];

unsigned long dureeCumulee = 0;
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

void sendMessageStandard();
void sendMessageGPS();
void majDataTR();
void configureInterrupt_timer4_1ms();

void setup() {
	Serial.begin(9600);
	delay(10000);
	message = new Message();
	htr = HTR::getInstance();
	sigfoxArduino = SigfoxArduino::getInstance();
	bluetooth = Bluetooth::getInstance(PINALIM, PINEN);
	//obd2 = OBD2::getInstance(bluetooth);

	//Acquisition datation par GPS
	gps = GPS::getInstance();
	configureInterrupt_timer4_1ms();
	gps->maj();
	delay(5000);
	htr->setDatation(gps->getDatation());

	donneesTR = new DonneesTR();
	sd = CarteSD::getInstance();
	delay(500);

}

void loop() {
	Serial.println("Entrée dans la loop");
	heureDebut = millis();

	Serial.println(dureeCumulee);

	majDataTR();

	sd->ecrire(donneesTR);

	if (dureeCumulee >= T_MSG_STND) {
		for (int i = 0; i < 20; i++) {
			Serial.println(
					"! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !");
		}
		sendMessageStandard();
	} else if (dureeCumulee >= T_MSG_GPS) {
		for (int i = 0; i < 20; i++) {
			Serial.println(
					"! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !");
		}
		sendMessageGPS();
	}

	htr->majDatation(millis());

	//Durée constante de la loop

	delay(DUREE_LOOP - (millis() - heureDebut));
	dureeCumulee += DUREE_LOOP - (millis() - heureDebut);

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
	 sigfoxArduino->*/

	/* } else {
	 //Sinon le bluetooth n'est pas actif on envoi un message dégadé*/
	byte* messageEncode = message->nouveau(DEGRADE, donneesTR, bMsg);
	sigfoxArduino->envoyer(messageEncode);
	Serial.println("message stnd encodé");
//}

}

void sendMessageGPS() {

	message->nouveau(GPS_SEUL, donneesTR, bMsg);
	Serial.println("message GPS encodé");

}

void TC4_Handler()              // Interrupt Service Routine (ISR) for timer TC4
{

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

