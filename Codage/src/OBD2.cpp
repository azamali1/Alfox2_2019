#include "OBD2.h"
//-----------------------------------------------------
//-- Convertisseur de l'Hexa en entier sur 16 bits-----
//-----------------------------------------------------
uint16_t hex2uint16(const char *p) {
	char c = *p;
	uint16_t i = 0;
	//On balaye les 4 caractères de la chaîne, chacun correspondant à un digit de la valeur hexa finale
	for (uint8_t n = 0; c && n < 4; c = *(++p)) {
		if (c >= 'A' && c <= 'F') { //si c est une des lettres d'un nombre hexa
			c -= 7; //c contient un code ASCII correspondant à une valeur hexa comprise entre 3A et 3F. Plus tard on gardera uniquement 0xA à 0xF
		} else if (c >= 'a' && c <= 'f') {
			c -= 39; //c vaut aussi une valeur hexa comprise entre 3A et 3F, plus tard on gardera uniquement 0xA à 0xF
		} else if (c == ' ' && n == 2) {
			continue;
		} else if (c < '0' || c > '9') { //si c n'est ni une lettre entre A et F ni un chifre, on quitte le test
			break;
		}
		//Après avoir passé ces différents tests, c a été modifié ou c est le code ASCII d'un chiffre donc 0x30 < c < 0x39
		i = (i << 4) | (c & 0xF); //on décale i de 4 bits (un digit) et on "ajoute" la valeur hexa des 4 bits de poids faibles de c à savoir une valeur hexa comprise entre 0 et F
		n++; // on passe au digit suivant
	}
	return i;
}

//-----------------------------------------------------
//-- Convertisseur de l'Hexa en entier sur 8 bits------
//-----------------------------------------------------
byte hex2uint8(const char *p) {
	byte c1 = *p;
	byte c2 = *(p + 1);
	if (c1 >= 'A' && c1 <= 'F')
		c1 -= 7;
	else if (c1 >= 'a' && c1 <= 'f')
		c1 -= 39;
	else if (c1 < '0' || c1 > '9')
		return 0;

	if (c2 == 0)
		return (c1 & 0xf);
	else if (c2 >= 'A' && c2 <= 'F')
		c2 -= 7;
	else if (c2 >= 'a' && c2 <= 'f')
		c2 -= 39;
	else if (c2 < '0' || c2 > '9')
		return 0;

	return c1 << 4 | (c2 & 0xf);
}

//-----------------------------------------------------
//------- Constructeur en singleton -------------------
//-----------------------------------------------------
OBD2* OBD2::OBD2Instance = 0;

OBD2* OBD2::getInstance(Bluetooth* bt) {

	if (OBD2Instance == 0) {
		OBD2Instance = new OBD2(bt);
	}
	return OBD2Instance;
}

OBD2* OBD2::getInstance(LiaisonSimulateur* liaison) {

	if (OBD2Instance == 0) {
		OBD2Instance = new OBD2(liaison);
	}
	return OBD2Instance;
}

OBD2::OBD2(Bluetooth* bt) {

	this->moduleBT = bt;
	liaisonBT = moduleBT->getLiaisonBT();
	liaisonBT->flush();
	/*liaisonBT->println("AT S0");
	 Serial.println(lireReponse());
	 liaisonBT->println("AT");
	 Serial.println(lireReponse());
	 liaisonBT->println("AT H0");
	 Serial.println(lireReponse());
	 liaisonBT->println("AT R0");
	 Serial.println(lireReponse());*/
	//ATE0: Desactive(0) ou non l’echo (si activÃ©, l’ELM renvoie alors les caractÃ¨res reÃ§u pour verif eventuelle)
	liaisonBT->println("AT E0");
	Serial.println(lireReponse());
	//ATSP0: Permet de parametrer le protocole Ã utiliser (0=mode auto)
	liaisonBT->println("AT SP0");
	Serial.println(lireReponse());
	String reponse = demande(C_VERSION);
	Serial.println(reponse);
	//Si le contact est coupé ou la liaison bluetooth est coupé, on précise qu'on est pas connecté
	if ((reponse.substring(0, 17) == "UNABLE TO CONNECT")
			|| (reponse.substring(0, 9) == "ERROR:(0)")) {
		this->connected = false;
		Serial.println("Pas connecté");
	} else {
		this->connected = true;
		Serial.println("connecté");

	}
	Serial.println("Est connecté ? ");
	Serial.println(this->isConnected());
}

