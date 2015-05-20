#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "com.h"
#include "strchang.h"
#include <math.h>

DWORD dw;
float r_0 = 100;
float alpha = 3,90802*0,001;
float beta = 0,580195*0,000001;
float umwandlungGrad = 273,1;


int main(){
// ************HANDLE ERSTELLEN************
	HANDLE hCOM;
	hCOM = CreateFile("Com1", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, NULL, NULL);
	if (hCOM == INVALID_HANDLE_VALUE) {
		printf("Handle konnte nicht erstellt werden. \n");
		return 1;
	}

	// ************KOMMMUNIKATIONSPARAMETER EINSTELLEN************
	DCB dcb;
	if (!GetCommState(hCOM, &dcb)) {
		printf("DCB Datei konnte nicht geladen werden \n");
		CloseHandle(hCOM);
		return 1;
	}
	int auswahl=0;
	printf("Multimeter auswählen \n \t 1 - Protek 506 \n \t 2 - PeakTech 4390 \n");
	scanf_s("%i", &auswahl);
	switch (auswahl){
	case 1:
		dcb.BaudRate = CBR_1200;
		dcb.Parity = NOPARITY;
		dcb.StopBits = TWOSTOPBITS;
		dcb.ByteSize = 7;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		if (!SetCommState(hCOM, &dcb)) {
			printf("DCB Datei konnte nicht beschrieben werden \n");
			CloseHandle(hCOM);
			return 1;
		}
		break;

	case 2:
		dcb.BaudRate = CBR_9600;
		dcb.Parity = NOPARITY;
		dcb.StopBits = TWOSTOPBITS;
		dcb.ByteSize = 7;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
		if (!SetCommState(hCOM, &dcb)) {
			printf("DCB Datei konnte nicht beschrieben werden \n");
			CloseHandle(hCOM);
			return 1;
		}
		break;
	
	default:
		printf("unzulässige Eingabe \n");
		CloseHandle(hCOM);
		return 1;
		break;
	}

	// ************KOMMUNIKATION************
	//*************antwortErhalten**********
	char eingabepuffer = [100];
	//
	if (!ReadFile(hCOM, eingabepuffer, 100, &dw, NULL))
	{
		printf("Daten konnten nicht empfangen werden\n");
		CloseHandle(handle);;
		return FALSE;
	}
	//
	if (dw != 100) {
		COMSTAT status;
		DWORD anzahl;
		ClearCommError(handle, &dw, &status);
		anzahl = status.cbInQue;
		if (anzahl) {
			WriteFile(handle, eingabepuffer, anzahl, &dw, NULL);
		}
	}

	//***************Anfrage senden******************

	if (!anfrageSenden(hCOM)) {
		printf("Anfrage an Multimeter fehlgeschlagen");
		CloseHandle(hCOM);
		return 1;
	}

	sleep(100); //TEST

	if (!antwortErhalten(hCOM)){
		printf("Antwort von Multimeter fehlgeschlagen");
		CloseHandle(hCOM);
		return 1;
	}

	float widerstand = stringverarbeitung(, auswahl)

	//Berechnung der Temperatur 
	float temperatur = umwandlungGrad - 0,5*(alpha/beta) + sqrt(0,25*((alpha*alpha)/(beta*beta)) + ((widerstand/r_0) - 1)/(beta));

	//Ausgabe des Ergebnisses
	printf("*****Die Temperatur beträgt %f Grad Celsius*****\n\n", temperatur);

	return 0;
}


BOOL anfrageSenden(HANDLE handle)
{
	char ausgabepuffer = "D";
	//
	if (!WriteFile(handle, ausgabepuffer, 1, &dw, NULL)) {
		printf("Anfrage konnte nicht gesendet werden \n");
		CloseHandle(handle);
		return FALSE;
	}
	//
	if (dw != 1) {
		COMSTAT status;
		DWORD anzahl;
		ClearCommError(handle, &dw, &status);
		anzahl = status.cbOutQue;
		if (anzahl) {
			WriteFile(handle, ausgabepuffer, anzahl, &dw, NULL);
		}
	}
	//
	return TRUE;
}