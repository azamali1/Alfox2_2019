/*/=========================/*/
/*/ File: SigfoxArduino.cpp /*/
/*/  create: 4 Avril 2019   /*/
/*/=========================/*/

#include <Arduino.h>
#include <SigFox.h>
#include <ArduinoLowPower.h>

#include "SigfoxArduino.h"

SigfoxArduino* SigfoxArduino::SigArduinoInstance = 0;

SigfoxArduino* SigfoxArduino::getInstance() {

	if (SigArduinoInstance == 0) {
		SigArduinoInstance = new SigfoxArduino();
	}
	return SigArduinoInstance;
}

SigfoxArduino::SigfoxArduino() {

}

bool SigfoxArduino::envoyer(byte* bMsg) {
	SigFox.begin();	//launch Sigfox
	delay(1);
	SigFox.beginPacket();	//start Paquet to send
	SigFox.write(bMsg, 12);
	SigFox.endPacket(); //Le serial se déconnecte systématiquement ici, vérifier l'envoi du message sur https://backend.sigfox.com/
	SigFox.end();	//end SigFox

	return 0;
}

//int SigfoxArduino::getNbMsgEmisParH(){
//}

//void SigfoxArduino::setNbMsgEmisParH(int nbMsgRemisParHeure){
//}

bool SigfoxArduino::sendMessageAndGetResponse(byte* bMsg) {
	unsigned int index = 0;

// Start the module
	SigFox.begin();
	delay(1);

	SigFox.beginPacket();
	SigFox.write(bMsg, 12);
	SigFox.endPacket(); // send buffer to SIGFOX network and wait for a response

	if ((SigFox.parsePacket() != 0) && (SigFox.parsePacket() != NULL)) {

		while (SigFox.available()) {
			if (index < sizeof bMsg)
				bMsg[index++] = SigFox.read();
		}
		SigFox.end();
		return true;

	} else {
		SigFox.end();
		return false;
	}
}

bool SigfoxArduino::isMsgRecu(byte* bMsg) {
	unsigned int index = 0;


	if ((SigFox.parsePacket() != 0) && (SigFox.parsePacket() != NULL)) {

		while (SigFox.available()) {
			if (index < sizeof bMsg)
				bMsg[index++] = SigFox.read();
		}
		SigFox.end();
		return true;

	} else {
		SigFox.end();
		return false;
	}

}

//String SigfoxArduino::lire(){
//}
