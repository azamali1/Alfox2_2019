#include "../../src/LedTri.h"

LedTri* maLed = new LedTri(redLedPin, greenLedPin, blueLedPin); // définit la pin pour chaque couleur

void setup() {
	// put your setup code here, to run once:

}

void loop() {
	// put your main code here, to run repeatedly:

	for (int r = 0; r < 254; r++) {
		maLed->setCouleur(rouge, r);
		delay(10);
	}
	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(rouge, r);
		delay(10);
	}

	delay(1000);
	for (int r = 0; r < 254; r++) {
		maLed->setCouleur(vert, r);
		delay(10);
	}
	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(vert, r);
		delay(10);
	}

	delay(1000);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(bleu, r);
		delay(10);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(bleu, r);
		delay(10);
	}

	delay(1000);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(magenta, r);
		delay(10);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(magenta, r);
		delay(10);
	}

	delay(1000);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(cyan, r);
		delay(10);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(cyan, r);
		delay(10);
	}

	delay(1000);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(jaune, r);
		delay(10);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(jaune, r);
		delay(10);
	}

	delay(1000);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(r, r, r);
		delay(10);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(r, r, r);
		delay(10);
	}

	delay(1000);
	maLed->setCouleur(255, 255, 255);
	maLed->resetCouleur();
}

