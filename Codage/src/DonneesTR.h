#ifndef DONNEES_H
#define DONNEES_H

#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <time.h>

class DonneesTR {
public:
	DonneesTR();
	static DonneesTR* getInstance();
	virtual ~DonneesTR();
	void razStat();
	float getConsommation();
	int getConsoMoyenne();
	int getConsoMax();
	int getVitesseMoyenne();
	int getVitesseMax();
	int getVitesse();
	int getRegime();
	int getRegimeMoyen();
	int getRegimeMax();
	int getNbDefaut();
	int getDefauts(int numero);
	void setDefaut(int numero, int defauts);
	void setVitesse(int vitesse);
	void setConsommation(float consommation);
	void setRegime(int regime);

	float getBatterie();
	void setBatterie(float tensionBatterie);

	float getDistanceParcourue();
	void majDistance();
	void majDistance(bool messageEnvoye);
	//void majData(OBD2 obd2);
	float getLatitude();
	float getLongitude();
	struct tm setDatation(struct tm dateGPS);
	struct tm getDatation();

	void setLatitude(float latitude);
	void setLongitude(float longitude);

	bool getBluetoothActif();
	void setBluetoothActif(bool activeOrNot);
	bool getOBD2Actif();
	void setOBD2Actif(bool activeOrNot);
	//Methode pour test unitaire Classe Message
	void initTestNORMAL();
	void initTestDEGRADE();
	void initTestDMD_GPS();
	void initTestGPS1();
	void initTestGPS2();
	void initTestDORMIR();
	void initTestINIT();

	// pas de getDefaut ou de getNbDefaut ni de set
private:
	static DonneesTR* DonneesTRInstance;
	float distanceParcourue;
	int nbDefauts;
	int defauts[4];
	float consommation;
	float consoMoyenne;
	float consoMax;
	int vitesse;
	int vitesseMoyenne;
	int vitesseMax;
	int regime;
	int regimeMoyen;
	int regimeMax;
	float latitude;
	float longitude;
	tm dateHTR;

	float batterie;

	int moyenneRegime = 0;  //nb total de valeurs
	long valeurMoyenneRegime = 0;
	int moyenneVitesse = 0; //nb total de valeurs
	long valeurMoyenneVitesse = 0;
	int moyenneConso = 0;   //nb total de valeurs

	bool bluetoothActif;bool OBD2Actif;
	;
};

#endif /* DONNEES_H */
