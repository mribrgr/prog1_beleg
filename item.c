//
//  item.c
//  beleg
//  46139
//  Created by Mauritius Berger on 31.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "date.h"
#include "item.h"
#include "person.h"
#include "loan.h"

t_item *createItem(char *name, char *type, char *author, unsigned long identifier)
{
    t_item *tmpItem = malloc(sizeof(t_item));
    if (!tmpItem) {
        error("Storage couldn't get reserved in 'createItem()'!");
    }
    
    tmpItem->id = identifier;
    tmpItem->person = NULL;
    tmpItem->next = tmpItem->before = NULL;
    tmpItem->name = name;
    tmpItem->type = type;
    tmpItem->author = author;
    
    return tmpItem;
}

int testItemDataLine(char *line)
{
    int i, countComma = 0, countDot = 0, diff = 0, last = 0;
    
    char *temp = checkString(line, MODE_COMMA_DOT);
    if (!strcmp(temp, "")) return 0;
    
    for (i=0; i<64 && line[i] != '\n'; i++) {
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

t_item *getItemByPerson(unsigned long personId, t_item *firstItem)
{
    t_item *currItem = firstItem;
    
    if (!currItem) {
        error("Invalid parameters to 'getItemByPerson()'!");
    }
    
    if (currItem->person) {
        if (currItem->person->id == personId) {
            return currItem;
        }
    }
    currItem = currItem->next;
    while (currItem) {
        if (currItem->person) {
            if (currItem->person->id == personId) {
                return currItem;
            }
        }
        currItem = currItem->next;
    }
    
    return NULL;
}