String OBD2::demande(TCode numCode) {
	liaisonBT->println(code[numCode]);
	String a = lireReponse();
	return a/*.toInt()*/;
}

String OBD2::lireReponse() {
	String reponse = "";
	delay(100);
	while (liaisonBT->available() <= 0)
		;
	reponse = liaisonBT->readStringUntil('>');
	return reponse;
}

int OBD2::testReponse(TCode code) {

	String reponse = demande(code);

	//Si les donnees ne sont pas au bon format, pas de donnée, on renvoie -1
	if (reponse.substring(0, 7) == "NO DATA") {
		return -1;
	}

	//Si le contact est coupé, la connexion est impossible, on renvoie -2
	if (reponse.substring(0, 17) == "UNABLE TO CONNECT") {
		this->connected = false;
		return -2;
	}
	//Si la connexion bluetooth est perdue on renvoie -3
	if (reponse.substring(0, 9) == "ERROR:(0)") {
		this->connected = false;
		return -3;
	}
	return hex2uint8(
			reponse.substring(DEBUT_POIDS_FORT, FIN_POIDS_FORT).c_str());
}

int OBD2::lireVitesse() {
	//Vitesse est en km/h
	return testReponse(C_VITESSE);
}

int OBD2::lireRegimeMoteur() {
	String reponse = demande(C_REGIME);

	//Si le moteur n'est pas démarré on renvoie -1
	if (reponse.substring(0, 7) == "NO DATA") {
		return -1;
	}
	//Si le contact est coupé, la connexion est impossible, on renvoie -2
	if (reponse.substring(0, 17) == "UNABLE TO CONNECT") {
		this->connected = false;
		return -2;
	}
	//Si la connexion bluetooth est perdue on renvoie -3
	if (reponse.substring(0, 9) == "ERROR:(0)") {
		this->connected = false;
		return -3;
	}
	String trame = "";
	trame = reponse.substring(DEBUT_POIDS_FORT, FIN_POIDS_FORT);
	trame += reponse.substring(DEBUT_POIDS_FAIBLE, FIN_POIDS_FAIBLE);

	return hex2uint16(trame.c_str()) / 4;
}

float OBD2::lireConsomation() {
	//Consommation est en L/100
	float conso = 0;
	float vitesse = (float) this->lireVitesse();
	//float pression = this->lirePression();
	//float regime = (float)this->lireRegimeMoteur();
	//float temperature = this->lireTemprerature();
	//float ratio = this->lireRatio();
	float dair = this->lireDair();
	float sonde = this->lireSonde();
	/*if(ratio == -1){
	 ratio = 18;
	 }*/
	if (vitesse == 0) {
		conso = 0;
	} else {
		//Calcul de la consommation que vous pouvez retrouver dans la documentation "Consommation OBD2"
		conso = ((360000 / 845) * (dair / (-1.045 * sonde + 15.222))
				* (1 / vitesse));
		//conso = ((6000 / vitesse)* (0.0027* ((pression * regime) / ((temperature + 273.15) * ratio))));
	}

	return conso;
}

float OBD2::lirePression() {
	//Pression est en kPa
	return testReponse(C_PRESSION);

}

float OBD2::lireTemprerature() {
	//Température est en °C
	return testReponse(C_TEMPERATURE);
}

float OBD2::lireRatio() {
	//Ratio = rapport air/carburant
	return testReponse(C_RATIO) * (2 / 65536);
}

float OBD2::lireDair() {
	//Dair = débit d'air en g/s
	int debitAir = testReponse(C_DAIR);
	if (debitAir == -1) {
		return -1;
	} else if (debitAir == -2) {
		return -2;
	} else if (debitAir == -3) {
		return -3;
	} else {
		return debitAir / 100;
	}
}

float OBD2::lireSonde() {
	//Température est en °C
	return testReponse(C_SONDE);
}

void OBD2::setIsConnected(bool etat) {
	this->connected = etat;
}

bool OBD2::isConnected() {


	return this->connected;

}

float OBD2::lireBatterie() {
	//Pression est en kPa
	return testReponse(C_BATTERIE);

}
