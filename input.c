//
//  input.c
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

t_person* inputPerson(t_person* firstPerson, t_person* lastPerson, char* vorname, char* nachname, int tag, int monat, int jahr)
{
    /* Definitionen */
    t_person* tmpPerson = NULL;
    
    if (!testInputNewPerson(vorname, nachname, tag, monat, jahr)) {
        error("Eingabe der Person ist falsch!");
    }
    
    tmpPerson = createPerson(vorname, nachname, createDate(tag, monat, jahr), getMaxPersonId(firstPerson) + 1);
    addPersonToList(lastPerson, tmpPerson);
    if (!testPerson(firstPerson)) {
        firstPerson = tmpPerson;
    }
    appendPersonToData(tmpPerson);
    
    if (!testPerson(tmpPerson)) {
        error("Person konnte nicht eingelesen werden!");
    } else {
        printAddSuccess("person");
    }
    
    return tmpPerson;
}

int testInputNewPerson(char* vorname, char* nachname, int tag, int monat, int jahr)
{
    if (strlen(vorname) > 0 && strlen(nachname) > 0 && tag > 0 && tag <= 31 && monat > 0 && monat <= 12 && jahr > 1900 && jahr <= 2050 ) {
        return 1;
    }
    
    return 0;
}
