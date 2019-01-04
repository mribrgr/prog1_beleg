//
//  date.c
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

t_date* createDate(int day, int month, int year)
{
    t_date* tmpDate = malloc(sizeof(t_date));

    if (tmpDate == NULL) {
        error("Speicherzuweisung für Datum fehlgeschlagen!");
    }

    tmpDate->day = day;
    tmpDate->month = month;
    tmpDate->year = year;

    return tmpDate;
}

t_date* getDateFromString(char* string)
{
    int i, tmp[3];
    
    tmp[0] = atoi(strtok(string, ".\0"));
    for (i=1; i<3 && tmp[i-1]; i++) {
        tmp[i] = atoi(strtok(NULL, ".\0"));
    }
    if (i<3) {
        error("Falsche Anzahl bei Datumszerlegung bei 'getDateFromString()'!");
    }
    
    return createDate(tmp[0], tmp[1], tmp[2]);
}

int testDate(t_date* tmpDate)
{
    if (!tmpDate) {
        return 0;
    }
    if (tmpDate->day > 0 && tmpDate->day <= 31 && tmpDate->month > 0 && tmpDate->month <= 12 && tmpDate->year > 1900 && tmpDate->year <= 2050) {
        return 1;
    }
    
    return 0;
}
