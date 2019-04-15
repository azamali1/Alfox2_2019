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
	void nouveau(Etat etat, DonneesTR* data, byte* b);

private:
	void normal(DonneesTR* data, byte* b);
	void degrade(DonneesTR* data, byte* b);
	void dmdGPS(DonneesTR* data, byte* b);
	void gps(DonneesTR* data, byte* b);
	void dormir(DonneesTR* data, byte* b);
	void init(DonneesTR* data, byte* b);

};
#endif /* MESSAGE_H */
