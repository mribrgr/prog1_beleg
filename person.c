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

t_person* getPerson(unsigned long identifier, t_person* firstPerson)
{
    if (!testPerson(firstPerson)) {
//        printPersonNotFound();
        return NULL;
    }
    
    t_person* currPerson = firstPerson;
    if (currPerson->id == identifier) {
        return currPerson;
    }
    currPerson = currPerson->next;
    while(currPerson) {
        if (currPerson->id == identifier) {
            return currPerson;
        }
        currPerson = currPerson->next;
    }
    
    return NULL;
}

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

/* Gibt die hoechste Id zurueck*/ // eventuell so umwandeln, dass auch eventuell freie IDs vergeben werden von Personen die mal gelöscht wurden
unsigned long getMaxPersonId(t_person* firstPerson)
{
    /* Deklarationen & Definitionen */
    unsigned long curr;
    t_person* tmpPerson = firstPerson;
    
    if (!testPerson(firstPerson)) {
        return 0;
    }
    
    curr = firstPerson->id;
    
    while (tmpPerson) {
        if (curr < tmpPerson->id) {
            curr = tmpPerson->id;
        }
        tmpPerson = tmpPerson->next;
    }
    
    return curr;
}

/* Gibt die letzte Id zurueck */
unsigned long getLastPersonId(t_person* firstPerson)
{
    /* Definitionen */
    t_person* tmpPerson = firstPerson;
    
    if (!testPerson(firstPerson)) {
        return 0;
    }
    
    while (tmpPerson->next) {
        tmpPerson = tmpPerson->next;
    }
    
    return tmpPerson->id;
}

/* Legt den Speicher von einer Person wieder frei,
 es werden nicht die ->next oder ->before Zeiger beachtet. */
void freePerson(t_person* tmpPerson)
{
    if (!testPerson(tmpPerson)) {
        return;
    }
    
    free(tmpPerson->first_name);
    free(tmpPerson->last_name);
    free(tmpPerson);
    tmpPerson = NULL;
    
    return;
}

void freePersonList(t_person* firstPerson)
{
    if (!testPerson(firstPerson)) {
        return;
    }
    
    t_person* tmpPerson = firstPerson->next;
    if (tmpPerson) {
        while (tmpPerson->next) {
            tmpPerson = tmpPerson->next;
            freePerson(tmpPerson->before);
        }
        freePerson(tmpPerson);
    }
    freePerson(firstPerson);
    
    return;
}

// sollte noch verbessert werden, sodass wirklich alles überprüft wird
int testPerson(t_person* tmpPerson)
{
    if (tmpPerson) {
        if (tmpPerson->id) {
            return 1;
        }
    }
    
    return 0;
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
