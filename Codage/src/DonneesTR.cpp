#include "DonneesTR.h"

DonneesTR* DonneesTR::DonneesTRInstance = 0;

DonneesTR* DonneesTR::getInstance() {

	if (DonneesTRInstance == 0) {
		DonneesTRInstance = new DonneesTR();
	}
	return DonneesTRInstance;
}

DonneesTR::DonneesTR() {
	distanceParcourue = 0;
	nbDefauts = 1;
	defauts[4] = 1;
	consommation = 0;
	consoMoyenne = 0;
	consoMax = 0;
	vitesse = 0;
	vitesseMoyenne = 0;
	vitesseMax = 0;
	regime = 0;
	regimeMoyen = 0;
	regimeMax = 0;
	latitude = 0;
	longitude = 0;
	OBD2Actif = true;
	bluetoothActif = true;
}

DonneesTR::~DonneesTR() {
}

void DonneesTR::razStat() {
	nbDefauts = 0;
	defauts[4] = 0;
	consommation = 0;
	consoMoyenne = 0;
	consoMax = 0;
	vitesse = 0;
	vitesseMoyenne = 0;
	vitesseMax = 0;
	regime = 0;
	regimeMoyen = 0;
	regimeMax = 0;
	latitude = 0;
	longitude = 0;
	OBD2Actif = false;
	bluetoothActif = false;
	dateHTR.tm_year = 2018;
	dateHTR.tm_mday = 1;
	dateHTR.tm_mon = 0;
	dateHTR.tm_hour = 0;
	dateHTR.tm_min = 0;
	dateHTR.tm_sec = 0;
}

float DonneesTR::getConsommation() {
	return consommation;
}

int DonneesTR::getConsoMoyenne() {
	return consoMoyenne;
}

int DonneesTR::getConsoMax() {
	return consoMax;
}

int DonneesTR::getVitesseMoyenne() {
	return vitesseMoyenne;
}

int DonneesTR::getVitesseMax() {
	return vitesseMax;
}

int DonneesTR::getVitesse() {
	return vitesse;
}

int DonneesTR::getRegimeMoyen() {
	return regimeMoyen;
}

int DonneesTR::getRegimeMax() {
	return regimeMax;
}

int DonneesTR::getRegime() {
	return regime;
}

int DonneesTR::getNbDefaut() {
	return nbDefauts;
}

int DonneesTR::getDefauts(int numero) {
	return defauts[numero];
}

void DonneesTR::setVitesse(int vitesse) {
	this->vitesse = vitesse;
	if (vitesse > vitesseMax)
		vitesseMax = vitesse;

	valeurMoyenneVitesse *= moyenneVitesse;
	valeurMoyenneVitesse += vitesse;
	moyenneVitesse++;
	valeurMoyenneVitesse /= moyenneVitesse;
	vitesseMoyenne = valeurMoyenneVitesse;
}

void DonneesTR::setConsommation(float consommation) {
	float vitesseFloat = this->vitesse;
	this->consommation = ((1 / vitesseFloat) * (consommation)) * 100;

}

void DonneesTR::setRegime(int regime) {
	this->regime = regime;
	if (regime > regimeMax)
		regimeMax = regime;

	valeurMoyenneRegime *= moyenneRegime;
	valeurMoyenneRegime += regime;
	moyenneRegime++;
	valeurMoyenneRegime /= moyenneRegime;
	regimeMoyen = valeurMoyenneRegime;
}

float DonneesTR::getDistanceParcourue() {
	return distanceParcourue;
}

void DonneesTR::majDistance() // d = vt
{
	distanceParcourue += (vitesse * 5) / 3.6;
	Serial.println(distanceParcourue);
}

void DonneesTR::setLatitude(float latitude) {
	this->latitude = latitude;
}

void DonneesTR::setLongitude(float longitude) {
	this->longitude = longitude;
}

float DonneesTR::getLatitude() {
	return latitude;
}

