/*/=======================/*/
/*/ File: SigfoxArduino.h /*/
/*/ create: 4 Avril 2019  /*/
/*/=======================/*/

#include <Arduino.h>

class SigfoxArduino
{	private:
	//int nbMsgRemisParHeure = 0;
	//int nbMaxParHeure = 5;
	//long tempoGlissant = 60000;
	static SigfoxArduino* SigArduinoInstance;
	SigfoxArduino();

public:
	static SigfoxArduino* getInstance();
	bool envoyer(byte* bMsg);
	bool sendMessageAndGetResponse(byte* bMsg, byte* rMsg);
	bool isMsgRecu(byte* bMsg);
	//String lire();
	//int getNbMsgEmisParH();
	//void setNbMsgEmisParH(int nbMsgRemisParHeure);

};
