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

bool SigfoxArduino::envoyer(byte* bMsg) {
	SigFox.begin();	//launch Sigfox
	delay(1);
	SigFox.beginPacket();	//start Paquet to send
	SigFox.write(bMsg, 12);
	SigFox.endPacket();  // send buffer to SIGFOX network
	SigFox.end();	//end SigFox

	return 0;
}

//int SigfoxArduino::getNbMsgEmisParH(){
//}

//void SigfoxArduino::setNbMsgEmisParH(int nbMsgRemisParHeure){
//}

//bool SigfoxArduino::isMsgRecu() {
//}

//String SigfoxArduino::lire(){
//}
