#include "/home/snir2g2/Bureau/Alfox2_2019/Codage/src/GPS.h"
#include "/home/snir2g2/Bureau/Alfox2_2019/Codage/src/DonneesTR.h"
#include "/home/snir2g2/Bureau/Alfox2_2019/Codage/src/Bluetooth.h"
#include "/home/snir2g2/Bureau/Alfox2_2019/Codage/src/CarteSD.h"
#include "/home/snir2g2/Bureau/Alfox2_2019/Codage/src/OBD2.h"
#include "/home/snir2g2/Bureau/Alfox2_2019/Codage/src/LedTri.h"
#include "/home/snir2g2/Bureau/Alfox2_2019/Codage/src/Global.h"

#define T_ECH 5000 //en millisecondes
#define T_MSG_STND 720000 //12 minutes en ms
#define T_MSG_ECO 3600000 //1h en ms
#define T_MSG_GPS 720000
#define T_MSG_MAINTENANCE 720000
#define T_MSG_DORMIR 3600000

Etat etat;

unsigned long dureeCumulee;
unsigned long heureDebut;
unsigned long heureFin;
unsigned long baseTimeLoop = T_ECH;
unsigned long tempoMessage;

bool chgtModeSrv;

//Message* message = new Message();  //Classe message non codée
Bluetooth* bluetooth = Bluetooth::getInstance(PINALIM, PINEN);
OBD2* obd2 = OBD2::getInstance(bluetooth);
LedTri* led = LedTri::getInstance(255, 255, 255);
GPS* gps = GPS::getInstance();
DonneesTR* donneesTR = new DonneesTR();
CarteSD* sd = CarteSD::getInstance();

void majDataTR();
void dormirLoop();
void nouvelEtat(Etat e);
void traiterEvenement(Event ev);
void traiterEtat(ModeG mode);

void majDataTR() {

	donneesTR->setVitesse(obd2->lireVitesse());
	delay(250);
	donneesTR->setRegime(obd2->lireRegimeMoteur());
	delay(250);
	donneesTR->setConsommation(obd2->lireConsomation());
	delay(250);
	/* obd2->demande(C_DEFAUT);
	 int defauts = obd2->lire();
	 if (defauts) {
	 nbDefauts = nbDefauts + 1;
	 donneesTR.setDefauts(defauts);
	 }*/
}

void dormirLoop() {
	baseTimeLoop = baseTimeLoop - (heureFin - heureDebut);
	delay(baseTimeLoop);
}

void nouvelEtat(Etat e) {

	if (e != etat) {
		traiterEtat(EXIT);
		// on doit toujours revenir à un état de suivi normal
		if (e == STANDARD) {
			if (obd2->isConnected()== true) {
				etat = NORMAL;
			} else {
				etat = DEGRADE;
			}
		} else
			etat = e;
		traiterEtat(ENTRY);
		traiterEtat(DO);
		chgtModeSrv = false;
	}
}

void traiterEvenement(Event ev) {

	switch (etat) {
	case INIT:
		nouvelEtat(INIT);
		break;
	case NORMAL:
		switch (ev) {
		case MODE_DMD_GPS:
			nouvelEtat(DMD_GPS);
			break;
		case MODE_GPS:
			nouvelEtat(GPS_SEUL);
			break;
		case BLUETOOTH_OFF:
			nouvelEtat(DEGRADE);
			break;
		case MODE_DORMIR:
			nouvelEtat(DORMIR);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		}
		break;
	case DEGRADE:
		switch (ev) {
		case MODE_DMD_GPS:
			nouvelEtat(DMD_GPS);
			break;
		case MODE_GPS:
			nouvelEtat(GPS_SEUL);
			break;
		case BLUETOOTH_ON:
			nouvelEtat(NORMAL);
			break;

		case MODE_DORMIR:
			nouvelEtat(DORMIR);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		}
		break;
	case DMD_GPS:
		nouvelEtat(DMD_GPS);
		break;
	case GPS_SEUL:
		switch (ev) {
		case MODE_STANDARD:
			nouvelEtat(STANDARD);
			break;
		case MODE_DORMIR:
			nouvelEtat(DORMIR);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		}
		break;
	case DORMIR:
		switch (ev) {
		case MODE_STANDARD:
			nouvelEtat(STANDARD);
			break;
		case MODE_MAINTENANCE:
			nouvelEtat(MAINTENANCE);
			break;
		}
		break;
	case MAINTENANCE:
		switch (ev) {
		case MODE_INIT:
			nouvelEtat(INIT);
			break;
		case MODE_STANDARD:
			nouvelEtat(STANDARD);
			break;
		}
		break;
	}

}

