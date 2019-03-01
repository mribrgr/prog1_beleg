//
//  personListData.c
//  beleg
//
//  Created by mribrgr on 12.12.18.
//  Copyright © 2018 mribrgr. All rights reserved.
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

t_person* getPersonFromData(FILE* filePointer)
{
    char line[MAX_LINE_SIZE];
    t_person* tmpPerson = NULL;
    
    fgets(line, MAX_LINE_SIZE, filePointer);
    
    if (!testPersonDataLine(line)) {
        return NULL;
    }
    
    char* partId = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partFirstName = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partLastName = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partDate = malloc(sizeof(char) * MAX_LINE_SIZE);
    
    if (!partId || !partFirstName || !partLastName || !partId || !partDate)
        error("Storage couldn't get reserved in 'getOneDataToPerson()'!");
    
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