float DonneesTR::getLongitude() {
	return longitude;
}

void DonneesTR::setDatation(struct tm dateGPS){

}

void DonneesTR::getDatation(){

}
/*
 void DonneesTR::majData(OBD2 obd2)
 {

 }*/

// modif pour le test unitaire de Message
bool DonneesTR::getOBD2Actif() {
	return OBD2Actif;
}

bool DonneesTR::getBluetoothActif() {
	return bluetoothActif;
}

void DonneesTR::initTestNORMAL() {
	// NORMAL : TM     K1  K2    K3  CD    CD  VM     VY    RM    RY    CM    CY
	// msg    : 209:d1 1:1 30:1e 0:0 42:2a 0:0 175:af 87:57 56:38 28:1c 92:5c 67:43
	// d1 = 1101 0001
	// 2a = 0x02 + 0x0A
	// K  = 01 30 00
	OBD2Actif = true;
	bluetoothActif = true;
	nbDefauts = 2;
	defauts[0] = 0x02;
	defauts[1] = 0x0A;
	defauts[2] = 0;
	defauts[3] = 0;
	distanceParcourue = 13000;
	vitesseMax = 175;
	vitesseMoyenne = 87;
	regimeMax = 56;
	regimeMoyen = 28;
	consoMax = 92;
	consoMoyenne = 67;
	consommation = 62;
	vitesse = 129;
	regime = 23;
	latitude = 23.23567;
	longitude = 1.12345;
	dateHTR.tm_year = 2018;
	dateHTR.tm_mday = 6;
	dateHTR.tm_mon = 4;
	dateHTR.tm_hour = 13;
	dateHTR.tm_min = 43;
	dateHTR.tm_sec = 10;
}

void DonneesTR::initTestDEGRADE() {
	// NORMAL : TM  K1  K2    K3  CD  CD  VM  VY  RM  RY  CM  CY
	// msg    : 2:2 1:1 30:1e 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0
	// d1 = 0002 0010
	// 2a = 0x02 + 0x0A
	// K  = 01 30 00
	OBD2Actif = false;
	bluetoothActif = false;
	nbDefauts = 0;
	defauts[0] = 0;
	defauts[1] = 0;
	defauts[2] = 0;
	defauts[3] = 0;
	distanceParcourue = 13000;
	vitesseMax = 0;
	vitesseMoyenne = 0;
	regimeMax = 0;
	regimeMoyen = 0;
	consoMax = 0;
	consoMoyenne = 0;
	consommation = 0;
	vitesse = 0;
	regime = 0;
	latitude = 0;
	longitude = 0;
	dateHTR.tm_year = 2018;
	dateHTR.tm_mday = 6;
	dateHTR.tm_mon = 4;
	dateHTR.tm_hour = 13;
	dateHTR.tm_min = 43;
	dateHTR.tm_sec = 10;
}

void DonneesTR::initTestDMD_GPS() {
	// NORMAL : TM     K1   K2    K3    CD   CD  VM     VY    RM    RY    CM    CY
	// msg    : 211:C3 12:c 34:22 56:38 42:0 0:0 175:af 87:57 56:38 28:1c 92:5c 67:43
	OBD2Actif = true;
	bluetoothActif = true;
	nbDefauts = 0;
	defauts[0] = 0;
	defauts[1] = 0;
	defauts[2] = 0;
	defauts[3] = 0;
	distanceParcourue = 123456;
	vitesseMax = 0;
	vitesseMoyenne = 0;
	regimeMax = 0;
	regimeMoyen = 0;
	consoMax = 0;
	consoMoyenne = 0;
	consommation = 0;
	vitesse = 0;
	regime = 0;
	latitude = 43.615982;
	longitude = 1.309508;
	dateHTR.tm_year = 2018;
	dateHTR.tm_mday = 6;
	dateHTR.tm_mon = 4;
	dateHTR.tm_hour = 13;
	dateHTR.tm_min = 43;
	dateHTR.tm_sec = 10;
}

