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

/* schiebt inputPerson in die Liste nach beforePerson ein
 Rückgabewert: Ende der Liste! // was soll damit gemacht werden?
 */
t_person* addPersonToList(t_person* beforePerson, t_person* inputPerson)
{
    if (!testPerson(inputPerson)) {
        return NULL;
    }
    
    if (!beforePerson && inputPerson) {
        return inputPerson;
    }
    
    if (beforePerson->next) {
        beforePerson->next->before = inputPerson;
        inputPerson->next = beforePerson->next;
    }
    inputPerson->before = beforePerson;
    beforePerson->next = inputPerson;
    
    return inputPerson;
}

/* Rückgabewert: Erstes Element der Liste */
t_person* deletePersonFromList(t_person* tmpPerson, t_person* firstPerson)
{
    if (!testPerson(tmpPerson)) {
        printNotFound("person");
        return firstPerson; // die Person gibt s nicht, d.h. nichts tun
    }
    
    if (!tmpPerson->before && tmpPerson->next) { // kein davor; beginn der liste
        firstPerson = tmpPerson->next;
        tmpPerson->next->before = NULL;
    } else if (tmpPerson->before && !tmpPerson->next) { // nur kein element danach; ende der liste
            tmpPerson->before = NULL;
    } else if (tmpPerson->before && tmpPerson->next) { // mittendrin
        tmpPerson->before->next = tmpPerson->next;
        tmpPerson->next->before = tmpPerson->before;
    } else { // bedeutet es gibt weder ein Element davor noch danach === komplette Liste ist nur ein Element
        firstPerson = NULL;
    }
    
    freePerson(tmpPerson);
    
    return firstPerson;
}

void writePersonToData(FILE* filePointer, t_person* tmpPerson)
{
    fprintf(
        filePointer,
        "%ld,%s,%s,%d.%d.%d\n",
        tmpPerson->id,
        tmpPerson->first_name,
        tmpPerson->last_name,
        tmpPerson->gebDatum->day,
        tmpPerson->gebDatum->month,
        tmpPerson->gebDatum->year
    );
    
    return;
}

void writePersonListToData(t_person* firstPerson)
{
    /* Deklarationen */
    FILE* filePointer;
    t_person* tmpPerson;
    
    filePointer = fopen("person.csv", "w"); /* Beim Modus 'w' wird eine eventuelle schon vorhandene Datei ueberschrieben */
    if (filePointer == NULL) {
        error("Schreiben der 'person.csv' nicht moeglich bei 'deletePersonFromData()'!");
    }
    
    if (testPerson(firstPerson)) {
        tmpPerson = firstPerson;
        writePersonToData(filePointer, tmpPerson);
        while(tmpPerson->next) {
            tmpPerson = tmpPerson->next;
            /* Stellt sicher, dass auch wirklich nur richtige Daten in die Datei geschrieben werden. */
            if (testPerson(tmpPerson)) {
                writePersonToData(filePointer, tmpPerson);
            }
        }
    }
    
    fclose(filePointer);
    
    return;
}

void appendPersonToData(t_person* tmpPerson)
{ // evtl umstrukturieren, damit man mithilfe der ->next und ->before die Person einspeichern kann
    /* Deklarationen */
    FILE* filePointer;
    
    if (!testPerson(tmpPerson)) {
        return;
    }
    
    filePointer = fopen("person.csv", "a"); // ich gehe davon aus, dass man immer am beginn einer leeren Zeile startet, er holt sich jedoch auch nicht die aktuelle PersonID
    if (!filePointer) {
        error("&Ouml;ffnen der 'person.csv' nicht moeglich bei 'appendPersonToData()'!");
    }
    writePersonToData(filePointer, tmpPerson);
    fclose(filePointer);
    
    return;
}

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

/* holt sich die Daten aus der person.csv-Datei
 und gibt das erste Element, falls vorhanden, zurück */
t_person* addPersonListDataToList(t_person* firstPerson, t_person* lastPerson)
{
    /* Deklarationen & Definitionen */
    FILE* filePointer;
    t_person* tmpPerson;
    int first = 0;
    
    if (!firstPerson || !lastPerson) {
        return NULL;
    }
    
    filePointer = fopen("person.csv", "r");
    if (!filePointer) {
        warning("'person.csv' konnte nicht ge&ouml;ffnet werden bei 'addPersonDataToList()'.");
        return NULL;
    }
    while(1) {
        tmpPerson = getPersonFromData(filePointer);
        if (!tmpPerson) {
            break;
        }
        if (!first) {
            lastPerson = firstPerson = tmpPerson;
            first = 1;
        } else {
            lastPerson = addPersonToList(lastPerson, tmpPerson);
        }
    }
    fclose(filePointer);
    
    return firstPerson;
}
