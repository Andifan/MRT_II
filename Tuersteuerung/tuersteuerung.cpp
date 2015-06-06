#include "ART3.h"
#include "ncurses.h"



/*
 * Der Simulationsmodus kann in der Headerdatei ART3.h mittels der
 * boolschen Variable SIMULATION an- oder ausgeschaltet werden!
 */

bool steuerungsalgorithmus() {
	long int signalcode = 0;
	DIO_Read(&signalcode);

}

int signalverarbeitung(long int &signal, int channel) {

}

int main() {

	bool abbruch = false;

	// Fügen Sie hier ihren Code ein
	// ...

	DIO_Init();
	while (!abbruch) {
		StartTimer(0.4);
		steuerungsalgorithmus();
	}
	printf("Hallo Welt! \nSIMULATION = %i \n",SIMULATION);
	sleep(2);

}
