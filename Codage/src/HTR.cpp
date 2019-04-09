#include "HTR.h"

HTR* HTR::htrInstance = 0;
HTR::HTR() {

}

struct tm HTR::setDatation(struct tm gpsDatation) {
	this->datation = gpsDatation;
	return datation;
}

struct tm HTR::getDatation() {
	return datation;
}

struct tm HTR::majDatation(unsigned int dureeMesuree) {

	//this->datation.tm_sec +=dureeMesuree/1000;
	Serial.print(datation.tm_mday);
	Serial.print("/");
	Serial.print(datation.tm_mon);
	Serial.print("/");
	Serial.print(datation.tm_year);
	Serial.print(" ");
	Serial.print(datation.tm_hour);
	Serial.print(":");
	Serial.print(datation.tm_min);
	Serial.print(":");
	Serial.println(datation.tm_sec);
	return datation;
}

HTR* HTR::getInstance() {
	if (htrInstance == 0) {
		htrInstance = new HTR();
	}
	return htrInstance;
}
