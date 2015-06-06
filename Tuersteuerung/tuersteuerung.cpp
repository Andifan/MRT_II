#include "ART3.h"
#include "ncurses.h"

#define offn_zeit = 2.00
#define oeffnen = 1
#define schliessen = 6

bool S1, S2, E1, E2, X1, X2, X3, LS1, LS2, BE, B, Y1, Y2, Y3;
long int signalcode = 0;
int modus; //0 - Automatik *** 1 - Hand *** 2 - Reparatur *** 3 - PST aus
bool A, H; //Automatik-Öffnungssignal (A), Handöffnungssignal (H)
/*
 * Der Simulationsmodus kann in der Headerdatei ART3.h mittels der
 * boolschen Variable SIMULATION an- oder ausgeschaltet werden!
 */
bool tuer_oeffnen () {
	while (!X1) {		//X1 = OFFEN- solange es noch nicht vollständig offen, Prüfen und Befehl weiter übergeben
		DIO_Write(oeffnen);
		signalverarbeitung();
	}
	return true;
}

bool tuer_auf(double zeit) {	//Zeitübergabe, wie lange  tür offen bleiben soll
	StartTimer(zeit);			//vorgefertigte wartefunktion
	signalverarbeitung();		
	if ((modus==0 && A)||(modus==1 && !E2)) {//wenn Automatik: neues Sensorsignal kommt, Hand: Schließbutton nicht gedrückt wurde
		if (!tuer_auf(offn_zeit)) {		//rekursion: wenn es offen bleiben soll, dann wird neue Funktion gestartet
			return false;
		}
	}
	return true;
}

bool tuer_schliessen() {
	while (!X3) {				//solange 
		if ((modus==0 && A)||(modus==1 && E1)) {
			return false;
		}
		DIO_Write(schliessen);
		signalverarbeitung();
	}
	return true;
}

bool steuerungsalgorithmus() {
	signalcode = 0;
	signalverarbeitung();
	if (S1&&S2) { //PST aus
		return true;
	}
	if (S1&&!S2) { //Reperatur
		return true;
	}
	if (!S1&&S2) { //Handbetrieb
		modus = 1;
		if (E1) {
			if (!tuer_oeffnen()) {
				return false;
			}
			if (!tuer_auf()) {
				return false;
			}
			while (!tuer_schliessen()) { //habe ich geändert : stand vorher false drin, damit ist aber ein mehrfaches Öffnen im Handbetrieb nicht möglich, habe ich zu analogem des Automatik betrieb geändert !!! wir hatten uns dabei doch nichts sinnvolles gedacht, oder ??????
				tuer_oeffnen();
				tuer_auf(offn_zeit);
			}

		}
	}
	if (!S1&&!S2) { //Automatik
		modus = 0;
		if (LS1||LS2||BE||B) {
			if (!tuer_oeffnen()) {
				return false;
			}
			if (!tuer_auf(offn_zeit)) {
				return false;
			}
			while (!tuer_schliessen()) {
				tuer_oeffnen();
				tuer_auf(offn_zeit);
			}
		}
	}
	return true;
}

void signalverarbeitung() {
	DIO_Read(&signalcode);
	int speicher = 0;
	for (int i = 0; i<14; ++i) {	//alle Stelles des DIO_Read werden ausgewertet-aber einzeln
		speicher = signalcode & 0x0001;	//letztes Zeichen wird evtl. einzige eins ///ich habe signal zu Signalcode geändert. das finde ich sinvoller oder ?????
		switch (i) {
			case 0: S1 = speicher; break;
			case 1: S2 = speicher; break;
			case 2: E1 = speicher; break;
			case 3: E2 = speicher; break;
			case 4: X1 = speicher; break;
			case 5: X2 = speicher; break;
			case 6: X3 = speicher; break;
			case 7: LS1 = speicher; break;
			case 10: LS2 = speicher; break;
			case 11: BE = speicher; break;
			case 12: B = speicher; break;
		}

		signal = signal >> 1;	//shift right : vorletztes Zeichen wird letztes
	}
	A = LS1 + LS2 + BE + B;
	//H = E1 + E2;
}

int main() {

	bool abbruch = true;

	// Fügen Sie hier ihren Code ein
	// ...

	DIO_Init(); 
	while (abbruch) {
		StartTimer(0.4);
		abbruch = steuerungsalgorithmus();
	}
	printf("Hallo Welt! \nSIMULATION = %i \n",SIMULATION);
	sleep(2);

	return 0;

}
