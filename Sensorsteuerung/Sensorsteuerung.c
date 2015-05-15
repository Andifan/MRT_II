#include <stdio.h>
#include <windows.h>
#include <string.h>

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
	printf("Multimeter ausw�hlen \n \t 1 - Protek 506 \n \t 2 - PeakTech 4390 \n");
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
	
	default:
		printf("unzul�ssige Eingabe \n");
		CloseHandle(hCOM);
		return 1;
	}

	return 0;
}
