#include <time.h>
#include <RTCZero.h>

class HTR {

private:
	struct tm datation;
	HTR();
	static HTR* htrInstance;

public:
	static HTR* getInstance();
	struct tm getDatation();
	void setDatation(struct tm gpsDatation);
	struct tm majDatation(unsigned long dureeMesuree);
};
