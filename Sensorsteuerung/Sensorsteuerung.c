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

/*/
float stringverarbeitung(char *messung, int geraet) {
    
    float z;
	if (geraet == 1){
	    char *pt = teilstring(0, 2, &messung[0])
	    if (strcmp(*pt, "RES") == 0){
		    free(pt);
		    *pt = teilstring(4, 8, &messung[0]);
		    z = atof(*pt);
		    free(pt);
		    *pt = teilstring(10,10, &messung[0]);
		    switch (*pt) {
		        case 'm':
		            return(z*0.001);
		            break;
		        case 'o':
		        	return(z);
		            break;
		        case 'k':
		            z=z*1000;
		            break;
		        case 'M':
		            return(z*1000000);
		            break;
		        case 'G':
		            return(z*1000000000);
		            break;
		        default 
		            printf("unbekannte Einheit");
		            return(-1);
		            break;
		            
		    }
		    free (*pt);
		    return(-1);
		    
	    }
	}

	if (geraet == 2)
	{
	    char *pt = teilstring(0, 1, &messung[0])
	    if (strcmp(*pt, "OH") == 0){
		    free(pt);
		    *pt = teilstring(4, 8, &messung[0]);
		    z = atof(*pt);
		    free(pt);
		    *pt = teilstring(9,9, &messung[0]);
		    switch (*pt) {
		        case 'm':
		            return(z*0.001);
		            break;
		        case ' ':
		        	return(z);
		            break;
		        case 'k':
		            z=z*1000;
		            break;
		        case 'M':
		            return(z*1000000);
		            break;
		        case 'G':
		            return(z*1000000000);
		            break;
		        default 
		            printf("unbekannte Einheit");
		            return(-1);
		            break;
		            
		    }
		    free(*pt);
		    return(-1);
	    }
	}

	else {
		printf("Gerät wurde nicht erkannt und String nicht bearbeitet\n");
		return (-1);
	}
}

char *teilstring(int anfang, int ende, char *ps1){
	char *ps = malloc(ende - anfang); // free muss noch hinzugefüght werden
	printf("%i \n", sizeof(ps));
	char teil[sizeof(ps)]; // es muss immer ein zeichen mehr platz definiert werden um platz für die \0 zu haben: 3 ausgelesene Elemente brauchen für 4 Platz
	ps1 = ps1 + anfang;
	int i;
	for (i = anfang; i <= ende; i++) {
		teil[i - anfang] = *ps1;
		ps1++;
	}
	teil[i - anfang] = '\0'; // schließt String ab
	printf("%s \n", teil);
	strcpy(ps, teil);
	return ps;
}
/*/

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
	char ausgabepuffer = "D";		
			
	if (!WriteFile(handle, ausgabepuffer, 1, &dw, NULL)) {		
		printf("Anfrage konnte nicht gesendet werden \n");		
		CloseHandle(handle);		
		return 1;		
	}		
			
	if (dw != 1) {		
		COMSTAT status;		
		DWORD anzahl;		
		ClearCommError(handle, &dw, &status);		
		anzahl = status.cbOutQue;		
		if (anzahl) {		
			WriteFile(handle, ausgabepuffer, anzahl, &dw, NULL);		
		}		
	}

	sleep(100);
	//*************antwortErhalten**********
	char eingabepuffer = [100];
	
	if (!ReadFile(hCOM, eingabepuffer, 100, &dw, NULL))
	{
		printf("Daten konnten nicht empfangen werden\n");
		CloseHandle(handle);
		return 1;
	}
	
	if (dw != 100) {
		COMSTAT status;
		DWORD anzahl;
		ClearCommError(handle, &dw, &status);
		anzahl = status.cbInQue;
		if (anzahl) {
			WriteFile(handle, eingabepuffer, anzahl, &dw, NULL);
		}
	}

	//************ String verarbeiten*********************
//	widerstand=stringverarbeitung(&messung[0],auswahl);
	char zahl[5];		
			
	for (int i=4,i<=8,i++) {		
		zahl[i-4]=messung[i];		
	}		
		
	float widerstand=atof(zahl);		
		
	switch(messung[11 - auswahl]) {		
		case 'm':		
			widerstand=widerstand*0,001;	
			break;		
		
		case 'o':		
			widerstand=widerstand;
			break;		
		
		case 'k':		
			widerstand=widerstand*1000;		
			break;		
		
		case 'M':		
			widerstand=widerstand*1000000;		
			break;
			
		case ' '
			if (auswahl=1) {
				widerstand=-1;
			}
			if (auswahl=2) {
				widerstand=widerstand;
			}
			
		default:		
			printf("Konnte Einheit nicht lesen.\n");		
			widerstand=-1;		
			break;	

	// **********Berechnung der Temperatur************ 
	temperatur = 0;
	if (widerstand!=-1){
		temperatur = umwandlungGrad - 0.5*(alpha/beta) + sqrt(0.25*((alpha*alpha)/(beta*beta)) + ((widerstand/r_0) - 1)/(beta));		
		printf("*****Die Temperatur beträgt %f Grad Celsius*****\n\n", temperatur);	
	}
	else {
		printf("fehlerhafte messung \n\n");
	}
	
	return 0;
}
