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

t_item** getItemsFromItemList(unsigned long personId, t_item* firstItem)
{ // Problem: es wird speicherplatz für Items erstellt, die schon Speicher reserviert bekommen haben
    /* Definitionen */
    t_item** tmpItems = NULL;
    
    if (!testObj(firstItem)) {
        return NULL;
    }
    
    tmpItems = malloc(sizeof(t_item*));
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
            tmpItems = realloc(tmpItems, sizeof(tmpItems) + sizeof(t_item*));
            if (!tmpItems) {
                error("Speicherreservierung fehlgeschlagen bei 'getItemsFromString()'!");
            }
            tmpItems[sizeof(tmpItems) / sizeof(t_item*)] = currItem;
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
