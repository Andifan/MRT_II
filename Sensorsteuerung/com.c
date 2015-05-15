#include "com.h";
#include <string.h>;
#include <Windows.h>;


DWORD dw; // Speichert die Anzahl der wirklich geschriebenen oder gelesenen Bytes und den Fehlercode im Falle eines Fehlers
BOOL anfrageSenden(HANDLE handle)
{
	char ausgabepuffer = "D";
	if (!WriteFile(handle, ausgabepuffer, 100, &dw, NULL)) {
		printf("Anfrage konnte nicht gesendet werden \n");
		CloseHandle(handle);
		return FALSE;
	}
	if (dw != 100) {
		COMSTAT status;
		DWORD anzahl;
		ClearCommError(handle, &dw, &status);
		anzahl = status.cbOutQue;
		if (anzahl) {
			WriteFile(handle, ausgabepuffer, anzahl, &dw, NULL);
		}
	}
	//
}