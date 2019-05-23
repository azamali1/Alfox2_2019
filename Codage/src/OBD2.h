#ifndef __OBD2__
#define __OBD2__

#include <Arduino.h>
#include "Bluetooth.h"
#include "LiaisonSimulateur.h"

//#define SIMU

#ifdef SIMU
//Communication avec le simulateur OBDSim
#define DEBUT_POIDS_FORT 8
#define FIN_POIDS_FORT 10
#define DEBUT_POIDS_FAIBLE 11
#define FIN_POIDS_FAIBLE 13

#else

//Communication avec OBD2 réel (Konwei)
#define DEBUT_POIDS_FORT 6
#define FIN_POIDS_FORT 8
#define DEBUT_POIDS_FAIBLE 9
#define FIN_POIDS_FAIBLE 11

#endif

typedef enum {
	C_VITESSE,
	C_CONSOMMATION,
	C_REGIME,
	C_DEFAUT,
	C_VERSION,
	C_PRESSION,
	C_TEMPERATURE,
	C_RATIO,
	C_DAIR,
	C_SONDE,
	C_BATTERIE
} TCode;

class OBD2 {

private:

	Bluetooth* moduleBT;
	Uart* liaisonBT;
	String code[11] = { "010D", "015F", "010C", "CODE_DEFAUT_NONDEF", "ATI",
			"010B", "010F", "0144", "0110","0114" ,"AT RV" };
	static OBD2* OBD2Instance;
	OBD2(Bluetooth* bt);
	OBD2(LiaisonSimulateur* liaison);bool connected;
	int testReponse(TCode code);

public:
	/** Constructeur **/
	static OBD2* getInstance(Bluetooth* bt);
	static OBD2* getInstance(LiaisonSimulateur* liaison);
	void setIsConnected(bool etat);bool isConnected();
	String demande(TCode numCode);
	float lireConsomation();
	int calculConsommation();
	int lireRegimeMoteur();
	int lireVitesse();
	float lirePression();
	float lireTemprerature();
	float lireRatio();
	float lireDair();
	float lireSonde();
	float lireBatterie();
	String lireReponse();
};

#endif
