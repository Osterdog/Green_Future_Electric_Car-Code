#ifdef COMPILE_CPP_NOT_ARDUINO

#include "All_Arduino_or_Cpp_symboldefines.h"


struct dummy_Serial Serial;



void pinMode(int PIN, int INPUTorOUTPUT)
{printf("\n Assign pin %d  to %d mode \n", PIN, INPUTorOUTPUT);}

void pinMode(char PIN_str[], int INPUTorOUTPUT)
{printf("\n Assign pin %s  to %d mode \n", PIN_str, INPUTorOUTPUT);}




void digitalWrite(int PIN , int VAL)
{printf("\n digital write of %d on pin %d\n", VAL, PIN);}

int digitalRead(int PIN)
{printf("\n digital read from pin %d \n", PIN); return getchar();}



void analogWrite(int PIN , int VAL)
{printf("\n Analogue write on pin %d of value %d \n", PIN, VAL);}

int analogRead(int PIN)
{printf("\n Analogue read from pin %d\n", PIN); return (int) getchar();}



void delay(int DEL_MS) 
{printf("\n delay of %d ms \n", DEL_MS);}

void delayMicroseconds(int DEL_MS)
{printf("\n delay of %d micros \n", DEL_MS);}

int pulseIn(int signal_pin, int HIGH_or_low, int timeout_microsec)
{printf("\n pulse in from pin %d value %d Tout %d \n", signal_pin, HIGH, timeout_microsec); return getchar();}


int millis()
{printf("\n call to millis\n"); return getchar();}





#endif