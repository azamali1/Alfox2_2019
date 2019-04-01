/*/=======================/*/
/*/File: Message_Test.cpp /*/
/*/create: 21 mars 2019   /*/
/*/=======================/*/

#include "../../src/Message.h"
#include "../../src/DonneesTR.h"

byte bMsg[12];

void afficherMsg(byte* buf, int size) {
	Serial.print( "Obtenu  : ");
    for (int i = 0; i < size; i++) {
    	Serial.print(buf [i]);
    }
    Serial.println();
}

void testMsgUpload(Etat etat, DonneesTR* data, Message* unMessage) {
    data->razStat();
    data->initTestNORMAL();
    unMessage->nouveau(NORMAL, data, bMsg);
    Serial.println("NORMAL  : 209:d1 1:1 30:1e 0:0 42:2a 0:0 175:af 87:57 56:38 28:1c 92:5c 67:43");
    afficherMsg(bMsg, 12);
    Serial.println();

    data->razStat();
    data->initTestDEGRADE();
    unMessage->nouveau(DEGRADE, data, bMsg);
    Serial.println( "DEGRADE : 2:2 1:1 30:1e 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0");
    afficherMsg(bMsg, 12);
    Serial.println();

    data->razStat();
    data->initTestDMD_GPS();
    unMessage->nouveau(DMD_GPS, data, bMsg);
    Serial.println( "DMD_GPS : 195:C3 12:c 34:22 56:38 43:2b 61:3d 59:3b 88:58 1:1 30:1e 95:5f 8:8");
    afficherMsg(bMsg, 12);
    Serial.println();

    data->razStat();
    data->initTestGPS1();
    unMessage->nouveau(GPS, data, bMsg);
    Serial.println( "GPS     : 212:D4 1:1 30:1e 0:0 43:2b 61:3d 59:3b 82:52 1:1 30:1e 95:5f 8:8");
    afficherMsg(bMsg, 12);
    Serial.println();

    data->razStat();
    data->initTestGPS2();
    unMessage->nouveau(GPS, data, bMsg);
    Serial.println( "GPS     : 212:D4 12:c 34:22 56:38 43:2b 61:3d 59:3b 89:59 1:1 30:1e 95:5f 9:9");
    afficherMsg(bMsg, 12);
    Serial.println();

    data->razStat();
    data->initTestDORMIR();
    unMessage->nouveau(DORMIR, data, bMsg);
    Serial.println( "DORMIR  : 199:C7 1:1 30:1e 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0");
    afficherMsg(bMsg, 12);
    Serial.println();

    data->razStat();
    data->initTestINIT();
    unMessage->nouveau(INIT, data, bMsg);
    //cout << "Test debug" << endl;
    Serial.println( "INIT    : 6:6 1:1 30:1e 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0");
    afficherMsg(bMsg, 12);
    Serial.println();
    Serial.println( "Test terminé !!!");
}

void testMsgDownload(Message* unMessage) {
    int valEtat = NORMAL;
    for (int i = 0; i < 12; i++)
        bMsg[i] = 0;
    bMsg[0] = 0x30; // Code de changement d'état
    bMsg[1] = valEtat;
    Etat nvEtat = unMessage->decoderEtat(bMsg);
    Serial.print ( "Décodage Etat : NORMAL > ");
    Serial.println( ((nvEtat == valEtat) ? "OK" : "BUG"));

    valEtat = DEGRADE;
    for (int i = 0; i < 12; i++)
        bMsg[i] = 0;
    bMsg[0] = 0x30; // Code de changement d'état
    bMsg[1] = valEtat;
    nvEtat = unMessage->decoderEtat(bMsg);
    Serial.print( "Décodage Etat : DEGRADE > ");
    Serial.println((nvEtat == valEtat) ? "OK" : "BUG");

    valEtat = GPS;
    for (int i = 0; i < 12; i++)
        bMsg[i] = 0;
    bMsg[0] = 0x30; // Code de changement d'état
    bMsg[1] = valEtat;
    nvEtat = unMessage->decoderEtat(bMsg);
    Serial.print( "Décodage Etat : GPS > ");
    Serial.println( ((nvEtat == valEtat) ? "OK" : "BUG"));
}

void setup() {
	Message* unMessage = new Message();
	DonneesTR* mesDonnees = new DonneesTR();
	delay(10000);
	afficherMsg(bMsg,12);
	testMsgDownload(unMessage);
	testMsgUpload(NORMAL,mesDonnees,unMessage);
}

void loop() {

}
