//
//  date.c
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

t_date* createDate(int day, int month, int year)
{
    t_date* tmpDate = malloc(sizeof(t_date));

    if (!tmpDate)
        error("Storage couldn't get reserved in 'createDate()'!");

    tmpDate->day = day;
    tmpDate->month = month;
    tmpDate->year = year;

    return tmpDate;
}

t_date* getDateFromString(char* string)
{
    int i, tmp[3];
    
    tmp[0] = atoi(strtok(string, ".\0"));
    for (i=1; i<3 && tmp[i-1]; i++)
        tmp[i] = atoi(strtok(NULL, ".\0"));
    if (i<3)
        error("Invalid input given in 'getDateFromString()'!");
    
    return createDate(tmp[0], tmp[1], tmp[2]);
}
