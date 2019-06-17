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
	C_BATTERIE,
	C_SONDE2,
	C_SONDE3,
	C_SONDE4,
	C_SONDE5,
	C_SONDE6,
	C_SONDE7,
	C_SONDE8,



} TCode;

class OBD2 {

private:

	Bluetooth* moduleBT;
	Uart* liaisonBT;
	String code[18] = { "010D", "015F", "010C", "CODE_DEFAUT_NONDEF", "ATI",
			"010B", "010F", "0144", "0110", "0114", "AT RV", "0115", "0116",
			"0117", "0118", "0119", "011A", "011B"};

	//différent PID sonde lambda

	//différent PID ratio en relation avec la sonde lambda
	//"0134", "0135", "0136", "0137", "0138", "0139", "013A", "013B",
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
	float lireRatio1();
	float lireRatio2();
	float lireRatio3();
	float lireRatio4();
	float lireRatio5();
	float lireRatio6();
	float lireRatio7();
	float lireRatio8();
	float lireDair();
	float lireSonde();
	float lireSonde1();
	float lireSonde2();
	float lireSonde3();
	float lireSonde4();
	float lireSonde5();
	float lireSonde6();
	float lireSonde7();
	float lireSonde8();
	float lireSonde9();
	float lireSonde10();
	float lireSonde11();
	float lireSonde12();
	float lireSonde13();
	float lireSonde14();
	float lireSonde15();
	float lireSonde16();
	float lireBatterie();
	String lireReponse();
	bool testerConnexion();
};

#endif
