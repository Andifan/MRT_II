//http://www2.informatik.uni-halle.de/lehre/c/c_str2n.html
// das mit dem string und den Pointern ist cool, aber doch super aufwändig. 
// Ich habe im Internet eine gute umwandlung gefunden, die alternativ auch funktionieren könnte 
// doch ich finde die variante auch gut... 
// also mir ist es gleich... 
// nur nochmal zum anschauen vllt. 
// dann hätte man einfach Teile des Arrays herausgenommen (4. -8. Zeichen ) und umgewandelt ... 

int stringverarbeitung(char[] messung, int geraet) {

	if (strcmp(teilstring(0, 2, &messung[0]), "RES") == 0){
		// hier Quellcode einfügen
	}

	if (geraet == 1)
	{
		for (int i = 0; i <=2 ; ++i)
		{
			
		}
	}

	if (geraet == 2)
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
