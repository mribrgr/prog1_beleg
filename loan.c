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

t_loan* getLoan(unsigned long identifier, t_loan* firstLoan)
{
    if (!testLoan(firstLoan)) {
        return NULL;
    }
    
    t_loan* currLoan = firstLoan;
    if (currLoan->id == identifier) {
        return currLoan;
    }
    currLoan = currLoan->next;
    while(currLoan) {
        if (currLoan->id == identifier) {
            return currLoan;
        }
        currLoan = currLoan->next;
    }
    
    return NULL;
}

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

/* Gibt die hoechste Id zurueck*/ // eventuell so umwandeln, dass auch eventuell freie IDs vergeben werden von Personen die mal gelöscht wurden
unsigned long getMaxLoanId(t_loan* firstLoan)
{
    /* Deklarationen & Definitionen */
    unsigned long curr;
    t_loan* tmpLoan = firstLoan;
    
    if (!testLoan(firstLoan)) {
        return 0;
    }
    
    curr = firstLoan->id;
    
    while (tmpLoan) {
        if (curr < tmpLoan->id) {
            curr = tmpLoan->id;
        }
        tmpLoan = tmpLoan->next;
    }
    
    return curr;
}

/* Gibt die letzte Id zurueck */
unsigned long getLastLoanId(t_loan* firstLoan)
{
    /* Definitionen */
    t_loan* tmpLoan = firstLoan;
    
    if (!testLoan(firstLoan)) {
        return 0;
    }
    
    while (tmpLoan->next) {
        tmpLoan = tmpLoan->next;
    }
    
    return tmpLoan->id;
}

/* Legt den Speicher von einer Person wieder frei,
 es werden nicht die ->next oder ->before Zeiger beachtet. */
void freeLoan(t_loan* tmpLoan)
{
    if (!testLoan(tmpLoan)) {
        return;
    }
    
    // evtl freeItems(tmpLoan->items)
    free(tmpLoan);
    tmpLoan = NULL;
    
    return;
}

void freeLoanList(t_loan* firstLoan)
{
    if (!testLoan(firstLoan)) {
        return;
    }
    
    t_loan* tmpLoan = firstLoan->next;
    if (tmpLoan) {
        while (tmpLoan->next) {
            tmpLoan = tmpLoan->next;
            freeLoan(tmpLoan->before);
        }
        freeLoan(tmpLoan);
    }
    freeLoan(firstLoan);
    
    return;
}

// sollte noch verbessert werden
int testLoan(t_loan* tmpLoan)
{
    if (tmpLoan) {
        if (tmpLoan->id) {
            return 1;
        }
    }
    
    return 0;
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
    
    testPerson(tmpPerson);
    testDate(loanBegin);
    testDate(loanEnd);
    for (i=0; i< (sizeof(items) / sizeof(t_item)); i++) {
        testItem(items[i]);
    }
    
    return 1;
}
