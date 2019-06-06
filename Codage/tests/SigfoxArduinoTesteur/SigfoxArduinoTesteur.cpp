#include <Arduino.h>

#include "../../src/SigfoxArduino.h"
#include "../../src/DonneesTR.h"
#include "../../src/Message.h"
#include "../../src/LedTri.h"


bool msgRecu = false;

SigfoxArduino * sigfoxArduino;
Message * message;
DonneesTR* donneesTR;
LedTri* ledTri;

//String messageTest("123456789123");
byte messageEncode[12];
byte messageRecu[8];

void setup() {
	Serial.begin(9600);
	 while (!Serial) {};
	Serial.println("Test de la classe SigfoxArduino");
	delay(10000);
	sigfoxArduino = SigfoxArduino::getInstance();
	message = new Message();
	donneesTR = DonneesTR::getInstance();
	ledTri = LedTri::getInstance(redLedPin, greenLedPin, blueLedPin);

	ledTri->setCouleur(255,255 ,255);
	Serial.println("création du message");
	donneesTR->razStat();
	time_t timestamp = time( NULL );
	struct tm * now = localtime( & timestamp );
	donneesTR->setDatation(*now);

	message->nouveau(DEGRADE, donneesTR, messageEncode);
	delay(2000);
	ledTri->setCouleur(bleu, 255);
	Serial.println("envoie du message");
	//test
	/*messageTest[0]=0xc4;
	messageTest[1]=0x58;
	messageTest[2]=0x06;
	messageTest[3]=0x57;
	messageTest[4]=0x2b;
	messageTest[5]=0x3d;
	messageTest[6]=0x39;
	messageTest[7]=0x38;
	messageTest[8]=0x01;
	messageTest[9]=0x1e;
	messageTest[10]=0x5d;
	messageTest[11]=0x62;
	messageTest.trim();*/
	msgRecu = sigfoxArduino->sendMessageAndGetResponse(messageEncode, messageRecu);
	//while (!Serial) {};
	if (msgRecu) {
		ledTri->setCouleur(cyan, 255);
		Serial.println("message reçu :");
		for (int i = 0; i < 8; i++) {
			Serial.print(messageRecu[i],HEX);

		}
	}
	else{
		ledTri->setCouleur(rouge, 255);
		Serial.println("message non reçu");
	}






}

void loop() {

}
