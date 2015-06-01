#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>

DWORD dw;
float temperatur;
#define r_0 100
#define alpha 3.90802*0.001
#define beta 0.580195*0.000001
#define umwandlungGrad 273,1

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
	//***************Anfrage senden******************
	do{
		char ausgabepuffer = "D";		
				
		if (!WriteFile(hCOM, ausgabepuffer, 1, &dw, NULL)) {		
			printf("Anfrage konnte nicht gesendet werden \n");		
			CloseHandle(hCOM);		
			return 1;		
		}		
			
		if (dw != 1) {		
			COMSTAT status;		
			DWORD anzahl;		
			ClearCommError(hCOM, &dw, &status);		
			anzahl = status.cbOutQue;		
			if (anzahl) {		
				WriteFile(hCOM, ausgabepuffer, anzahl, &dw, NULL);		
			}		
		}

		sleep(100);
		//*************antwortErhalten**********
		char eingabepuffer = [100];
	
		if (!ReadFile(hCOM, eingabepuffer, 100, &dw, NULL))
		{
			printf("Daten konnten nicht empfangen werden\n");
			CloseHandle(hCOM);
			return 1;
		}
		
		if (dw != 100) {
			COMSTAT status;
			DWORD anzahl;
			ClearCommError(hCOM, &dw, &status);
			anzahl = status.cbInQue;
			if (anzahl) {
				WriteFile(hCOM, eingabepuffer, anzahl, &dw, NULL);
			}
		}

		//************ String verarbeiten*********************
		char zahl[5];		
		float faktor=-1;	
		float widerstand=-1;
		switch(eingabepuffer[11 - auswahl]) {		
			case 'm':		
				faktor=0.001;	
				break;		
		
			case ('o' || 'O'):		
				faktor=1;
				break;
			
			case 'k':		
				faktor=1000;		
				break;		
		
			case 'M':		
				faktor = 1000000;		
				break;
				
			case ' '
				if (auswahl=1) {
					faktor=-1;
				}
				if (auswahl=2) {
					faktor=1;
				}
				
			default:		
				printf("Konnte Einheit nicht lesen.\n");		
				faktor=-1;		
				break;
		}
	
		if (faktor != -1) {
			for (int i=4,i<=8,i++) {		
				zahl[i-4]=eingabepuffer[i];		
			}
			widerstand = atof(zahl);
			widerstand=widerstand*faktor;
		}
			

		// **********Berechnung der Temperatur************ 
		temperatur = 0;
		if (widerstand>0){
			temperatur = umwandlungGrad - 0.5*(alpha/beta) + sqrt(0.25*((alpha*alpha)/(beta*beta)) + ((widerstand/r_0) - 1)/(beta));		
			printf("*****Die Temperatur beträgt %f Grad Celsius*****\n\n", temperatur);	
		}
		else {
			printf("fehlerhafte messung \n\n");
		}
	}
	while()
	return 0;
}
