//
//  general.c
//  beleg
//
//  Created by Mauritius Berger on 04.01.19.
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

int testObj (void* input)
{
    t_loan* tmp = input;
    if (tmp) {
        if (tmp->id) {
            return 1;
        }
    }
    
    return 0;
}

void* getObj (unsigned long identifier, void* firstObj)
{
    if (!testObj((t_loan*) firstObj)) {
        return NULL;
    }
    
    t_loan* currObj = (t_loan*) firstObj;
    if (currObj->id == identifier) {
        return currObj;
    }
    currObj = currObj->next;
    while(currObj) {
        if (currObj->id == identifier) {
            return currObj;
        }
        currObj = currObj->next;
    }
    
    return NULL;
}

void appendObjToData (char* structure, void* tmp)
{
    /* Deklarationen */
    FILE* filePointer;
    char buf[64];
    
    if (!testObj(tmp)) {
        return;
    }
    sprintf(buf, "%s.csv", structure);
    
    filePointer = fopen(buf, "a");
    if (!filePointer) {
        sprintf(buf, "&Ouml;ffnen der '%s.csv' nicht moeglich bei 'appendObjToData()'!", structure);
        error(buf);
    }
    
    if (!strcmp(structure, "item")) {
        t_item* tmpObj = (t_item*) tmp;
        writeObjToData(structure, filePointer, tmpObj);
    } else if (!strcmp(structure, "loan")) {
        t_loan* tmpObj = (t_loan*) tmp;
        writeObjToData(structure, filePointer, tmpObj);
    } else if (!strcmp(structure, "person")) {
        t_person* tmpObj = (t_person*) tmp;
        writeObjToData(structure, filePointer, tmpObj);
    }
    
    fclose(filePointer);
    
    return;
}

void writeObjListToData (char* structure, void* tmp)
{
    /* Deklarationen */
    FILE* filePointer;
    char buf[64];
    
    sprintf(buf, "%s.csv", structure);
    filePointer = fopen(buf, "w"); /* Beim Modus 'w' wird eine eventuelle schon vorhandene Datei ueberschrieben */
    if (!filePointer) {
        sprintf(buf, "Schreiben der '%s.csv' nicht moeglich bei 'writeObjListToData()'!", structure);
        error(buf);
    }
    
    if (testObj(tmp)) {
        if (!strcmp(structure, "item")) {
            writeObjToData(structure, filePointer, (t_item*) tmp);
        } else if (!strcmp(structure, "loan")) {
            writeObjToData(structure, filePointer, (t_loan*) tmp);
        } else if (!strcmp(structure, "person")) {
            writeObjToData(structure, filePointer, (t_person*) tmp);
        }
        while(((t_loan*) tmp)->next) {
            tmp = ((t_loan*) tmp)->next;
            /* Stellt sicher, dass auch wirklich nur richtige Daten in die Datei geschrieben werden. */
            if (testObj(tmp)) {
                if (!strcmp(structure, "item")) {
                    writeObjToData(structure, filePointer, (t_item*) tmp);
                } else if (!strcmp(structure, "loan")) {
                    writeObjToData(structure, filePointer, (t_loan*) tmp);
                } else if (!strcmp(structure, "person")) {
                    writeObjToData(structure, filePointer, (t_person*) tmp);
                }
            }
        }
    }
    
    fclose(filePointer);
    
    return;
}

