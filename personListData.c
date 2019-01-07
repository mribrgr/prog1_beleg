//
//  personList.c
//  beleg
//
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

/* Standardbibliotheken */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Eigene Header-Dateien */
#include "main.h"
#include "date.h"
#include "item.h"
#include "person.h"
#include "loan.h"

/* parst die Daten aus dem eingegebenen File und gibt die Daten als Person zurück */
t_person* getPersonFromData(FILE* filePointer)
{
    /* Deklarationen & Definitionen */
    char line[64];
    
    t_person* tmpPerson = NULL;
    
    fgets(line, 64, filePointer);
    
    if (!testPersonDataLine(line)) {
        // warning("Zeile aus 'person.csv' war ung&uuml;ltig bei 'getOneDataToPerson()'!");
        return NULL; // eigentlich sollte er nur abbrechen wenn das file zu ende ist und nicht beim ersten ungültigen
    }
    
    char* partId = malloc(sizeof(char) * 64);
    char* partFirstName = malloc(sizeof(char) * 64);
    char* partLastName = malloc(sizeof(char) * 64);
    char* partDate = malloc(sizeof(char) * 64);
    
    if (!partId || !partFirstName || !partLastName || !partId || !partDate) {
        error("Speicher konnte nicht reserviert werden bei 'getOneDataToPerson()'!");
    }
    
    strcpy(partId, strtok(line, ",\0"));
    strcpy(partFirstName, strtok(NULL, ",\0"));
    strcpy(partLastName, strtok(NULL, ",\0"));
    strcpy(partDate, strtok(NULL, ",\0"));
    
    tmpPerson = createPerson(
        partFirstName,
        partLastName,
        getDateFromString(partDate),
        atol(partId)
    );

    free(partId);
    free(partDate);
    
    return tmpPerson;
}