void DonneesTR::initTestGPS1() {
	// NORMAL : TM K1 K2 K3 L1 L2 L3 L4 G1 G2 G3 G4
	// msg    : D4 01 1E 00 2b 3d 3b 52 01 1e 5f 08
	OBD2Actif = true;
	bluetoothActif = true;
	nbDefauts = 2;
	defauts[0] = 0x02;
	defauts[1] = 0x0A;
	defauts[2] = 0;
	defauts[3] = 0;
	distanceParcourue = 13000;
	vitesseMax = 0;
	vitesseMoyenne = 0;
	regimeMax = 0;
	regimeMoyen = 0;
	consoMax = 0;
	consoMoyenne = 0;
	consommation = 0;
	vitesse = 0;
	regime = 0;
	latitude = 43.615982;
	longitude = 1.309508;
	dateHTR.tm_year = 2018;
	dateHTR.tm_mday = 6;
	dateHTR.tm_mon = 4;
	dateHTR.tm_hour = 13;
	dateHTR.tm_min = 43;
	dateHTR.tm_sec = 10;
}

void DonneesTR::initTestGPS2() {
	// NORMAL : TM K1 K2 K3 L1 L2 L3 L4 G1 G2 G3 G4
	// msg    : D4 0c 22 38 2b 3d 3b 59 01 1e 5f 08
	OBD2Actif = true;
	bluetoothActif = true;
	nbDefauts = 2;
	defauts[0] = 0x02;
	defauts[1] = 0x0A;
	defauts[2] = 0;
	defauts[3] = 0;
	distanceParcourue = 123456;
	vitesseMax = 0;
	vitesseMoyenne = 0;
	regimeMax = 0;
	regimeMoyen = 0;
	consoMax = 0;
	consoMoyenne = 0;
	consommation = 0;
	vitesse = 0;
	regime = 0;
	latitude = -43.615988;
	longitude = -01.309508;
	dateHTR.tm_year = 2018;
	dateHTR.tm_mday = 6;
	dateHTR.tm_mon = 4;
	dateHTR.tm_hour = 13;
	dateHTR.tm_min = 43;
	dateHTR.tm_sec = 10;
}

void DonneesTR::initTestINIT() {
	// NORMAL : TM  K1  K2    K3  CD  CD  VM  VY  RM  RY  CM  CY
	// msg    : 7:7 1:1 30:1e 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0
	// d1 = 0000 0110
	OBD2Actif = false;
	bluetoothActif = false;
	nbDefauts = 0;
	defauts[0] = 0;
	defauts[1] = 0;
	defauts[2] = 0;
	defauts[3] = 0;
	distanceParcourue = 15000;
	vitesseMax = 0;
	vitesseMoyenne = 0;
	regimeMax = 0;
	regimeMoyen = 0;
	consoMax = 0;
	consoMoyenne = 0;
	consommation = 0;
	vitesse = 0;
	regime = 0;
	latitude = 0;
	longitude = 0;
}

void DonneesTR::initTestDORMIR() {
	// NORMAL : TM  K1  K2    K3  CD  CD  VM  VY  RM  RY  CM  CY
	// msg    : 7:C7 1:1 30:1e 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0
	// d1 = 1100 0111
	OBD2Actif = true;
	bluetoothActif = true;
	nbDefauts = 0;
	defauts[0] = 0;
	defauts[1] = 0;
	defauts[2] = 0;
	defauts[3] = 0;
	distanceParcourue = 13000;
	vitesseMax = 0;
	vitesseMoyenne = 0;
	regimeMax = 0;
	regimeMoyen = 0;
	consoMax = 0;
	consoMoyenne = 0;
	consommation = 0;
	vitesse = 0;
	regime = 0;
	latitude = 0;
	longitude = 0;
}
