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

/* schiebt inputItem in die Liste nach beforeLoan ein
 Rückgabewert: Ende der Liste! // was soll damit gemacht werden?
 */
t_item* addItemToList(t_item* beforeItem, t_item* inputItem)
{
    if (!testItem(inputItem)) {
        return NULL;
    }
    
    if (!beforeItem && inputItem) {
        return inputItem;
    }
    
    if (beforeItem->next) {
        beforeItem->next->before = inputItem;
        inputItem->next = beforeItem->next;
    }
    inputItem->before = beforeItem;
    beforeItem->next = inputItem;
    
    return inputItem;
}

/* Rückgabewert: Erstes Element der Liste */
t_item* deleteItemFromList(t_item* tmpItem, t_item* firstItem)
{
    if (!testItem(tmpItem)) {
        printNotFound("item");
        return firstItem; // das Item gibt s nicht, d.h. nichts tun
    }
    
    if (!tmpItem->before && tmpItem->next) { // kein davor; beginn der liste
        firstItem = tmpItem->next;
        tmpItem->next->before = NULL;
    } else if (tmpItem->before && !tmpItem->next) { // nur kein element danach; ende der liste
        tmpItem->before = NULL;
    } else if (tmpItem->before && tmpItem->next) { // mittendrin
        tmpItem->before->next = tmpItem->next;
        tmpItem->next->before = tmpItem->before;
    } else { // bedeutet es gibt weder ein Element davor noch danach === komplette Liste ist nur ein Element
        firstItem = NULL;
    }
    
    freeItem(tmpItem);
    
    return firstItem;
}

void writeItemToData(FILE* filePointer, t_item* tmpItem)
{
    fprintf(
        filePointer,
        "%ld,%ld,%s,%s,%s\n",
        tmpItem->id,
        tmpItem->person->id,
        tmpItem->name,
        tmpItem->type,
        tmpItem->author
    );
    
    return;
}

void writeItemListToData(t_item* firstItem)
{
    /* Deklarationen */
    FILE* filePointer;
    t_item* tmpItem;
    
    filePointer = fopen("item.csv", "w"); /* Beim Modus 'w' wird eine eventuelle schon vorhandene Datei ueberschrieben */
    if (filePointer == NULL) {
        error("Schreiben der 'item.csv' nicht moeglich bei 'writeItemListToData()'!");
    }
    
    if (testItem(firstItem)) {
        tmpItem = firstItem;
        writeItemToData(filePointer, tmpItem);
        while(tmpItem->next) {
            tmpItem = tmpItem->next;
            /* Stellt sicher, dass auch wirklich nur richtige Daten in die Datei geschrieben werden. */
            if (testItem(tmpItem)) {
                writeItemToData(filePointer, tmpItem);
            }
        }
    }
    
    fclose(filePointer);
    
    return;
}

void appendItemToData(t_item* tmpItem)
{
    /* Deklarationen */
    FILE* filePointer;
    
    if (!testItem(tmpItem)) {
        return;
    }
    
    filePointer = fopen("item.csv", "a");
    if (!filePointer) {
        error("&Ouml;ffnen der 'item.csv' nicht moeglich bei 'appendItemToData()'!");
    }
    writeItemToData(filePointer, tmpItem);
    fclose(filePointer);
    
    return;
}

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

/* holt sich die Daten aus der item.csv-Datei
 und gibt das erste Element, falls vorhanden, zurück */
t_item* addItemListDataToList(t_item* firstItem, t_item* lastItem, t_person* firstPerson)
{
    /* Deklarationen & Definitionen */
    FILE* filePointer;
    t_item* tmpItem;
    int first = 0;
    
    if (!firstItem || !lastItem) {
        return NULL;
    }
    
    filePointer = fopen("item.csv", "r");
    if (!filePointer) {
        warning("'item.csv' konnte nicht ge&ouml;ffnet werden bei 'addItemListDataToList()'.");
        return NULL;
    }
    while(1) {
        tmpItem = getItemFromData(filePointer, firstPerson, firstItem);
        if (!tmpItem) {
            break;
        }
        if (!first) {
            lastItem = firstItem = tmpItem;
            first = 1;
        } else {
            lastItem = addItemToList(lastItem, tmpItem);
        }
    }
    fclose(filePointer);
    
    return firstItem;
}
