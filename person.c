//
//  person.c
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

t_person* createPerson(char* firstName, char* lastName, t_date* gebDatum, unsigned long identifier)
{
    t_person* tmpPerson = malloc(sizeof(t_person));
    if (!tmpPerson) {
        error("Speicherreservierung für Person fehlgeschlagen bei 'createPerson()'!");
    }
    
    tmpPerson->id = identifier;
    tmpPerson->before = tmpPerson->next = NULL; // alle NULL, bedeutet begin und ende ist NULL
    tmpPerson->first_name = firstName;
    tmpPerson->last_name = lastName;
    tmpPerson->gebDatum = gebDatum;
    
    return tmpPerson;
}

/* Guckt ob die angegebene Linie der Datei gültig ist */
int testPersonDataLine(char* line)
{
    /* Deklarationen & Definitionen */
    int i, countComma = 0, countDot = 0, diff = 0, last = 0;
    
    for (i=0; i<64 && line[i] != '\n'; i++) {
        if (!isalnum(line[i]) && line[i] != ',' && line[i] != '.') {
            return 0;
        }
        if (line[i] == ',') {   // , bei 4 und , bei 5
            diff = i - last;    // diff = 1
            last = i;           // last = 5
            countComma++;
        }
        if (line[i] == '.') {
            diff = i - last;
            last = i;
            countDot++;
        }
        if ((diff == 0 && countComma == 1) || (diff == 1 && i != 1 && last != 1)) {
            return 0;
        }
    }
    if (countComma == 3 && countDot == 2) {
        return 1;
    }
    
    return 0;
}
