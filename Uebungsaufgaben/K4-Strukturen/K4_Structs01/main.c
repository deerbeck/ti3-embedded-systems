#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char vorname[50];
    char nachname[50];
    int tag;
    int monat;
    int jahr;
};

int main() {
    FILE *datei = fopen("celebrity.txt", "r");
    if (datei == NULL) {
        printf("Fehler beim Öffnen der Datei.\n");
        return 1;
    }

    struct Person personen[100];
    int anzahlPersonen = 0;
    char zeile[100];

    while (anzahlPersonen < 100 && fgets(zeile, sizeof(zeile), datei) != NULL) {
        char *vorname = strtok(zeile, ";");
        char *nachname = strtok(NULL, ";");
        char *geburtsdatum = strtok(NULL, "\n");

        if (vorname != NULL && nachname != NULL && geburtsdatum != NULL) {
            strcpy(personen[anzahlPersonen].vorname, vorname);
            strcpy(personen[anzahlPersonen].nachname, nachname);
            sscanf(geburtsdatum, "%d/%d/%d",
                   &personen[anzahlPersonen].tag,
                   &personen[anzahlPersonen].monat,
                   &personen[anzahlPersonen].jahr);

            anzahlPersonen++;
        }
    }

    fclose(datei);

    // Ausgabe der ersten 16 Einträge
    for (int i = 0; i < anzahlPersonen && i < 16; i++) {
        printf("Vorname: %s\n", personen[i].vorname);
        printf("Nachname: %s\n", personen[i].nachname);
        printf("Geburtsdatum: %d/%d/%d\n", personen[i].tag, personen[i].monat, personen[i].jahr);
        printf("\n");
    }

    return 0;
}
