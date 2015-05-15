#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(){
	HANDLE hCOM;
	hCOM = CreateFile("Com1", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, NULL, NULL);
	if (hCOM == INVALID_HANDLE_VALUE) {
		printf("Handle konnte nicht erstellt werden. \n");
		return 1;
	}

	return 0;
}
