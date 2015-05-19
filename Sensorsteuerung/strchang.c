#include "strchang.h";
#include <string.h>;
#include <Windows.h>;
#include <cstring.h>;

int stringverarbeitung(char[] messung, int gerät) {
	char messkopie[];
	strcpy_s(messkopie, sizeof(messung), messung);

	if (gerät == 1)
	{
		for (int i = 0; i <=2 ; ++i)
		{
			
		}
	}

	if (gerät == 2)
	{
		/* code */
	}

	else {
		printf("Gerät wurde nicht erkannt und String nicht bearbeitet\n");
		return 0;
	}
}

void teilstring(int anfang, int ende, char messung[], char *ps) {
	char teil[ende - anfang];
	for (int i = anfang; i <= ende; ++i)
	{
		teil[i - anfang] = messung[i];
	}

	strcpy(ps, teil);
	
}