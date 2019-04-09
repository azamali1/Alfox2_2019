#include "HTR.h"

HTR* HTR::htrInstance = 0;
HTR::HTR() {

}

void HTR::setDatation(struct tm gpsDatation) {
	this->datation = gpsDatation;

}

struct tm HTR::getDatation() {
	return datation;
}

struct tm HTR::majDatation(unsigned long dureeMesuree) {

	this->datation.tm_sec += int(dureeMesuree) / 1000;
	if (datation.tm_sec >= 60) {
		datation.tm_sec -= 60;
		datation.tm_min += 1;
	}
	if(datation.tm_min >= 60){
		datation.tm_min -= 60;
		datation.tm_hour += 1;
	}
	if(datation.tm_hour >= 24){
		datation.tm_hour -= 24;
		datation.tm_mday += 1;
	}
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
