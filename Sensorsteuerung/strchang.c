
float stringverarbeitung(char messung, int geraet) {


	char zahl[5]
	
	for (int i=4,i<=8,i++) {
		zahl[i-4]=messung[i];
	}

	float z=atof(zahl);

	switch(messung[11 - geraet]) {
		case m:
			return (z*0,001);
			break;

		case o:
			return z;
			break;

		case k:
			return (z*1000);
			break;

		case M:
			return (z*1000000);
			break;

		default:
			printf("Konnte Einheit nicht lesen.\n");
			return (-1);
			break;
	}

/*/char *teilstring(int anfang, int ende, char *ps1){
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
/*/

}