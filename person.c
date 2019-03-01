//
//  person.c
//  beleg
//  46139
//  Created by Mauritius Berger on 12.12.18.
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

t_person* createPerson(char* firstName, char* lastName, t_date* gebDatum, unsigned long identifier)
{
    t_person* tmpPerson = malloc(sizeof(t_person));
    if (!tmpPerson) {
        error("Storage couldn't get reserved in 'createPerson()'!");
    }
    
    tmpPerson->id = identifier;
    tmpPerson->before = tmpPerson->next = NULL;
    tmpPerson->first_name = firstName;
    tmpPerson->last_name = lastName;
    tmpPerson->gebDatum = gebDatum;
    
    return tmpPerson;
}

int testPersonDataLine(char* line)
{
    int i, countComma = 0, countDot = 0, diff = 0, last = 0;
    
    char *temp = checkString(line, MODE_COMMA_DOT);
    if (!strcmp(temp, "")) return 0;
    
    for (i=0; i<MAX_SIZE_STRING && line[i] != '\n'; i++) {
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
        if ((diff == 0 && countComma == 1) || (diff == 1 && i != 1 && last != 1))
            return 0;
    }
    if (countComma == 3 && countDot == 2)
        return 1;
    
    return 0;
}
