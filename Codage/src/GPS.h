#ifndef __GPS__
#define __GPS__

#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <time.h>


class GPS
{

	private:

		float latitude;
		float longitude; 
		float vitesse;
		struct tm datation;
		bool available = false;
		static GPS* gpsInstance;
		GPS();
		//HTR*
    
    boolean usingInterrupt = false;
    Adafruit_GPS* gps;
    HardwareSerial* serialGPS;


	public:
	
		/** Constructeur **/
		static GPS* getInstance();
		int maj();
		float getLatitude() {return latitude;};
		float getLongitude() {return longitude;};
		float getVitesse() {return vitesse;};
		struct tm getDatation() {return datation;};
		bool isDispo();
		char readDATA();
		
};

#endif
