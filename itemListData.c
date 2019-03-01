//
//  itemListData.c
//  beleg
//  46139
//  Created by Mauritius Berger on 02.01.19.
//  Copyright © 2019 Mauritius Berger. All rights reserved.
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

t_item* getItemFromData(FILE* filePointer, t_person* firstPerson, t_item* firstItem)
{
    char line[MAX_LINE_SIZE];
    
    t_item* tmpItem = malloc(sizeof(t_item));
    if (!tmpItem)
        error("Storage couldn't get reserved in 'getItemFromData()'!");
    
    fgets(line, MAX_LINE_SIZE, filePointer);
    
    if (!testItemDataLine(line)) return NULL;
    
    char* partId = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partPersonId = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partName = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partType = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partAuthor = malloc(sizeof(char) * MAX_LINE_SIZE);
    
    if (!partId || !partPersonId || !partName || !partType || !partAuthor)
        error("Storage couldn't get reserved in 'getItemFromData()'!");
    
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
    
    if (atol(partPersonId) > 0) tmpItem->person = (t_person *) getObj(atol(partPersonId), firstPerson);
    
    free(partId);
    free(partPersonId);
    
    return tmpItem;
}
