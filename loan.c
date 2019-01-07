//
//  loan.c
//  beleg
//
//  Created by Mauritius Berger on 29.12.18.
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

t_loan* createLoan(t_person* tmpPerson, t_date* loanBegin, t_date* loanEnd, t_item** items, unsigned long identifier)
{
    t_loan* tmpLoan = malloc(sizeof(t_loan));
    if (!tmpLoan) {
        error("Speicherreservierung fehlgeschlagen bei 'createLoan()'!");
    }
    
    tmpLoan->id = identifier;
    tmpLoan->person = tmpPerson;
    tmpLoan->loan_begin = loanBegin;
    tmpLoan->loan_end = loanEnd;
    tmpLoan->items = items;
    tmpLoan->before = tmpLoan->next = NULL;
    
    return tmpLoan;
}

/* Guckt ob die angegebene Linie der Datei gültig ist */
int testLoanDataLine(char* line)
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
    if (countComma == 3 && countDot == 4) {
        return 1;
    }
    
    return 0;
}

int testInputNewLoan(t_person* tmpPerson, t_date* loanBegin, t_date* loanEnd, t_item** items)
{
    int i;
    
    testObj(tmpPerson);
    testDate(loanBegin);
    testDate(loanEnd);
    for (i=0; i< (sizeof(items) / sizeof(t_item)); i++) {
        testObj(items[i]);
    }
    
    return 1;
}
