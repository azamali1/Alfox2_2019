#include "HTR.h"

HTR* HTR::htrInstance = 0;
HTR::HTR(){

}

struct tm HTR::setDatation(struct tm gpsDatation) {
	this->datation = gpsDatation;
	return datation;
}

struct tm HTR::getDatation() {
	return datation;
}

struct tm HTR::majDatation(unsigned int dureeMesuree){
	this->datation.tm_sec = dureeMesuree/100;
	return datation;
}

HTR* HTR::getInstance(){
	if (htrInstance == 0){
	htrInstance = new HTR();
	}
	return htrInstance;
}
