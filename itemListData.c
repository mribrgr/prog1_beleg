//
//  itemListData.c
//  beleg
//
//  Created by Mauritius Berger on 02.01.19.
//  Copyright © 2019 Mauritius Berger. All rights reserved.
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

/* parst die Daten aus dem eingegebenen File und gibt die Daten als Item zurück */
t_item* getItemFromData(FILE* filePointer, t_person* firstPerson, t_item* firstItem)
{
    /* Deklarationen & Definitionen */
    char line[64];
    
    t_item* tmpItem = malloc(sizeof(t_item));
    if (!tmpItem) {
        error("Speicherreservierungen fehlgeschlagen bei 'getItemFromData()'!");
    }
    
    fgets(line, 64, filePointer);
    
    if (!testLoanDataLine(line)) {
        return NULL; // eigentlich sollte er nur abbrechen wenn das file zu ende ist und nicht beim ersten ungültigen
    }
    
    char* partId = malloc(sizeof(char) * 64);
    char* partPersonId = malloc(sizeof(char) * 64);
    char* partName = malloc(sizeof(char) * 64);
    char* partType = malloc(sizeof(char) * 64);
    char* partAuthor = malloc(sizeof(char) * 64);
    
    if (!partId || !partPersonId || !partName || !partType || !partAuthor) {
        error("Speicher konnte nicht reserviert werden bei 'getItemFromData()'!");
    }
    
    strcpy(partId, strtok(line, ",\0"));
    strcpy(partPersonId, strtok(NULL, ",\0"));
    strcpy(partName, strtok(NULL, ",\0"));
    strcpy(partType, strtok(NULL, ",\0"));
    strcpy(partAuthor, strtok(NULL, ",\0"));
    
    tmpItem = createItem(
        partName,
        partType,
        partAuthor,
        atol(partId)
    );
    
    free(partId);
    free(partPersonId);
    
    return tmpItem;
}
