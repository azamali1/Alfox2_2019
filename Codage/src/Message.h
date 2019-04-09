/*/======================/*/
/*/File: MessageSigfox.h /*/
/*/create: 21 mars 2019  /*/
/*/======================/*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <Arduino.h>
#include "DonneesTR.h"
#include "Global.h"

typedef unsigned char byte;

class Message {

public:
    static Etat decoderEtat(byte* msg);
    byte* nouveau(Etat etat, DonneesTR* data, byte* b);

private:
    byte* normal(DonneesTR* data, byte* b);
    byte* degrade(DonneesTR* data, byte* b);
    byte* dmdGPS(DonneesTR* data, byte* b);
    byte* gps(DonneesTR* data, byte* b);
    byte* dormir(DonneesTR* data, byte* b);
    byte* init(DonneesTR* data, byte* b);

};
#endif /* MESSAGE_H */
