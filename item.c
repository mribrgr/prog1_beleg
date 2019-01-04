//
//  item.c
//  beleg
//
//  Created by Mauritius Berger on 31.12.18.
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

t_item* getItem(unsigned long identifier, t_item* firstItem)
{
    if (!testItem(firstItem)) {
        return NULL;
    }
    
    t_item* currItem = firstItem;
    if (currItem->id == identifier) {
        return currItem;
    }
    currItem = currItem->next;
    while(currItem) {
        if (currItem->id == identifier) {
            return currItem;
        }
        currItem = currItem->next;
    }
    
    return NULL;
}

t_item* createItem(char* name, char* type, char* author, unsigned long identifier)
{
    t_item* tmpItem = malloc(sizeof(t_item));
    if (!tmpItem) {
        error("Speicherreservierung fehlgeschlagen bei 'createItem()'!");
    }
    
    tmpItem->id = identifier;
    tmpItem->person = NULL;
    tmpItem->person->id = 0;
    tmpItem->next = tmpItem->before = NULL;
    tmpItem->name = name;
    tmpItem->type = type;
    tmpItem->author = author;
    
    return tmpItem;
}

/* Gibt die hoechste Id zurueck*/ // eventuell so umwandeln, dass auch eventuell freie IDs vergeben werden von Personen die mal gelöscht wurden
unsigned long getMaxItemId(t_item* firstItem)
{
    /* Deklarationen & Definitionen */
    unsigned long curr;
    t_item* tmpItem = firstItem;
    
    if (!testItem(firstItem)) {
        return 0;
    }
    
    curr = firstItem->id;
    
    while (tmpItem) {
        if (curr < tmpItem->id) {
            curr = tmpItem->id;
        }
        tmpItem = tmpItem->next;
    }
    
    return curr;
}

/* Gibt die letzte Id zurueck */
unsigned long getLastItemId(t_item* firstItem)
{
    /* Definitionen */
    t_item* tmpItem = firstItem;
    
    if (!testItem(firstItem)) {
        return 0;
    }
    
    while (tmpItem->next) {
        tmpItem = tmpItem->next;
    }
    
    return tmpItem->id;
}

/* Legt den Speicher von einer Person wieder frei,
 es werden nicht die ->next oder ->before Zeiger beachtet. */
void freeItem(t_item* tmpItem)
{
    if (!testItem(tmpItem)) {
        return;
    }
    
    free(tmpItem->name);
    free(tmpItem->type);
    free(tmpItem->author);
    free(tmpItem);
    tmpItem = NULL;
    
    return;
}

void freeItemList(t_item* firstItem)
{
    if (!testItem(firstItem)) {
        return;
    }
    
    t_item* tmpItem = firstItem->next;
    if (tmpItem) {
        while (tmpItem->next) {
            tmpItem = tmpItem->next;
            freeItem(tmpItem->before);
        }
        freeItem(tmpItem);
    }
    freeItem(firstItem);
    
    return;
}

t_item** getItemsFromItemList(unsigned long personId, t_item* firstItem)
{ // Problem: es wird speicherplatz für Items erstellt, die schon Speicher reserviert bekommen haben
    /* Definitionen */
    t_item** tmpItems = NULL;
    
    if (!testItem(firstItem)) {
        return NULL;
    }
    
    tmpItems = malloc(sizeof(t_item));
    if (!tmpItems) {
        error("Speicherreservierung fehlgeschlagen bei 'getItemsFromString()'!");
    }
    
    t_item* currItem = firstItem;
    if (currItem->person->id == personId) {
        tmpItems[0] = currItem;
    }
    currItem = currItem->next;
    while (currItem) {
        if (currItem->person->id == personId) {
            tmpItems = realloc(tmpItems, sizeof(tmpItems) + sizeof(t_item));
            if (!tmpItems) {
                error("Speicherreservierung fehlgeschlagen bei 'getItemsFromString()'!");
            }
            tmpItems[sizeof(tmpItems) / sizeof(t_item)] = currItem;
        }
        currItem = currItem->next;
    }
    
    return tmpItems;
}

// evtl. unused
int countItemsWithPersonId(unsigned long personId, t_item* firstItem)
{
    int count = 0;
    
    t_item* currItem = firstItem;
    if (currItem->person->id == personId) {
        count++;
    }
    currItem = currItem->next;
    while (currItem) {
        if (currItem->person->id == personId) {
            count++;
        }
        currItem = currItem->next;
    }
    
    return count;
}

int testItem(t_item* tmpItem)
{
    if (tmpItem) {
        if (tmpItem->id) {
            return 1;
        }
    }
    
    return 0;
}

/* Guckt ob die angegebene Linie der Datei gültig ist */
int testItemDataLine(char* line)
{
    /* Deklarationen & Definitionen */
    int i, countComma = 0, countDot = 0, diff = 0, last = 0;
    
    for (i=0; i<64 && line[i] != '\n'; i++) {
        if (!isalnum(line[i]) && line[i] != ',' && line[i] != '.') {
            return 0;
        }
        if (line[i] == ',') {
            diff = i - last;
            last = i;
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
    if (countComma == 4) {
        return 1;
    }
    
    return 0;
}