void writeObjToData(char* structure, FILE* filePointer, void* tmpObj)
{
    if (!strcmp(structure, "loan")) {
        fprintf(filePointer,"%ld", ((t_loan*) tmpObj)->id);
        fprintf(filePointer,",%ld", ((t_loan*) tmpObj)->person->id);
        fprintf(filePointer,",%d.%d.%d", ((t_loan*) tmpObj)->loan_begin->day, ((t_loan*) tmpObj)->loan_begin->month, ((t_loan*) tmpObj)->loan_begin->year);
        fprintf(filePointer,",%d.%d.%d", ((t_loan*) tmpObj)->loan_end->day, ((t_loan*) tmpObj)->loan_end->month, ((t_loan*) tmpObj)->loan_end->year);
    }
    if (!strcmp(structure, "item")) {
        fprintf(filePointer,"%ld", ((t_item*) tmpObj)->id);
        fprintf(filePointer,",%ld", ((t_item*) tmpObj)->person->id);
        fprintf(filePointer,",%s", ((t_item*) tmpObj)->name);
        fprintf(filePointer,",%s", ((t_item*) tmpObj)->type);
        fprintf(filePointer,",%s", ((t_item*) tmpObj)->author);
    }
    if (!strcmp(structure, "person")) {
        fprintf(filePointer,"%ld", ((t_person*) tmpObj)->id);
        fprintf(filePointer,",%s", ((t_person*) tmpObj)->first_name);
        fprintf(filePointer,",%s", ((t_person*) tmpObj)->last_name);
        fprintf(filePointer,",%d.%d.%d", ((t_person*) tmpObj)->gebDatum->day, ((t_person*) tmpObj)->gebDatum->month, ((t_person*) tmpObj)->gebDatum->year);
    }
    fprintf(filePointer, "\n");
    
    return;
}

/* holt sich die Daten aus der <structure>.csv-Datei
 und gibt das erste Element, falls vorhanden, zurück */
void* addObjListDataToList(char* structure, t_person* firstPerson, t_item* firstItem, t_loan* firstLoan, void* lastObj)
{
    /* Deklarationen & Definitionen */
    FILE* filePointer;
    void* tmpObj = NULL;
    int first = 0;
    char buf[64];
    
    if ( !strcmp(structure, "item") && (!firstItem || !lastObj) ) return NULL;
    if ( !strcmp(structure, "person") && (!firstPerson || !lastObj) ) return NULL;
    if ( !strcmp(structure, "loan") && (!firstLoan || !lastObj) ) return NULL;
    
    sprintf(buf, "%s.csv", structure);
    filePointer = fopen(buf, "r");
    if (!filePointer) {
        sprintf(buf, "'%s.csv' konnte nicht ge&ouml;ffnet werden bei 'addObjListDataToList()'.", structure);
        warning(buf);
        return NULL;
    }
    
    while (1) {
        if (!strcmp(structure, "item")) tmpObj = getItemFromData(filePointer, firstPerson, firstItem);
        if (!strcmp(structure, "loan")) tmpObj = getLoanFromData(filePointer, firstPerson, firstItem);
        if (!strcmp(structure, "person")) tmpObj = getPersonFromData(filePointer);
        if (!tmpObj) {
            break;
        }
        if (!first) {
            if (!strcmp(structure, "item")) lastObj = firstItem = tmpObj;
            if (!strcmp(structure, "loan")) lastObj = firstLoan = tmpObj;
            if (!strcmp(structure, "person")) lastObj = firstPerson = tmpObj;
            first = 1;
        } else {
            if (!strcmp(structure, "item")) lastObj = addObjToList((t_item*) lastObj, (t_item*) tmpObj);
            if (!strcmp(structure, "loan")) lastObj = addObjToList((t_loan*) lastObj, (t_loan*) tmpObj);
            if (!strcmp(structure, "person")) lastObj = addObjToList((t_person*) lastObj, (t_person*) tmpObj);
        }
    }
    
    fclose(filePointer);
    
    if (!strcmp(structure, "item")) return firstItem;
    if (!strcmp(structure, "loan")) return firstLoan;
    if (!strcmp(structure, "person")) return firstPerson;
    
    return NULL;
}

