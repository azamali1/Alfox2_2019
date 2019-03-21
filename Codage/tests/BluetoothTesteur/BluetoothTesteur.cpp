#include "../../src/Bluetooth.h"


Bluetooth* bluetooth;
char c = ' ';
boolean NL = true;

void setup() {
  Serial.begin(9600);
  delay(5000);
  bluetooth = new Bluetooth(PINALIM, PINEN);
  Serial.println("Test de la classe Bluetooth");
  //bluetooth->connexion("2017,11,7030A"); // OBD2 bleu
  //bluetooth->connexion("780C,B8,46F54"); // PC Commenge simulateur
   bluetooth->connexion("E84E,84,CCF54A"); //Portable ZAMALI
   bluetooth->connexion(""); //Portable LOPEZ
  //bluetooth->connexion("001A,7D,DA7117"); //Dongle 4.0
  delay(2000);
  Serial.println(bluetooth->isActif());

}

void loop()
{
    if (bluetooth->getLiaisonBT()->available())
    {
      c = bluetooth->getLiaisonBT()->read();
      Serial.write(c);
    }

    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
      c = Serial.read();
      bluetooth->getLiaisonBT()->write(c);
      if (NL) { Serial.print("\r\n>");  NL = false; }
      Serial.write(c);
      if (c==10)
      {
        NL = true;
      }
  }
}

void SERCOM3_Handler()
{
  bluetooth->getLiaisonBT()->IrqHandler();
}
