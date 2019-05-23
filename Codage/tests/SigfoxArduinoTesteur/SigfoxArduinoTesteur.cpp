#include <Arduino.h>

#include "../../src/SigfoxArduino.h"
#include "../../src/DonneesTR.h"
#include "../../src/Message.h"

bool msgRecu = false;

SigfoxArduino * sigfoxArduino;
Message * message;
DonneesTR* donneesTR;

byte messageEncode[12];

void setup() {
	Serial.begin(9600);
	Serial.println("Test de la classe SigfoxArduino");
	delay(10000);
	sigfoxArduino = SigfoxArduino::getInstance();
	message = new Message();
	donneesTR = DonneesTR::getInstance();

}

void loop() {
	message->nouveau(DEGRADE, donneesTR, messageEncode);
	msgRecu = sigfoxArduino->sendMessageAndGetResponse(messageEncode);
	if (msgRecu) {
		delay(30000);
		for (int i = 0; i < 12; i++) {
			Serial.print(messageEncode[i]);
		}
	}
	delay(30000);


}