/* Rückgabewert: Erstes Element der Liste */
void* deleteObjFromList(char* structure, void* tmpObj, void* firstObj)
{
    if (!testObj(tmpObj)) {
        printNotFound(structure);
        return firstObj; // das Objekt gibt s nicht, d.h. nichts tun
    }
    
    if (!((t_loan*) tmpObj)->before && ((t_loan*) tmpObj)->next) { // kein davor; beginn der liste
        firstObj = ((t_loan*) tmpObj)->next;
        ((t_loan*) tmpObj)->next->before = NULL;
    } else if (((t_loan*) tmpObj)->before && !((t_loan*) tmpObj)->next) { // nur kein element danach; ende der liste
        ((t_loan*) tmpObj)->before = NULL;
    } else if (((t_loan*) tmpObj)->before && ((t_loan*) tmpObj)->next) { // mittendrin
        ((t_loan*) tmpObj)->before->next = ((t_loan*) tmpObj)->next;
        ((t_loan*) tmpObj)->next->before = ((t_loan*) tmpObj)->before;
    } else { // bedeutet es gibt weder ein Element davor noch danach === komplette Liste ist nur ein Element
        firstObj = NULL;
    }
    
    freeObj(structure, tmpObj);
    
    return firstObj;
}

/* Legt den Speicher von einem Objekt wieder frei,
 es werden nicht die ->next oder ->before Zeiger beachtet. */
void freeObj(char* structure, void* tmpObj)
{
    if (!testObj(tmpObj)) {
        return;
    }
    
    if (!strcmp(structure, "item")) {
        free(((t_item*) tmpObj)->name);
        free(((t_item*) tmpObj)->type);
        free(((t_item*) tmpObj)->author);
    }
    if (!strcmp(structure, "person")) {
        free(((t_person*) tmpObj)->first_name);
        free(((t_person*) tmpObj)->last_name);
    }
    
    free(tmpObj);
    tmpObj = NULL;
    
    return;
}

void freeObjList(char* structure, void* firstObj)
{
    if (!testObj(firstObj)) {
        return;
    }
    
    t_loan* tmpObj = ((t_loan*) firstObj)->next;
    if (tmpObj) {
        while (((t_loan*) tmpObj)->next) {
            tmpObj = ((t_loan*) tmpObj)->next;
            freeObj(structure, ((t_loan*) tmpObj)->before);
        }
        freeObj(structure, tmpObj);
    }
    freeObj(structure, firstObj);
    
    return;
}

/* schiebt inputObj in die Liste nach beforeObj ein
 Rückgabewert: Ende der Liste! // was soll damit gemacht werden?
 */
void* addObjToList(void* beforeObj, void* inputObj)
{
    if (!testObj(inputObj)) {
        return NULL;
    }
    
    if (!beforeObj && inputObj) {
        return inputObj;
    }
    
    if (((t_loan*) beforeObj)->next) {
        ((t_loan*) beforeObj)->next->before = inputObj;
        ((t_loan*) inputObj)->next = ((t_loan*) beforeObj)->next;
    }
    ((t_loan*) inputObj)->before = beforeObj;
    ((t_loan*) beforeObj)->next = inputObj;
    
    return inputObj;
}

/* Gibt die hoechste Id zurueck*/ // eventuell so umwandeln, dass auch eventuell freie IDs vergeben werden von Personen die mal gelöscht wurden
unsigned long getMaxObjId(void* firstObj)
{
    /* Deklarationen & Definitionen */
    unsigned long curr;
    t_loan* tmpObj = firstObj;
    
    if (!testObj(firstObj)) {
        return 0;
    }
    
    curr = tmpObj->id;
    
    while (tmpObj) {
        if (curr < tmpObj->id) {
            curr = tmpObj->id;
        }
        tmpObj = tmpObj->next;
    }
    
    return curr;
}

/* Gibt die letzte Id zurueck */
unsigned long getLastObjId(void* firstObj)
{
    /* Definitionen */
    t_loan* tmpObj = firstObj;
    
    if (!testObj(firstObj)) {
        return 0;
    }
    
    while (tmpObj->next) {
        tmpObj = tmpObj->next;
    }
    
    return tmpObj->id;
}
