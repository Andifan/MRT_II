
int stringverarbeitung(char[] messung, int gerät) {

	if (strcmp(teilstring(0, 2, &messung[0]), "RES") == 0){
		// hier Quellcode einfügen
	}

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

char *teilstring(int anfang, int ende, char *ps1){
	char *ps = malloc(ende - anfang); // free muss noch hinzugefüght werden
	printf("%i \n", sizeof(ps1));
	char teil[sizeof(ps1)]; // es muss immer ein zeichen mehr platz definiert werden um platz für die \0 zu haben: 3 ausgelesene Elemente brauchen für 4 Platz
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