
#ifndef All_Arduino_or_Cpp_symboldefines_h
#define All_Arduino_or_Cpp_symboldefines_h

#ifndef COMPILE_CPP_NOT_ARDUINO
#include <Arduino.h>

#else

#include "stdio.h"
#include <string>
using namespace std;

typedef bool boolean; 
#define LOW 0
#define HIGH 1
#define INPUT 1
#define OUTPUT 0
#define INPUT_PULLUP 2

#define min(x, y) (x<y)?x:y
#define max(x, y) (x>y)?x:y



//#define Serial.print('TheString') printf("\n TheString \n")
#define byte(x) (unsigned char)(x)
#define DEC 0
struct dummy_Serial
{
	void begin(int rate){printf("\n Serial.begin(%d)\n", rate);}
	int available(){printf("\n Serial Available?\n"); return getchar();}
	int read(){printf("\n input Serial incoming byte\n"); return getchar();}
	void println(int incomingCommandByte, int frmt){;}
	void println(char inchar){;}
	void println(){printf("\n");}
	void print(char *inchar){printf(inchar);}	
	void print(int inint){printf("\n %d", inint);}
	//void print(){;}
	int write(unsigned char in_byte){return 1;}
};


extern struct dummy_Serial Serial;

struct Stream
{
	void begin(int rate){printf("\n Serial.begin(%d)\n", rate);}
	int available(){printf("\n Serial Available?\n"); return getchar();}
	int read(){printf("\n input Serial incoming byte\n"); return getchar();}
	void println(int incomingCommandByte, int frmt){;}
	void println(char inchar){;}
	void println(){;}
	int write(unsigned char in_byte){return 1;}
	void flush(){printf("\n Serial.flush\n");}

};

#define String string

void pinMode(int PIN, int INPUTorOUTPUT);
void pinMode(char PIN_str[], int INPUTorOUTPUT);

void digitalWrite(int PIN , int VAL);
int digitalRead(int PIN);

int analogRead(int PIN);
void analogWrite(int PIN , int VAL);

void delay(int DEL_MS) ;

void delayMicroseconds(int DEL_MS);

int pulseIn(int signal_pin, int HIGH_or_low, int timeout_microsec);


int millis();


#define CHANGE 2
#define RISING 3
#define FALLING 4

#endif





#endif