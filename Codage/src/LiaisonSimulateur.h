#ifndef __LIAISONSIMULATEUR__
#define __LIAISONSIMULATEUR__

#include <Arduino.h>
#include "wiring_private.h"
#define PINALIM 0
#define PINEN 1

class LiaisonSimulateur {

  private :
    Uart* serialBT;
    int modeMaster();
    int modeConnexion();
    int motDePasse();
    int initialisation();
    int appairage(String adresse);
    int bind(String adresse);
    int modeDeconnecte();
    int lien(String adresse);
    int reinitialiser();
    int pinAlim;
    int pinEn;
    String adresseOBD2;
    static LiaisonSimulateur* liaisonSimulateurInstance;
    LiaisonSimulateur(int pinAlim, int pinEn);
    
  
  public:
    static LiaisonSimulateur* getInstance(int pinAlim, int pinEn);
    int connexion(String adresse);
    bool isActif();
    Uart* getLiaisonBT();
};

#endif