void traiterEtat(ModeG mode) {
	switch (etat) {
	case INIT:
		switch (mode) {
		case ENTRY:
			break;
		case DO:
			Serial.println("Initialisation");
			nouvelEtat(STANDARD);
			break;
		case EXIT:
			break;
		}
		break;
	case NORMAL:
		switch (mode) {
		case ENTRY:
			if (chgtModeSrv) {
				dureeCumulee = 0;
			}
			baseTimeLoop = T_ECH;
			tempoMessage = T_MSG_STND;
			break;
		case DO:
			if ((dureeCumulee % tempoMessage) == 0) {
				Serial.println("Envoi d'un message NORMAL");
				// sigfox.envoyer(Message.normal(
				//   connexionOBD2,
				// 0,
				//dpVoiture.getCodeDefauts(),
				//(int)dpVoiture.getCompteur(),
				//dpVoiture.getConsoMoyenne(),
				//dpVoiture.getVitesseMoyenne(),
				//dpVoiture.getRegimeMoyen())
				//  );
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DEGRADE:
		switch (mode) {
		case ENTRY:
			if (chgtModeSrv) {
				dureeCumulee = 0;
			}
			baseTimeLoop = T_ECH;
			tempoMessage = T_MSG_STND;
			break;
		case DO:
			if ((dureeCumulee % tempoMessage) == 0) {
				Serial.println("Envoi d'un message DEGRADE");
				//sigfox.envoyer(Message.degrade(connexionOBD2));
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DMD_GPS:
		switch (mode) {
		case ENTRY:
			dureeCumulee = 0;
			break;
		case DO:
			Serial.println("Envoi d'un message DMD_GPS");
			//sigfox.envoyer(Message.gps(gps));
			chgtModeSrv = false;
			nouvelEtat(STANDARD);
			break;
		case EXIT:
			break;
		}
		break;
	case GPS_SEUL:
		switch (mode) {
		case ENTRY:
			dureeCumulee = 0;
			baseTimeLoop = T_ECH;
			tempoMessage = T_MSG_GPS;
			break;
		case DO:
			if ((dureeCumulee % tempoMessage) == 0) {
				Serial.println("Envoi d'un message GPS");
				//sigfox.envoyer(Message.gps(gps));
			}
			break;
		case EXIT:
			break;
		}
		break;
	case DORMIR:
		switch (mode) {
		case ENTRY:
			Serial.println("Envoi d'un message DORMIR");
			//sigfox.envoyer(Message.eco(connexionOBD2));
			baseTimeLoop = T_ECH;
			tempoMessage = T_MSG_DORMIR;
			break;
		case DO:
			break;
		}
		break;
	case MAINTENANCE:
		switch (mode) {
		case ENTRY:
			// afficher un id sur la console
			baseTimeLoop = T_ECH;
			tempoMessage = T_MSG_MAINTENANCE;
			Serial.println("Envoi d'un message MAINTENANCE");
			break;
		case DO:
			break;
		case EXIT:
			break;
		}
		break;
	case ECO:
		switch (mode) {
		case ENTRY:
			baseTimeLoop = T_ECH;
			tempoMessage = T_MSG_ECO;
			break;
		case DO:
			break;
		case EXIT:
			break;
		}
	}
}

void setup() {
	Serial.begin(9600);
	//Serial.println(VERSION);
}

void loop() {
	//variables

	//debut

	// millis retourne un entier contenant le nombre de millisecondes depuis le démarrage du programme
	heureDebut = millis();

	// ---------- TRAITEMENTS SYSTEMATIQUES -------------

	// le GPS, on récupère l'heure et la position
	if (gps->isDispo()) {

		gps->maj();
		donneesTR->setLatitude(gps->getLatitude());
		donneesTR->setLongitude(gps->getLongitude());
	}

	// Horloge Temps Réel  //////// Sprint 4

	//donneesTR->setDateHTR(htr.getDate());

	// LED
	led->setCouleur(rouge, 255/*couleurEtatCrt*/);

	// ---------------------------------------------------
	// ------------- TRAITEMENTS EVENEMENTS -------------

	// réception d’un message Sigfox de changement d’état
	/*	if (message->msgPresent()) {                                            //////////// Classe Message non codée ///////////
	 String msg = message->lire();
	 nouvelEtat = message->decoderEtat(msg);
	 nouvelEvent(nouvelEtat);
	 }

	 */

	// Surveillance du Bluetooth
	if (BLUETOOTH_ON) {
		if (etat == DEGRADE) {
			traiterEvenement(BLUETOOTH_ON);
		} else if (etat == NORMAL)
			traiterEvenement(BLUETOOTH_OFF);
	}

	// Surveillance de la voie série
	/*	int donneesAlire = Serial.available();//lecture du nombre de caractères disponibles dans le buffer
	 if (donneesAlire > 0) {                    //si le serial a reçu un caractère // si le buffer n'est pas vide
	 String car = Serial.read(donneesAlire);//lecture du caractère reçu
	 //while(Serial.read(donneesAlire) != -1);  Permet de lire et vider tout le buffer; à voir si à utiliser?

	 if (car == "#") {
	 traiterEvenement(MODE_MAINTENANCE);
	 }
	 }*/

	// ---------------------------------------------------
	// -------------- TRAITEMENTS COURANTS ---------------
	traiterEtat(DO);

	// ------- Cycle de traitement -----------------------

	// on le traite en une seule fois (c’est suspensif)
	// durée approximative 3x50ms (A vérifier)
	// les setter de donnéesTR font les calculs de moyennes, max et km
	// acqDonneesVehicule
	// debut

	// Procédures appelées dans le traitement DO de la MAE
	//traitement12mn
	//debut

	//message->envoyer(message->codage(etat, donneesTR));  //Classe Message non codée
	sd->ecrire(donneesTR);
	majDataTR();
	heureFin = millis();

	dormirLoop();
	//fin
}

