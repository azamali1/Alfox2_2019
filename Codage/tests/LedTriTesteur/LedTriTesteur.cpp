#include "../../src/LedTri.h"


LedTri* maLed = new LedTri(redLedPin, greenLedPin, blueLedPin); // définit la pin pour chaque couleur

void setup() {
	// put your setup code here, to run once:

}

void loop() {
	// put your main code here, to run repeatedly:

	//Teste 2 fois toutes les valeurs possible de la fonction setCouleur à deux paramètres\\

	for (int r = 0; r < 254; r++) {
		maLed	->setCouleur(rouge, r);
		delay(5);
	}
	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(rouge, r);
		delay(5);
	}

	delay(5);
	for (int r = 0; r < 254; r++) {
		maLed->setCouleur(vert, r);
		delay(5);
	}
	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(vert, r);
		delay(5);
	}

	delay(5);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(bleu, r);
		delay(5);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(bleu, r);
		delay(5);
	}

	delay(5);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(magenta, r);
		delay(5);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(magenta, r);
		delay(5);
	}

	delay(5);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(cyan, r);
		delay(5);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(cyan, r);
		delay(5);
	}

	delay(5);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(jaune, r);
		delay(5);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(jaune, r);
		delay(5);
	}

	//Teste 2 fois toutes les valeurs possible de la fonction setCouleur à trois paramètres
	delay(5);
	for (int r = 0; r < 255; r++) {
		maLed->setCouleur(r, r, r);
		delay(5);
	}

	for (int r = 255; r >= 0; r--) {
		maLed->setCouleur(r, r, r);
		delay(5);
	}
	maLed->resetCouleur();
	delay(5);
}
