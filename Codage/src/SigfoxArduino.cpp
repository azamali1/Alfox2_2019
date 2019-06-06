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
	Serial.println("envoye du message Sigfox");
	SigFox.begin();	//launch Sigfox
	delay(1);
	SigFox.debug();
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

bool SigfoxArduino::sendMessageAndGetResponse(byte* bMsg, byte* rMsg) {
	unsigned int index = 0;

	Serial.println("envoi et reception du message Sigfox");
// Start the module
	if (!SigFox.begin()) {
		Serial.println("Shield error or not present!");
		return false;
	}
	delay(100);
	 SigFox.debug();

	SigFox.status();
	delay(1);
	SigFox.beginPacket();
	SigFox.write(bMsg, 12);

	int ret = SigFox.endPacket(true); // send buffer to SIGFOX network and wait for a response
	/*Serial.end();
	 delay(100);
	 Serial.begin(9600);
	 delay(100);
	 while (!Serial) {};*/
	if (ret > 0) {
		Serial.println("pas de transmission");
	} else {
		Serial.println("Transmission ok");
	}

	Serial.println(SigFox.status(SIGFOX));
	Serial.println(SigFox.status(ATMEL));

	if (SigFox.parsePacket()) {
		Serial.println("Réponse du serveur:");
		while (SigFox.available()) {
			rMsg[index] = SigFox.read();
			index++;
		}
		delay(100);
		SigFox.end();
		return true;

	} else {
		delay(100);
		SigFox.end();
		return false;
	}
}

bool SigfoxArduino::isMsgRecu(byte* bMsg) {
	unsigned int index = 0;
	Serial.println("en attente de reception du message Sigfox");

	if (SigFox.parsePacket()) {

		while (SigFox.available()) {
			if (index < sizeof bMsg)
				bMsg[index++] = SigFox.read();
			Serial.println(bMsg[index++]);
		}
		SigFox.end();
		return true;
		Serial.println("message Sigfox reçus ");

	} else {
		SigFox.end();
		return false;
		Serial.println("message Sigfox non reçus ");
	}

}

//String SigfoxArduino::lire(){
//}
