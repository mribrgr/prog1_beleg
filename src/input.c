//
//  input.c
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

void inputLoan(t_loan *firstLoan, t_person *tmpPerson, t_item *tmpItem, int loan_begin_day, int loan_begin_month, int loan_begin_year, int loan_end_day, int loan_end_month, int loan_end_year, t_item *firstItem)
{
    if (!tmpPerson || !tmpItem || !testInputNewLoan(loan_begin_day, loan_begin_month, loan_begin_year, loan_end_day, loan_end_month, loan_end_year)) {
        error("Invalid input given to 'inputLoan()'!");
    }
    
    t_loan *tmpLoan = NULL;
    
    tmpLoan = createLoan(tmpPerson, createDate(loan_begin_day, loan_begin_month, loan_begin_year), createDate(loan_end_day, loan_end_month, loan_end_year), tmpItem, getMaxObjId(firstLoan) + 1);
    addObjToList((t_loan *) getObj(getLastObjId(firstLoan), firstLoan), tmpLoan);
    if (!testObj(firstLoan)) {
        firstLoan = tmpLoan;
    }
    appendObjToData("loan", tmpLoan);
    
    if (!testObj(tmpLoan)) error("loan couldn't get added at 'inputLoan()'!");
    else printAddSuccess("loan");
    
    tmpItem->person = tmpPerson;
    
    writeObjListToData("item", firstItem);
    
    return;
}

int testInputNewLoan(int loan_begin_day, int loan_begin_month, int loan_begin_year, int loan_end_day, int loan_end_month, int loan_end_year)
{
    if (!testInputDate(loan_begin_day, loan_begin_month, loan_begin_year)) {
        return 0;
    }
    if (!testInputDate(loan_end_day, loan_end_month, loan_end_year)) {
        return 0;
    }
    if (loan_begin_day > loan_end_day && loan_begin_month == loan_end_month && loan_begin_year == loan_end_year) {
        return 0;
    }
    if (loan_begin_month > loan_end_month && loan_begin_year == loan_end_year) {
        return 0;
    }
    if (loan_begin_year > loan_end_year) {
        return 0;
    }
    return 1;
}

t_person *inputPerson(t_person *firstPerson, char *vorname, char *nachname, int tag, int monat, int jahr)
{
    t_person *tmpPerson = NULL;
    
    if (!testInputNewPerson(vorname, nachname, tag, monat, jahr))
        error("Too few inputs for the person!");
    
    vorname = checkString(vorname, MODE_PERCENT_PLUS);
    nachname = checkString(nachname, MODE_PERCENT_PLUS);
    
    tmpPerson = createPerson(vorname, nachname, createDate(tag, monat, jahr), getMaxObjId(firstPerson) + 1);
    addObjToList((t_person*) getObj(getLastObjId(firstPerson), firstPerson), tmpPerson);
    if (!testObj(firstPerson))
        firstPerson = tmpPerson;
    appendObjToData("person", tmpPerson);
    
    if (!testObj(tmpPerson)) error("person couldn't get added at 'inputPerson()'!");
    else printAddSuccess("person");
    
    return tmpPerson;
}

int testInputNewPerson(char *vorname, char *nachname, int tag, int monat, int jahr)
{
    if (!testName(vorname) || !testName(nachname))
        return 0;
    if (!testInputDate(tag, monat, jahr))
        return 0;
    
    return 1;
}

t_item *inputItem(t_item *firstItem, char *name, char *type, char *author)
{
    t_item *tmpItem = NULL;
    
    if (!testInputNewItem(name, type, author))
        error("Eingabe des Mediums ist falsch bei 'inputItem()'!");
    
    name = checkString(name, MODE_PERCENT_PLUS);
    type = checkString(type, MODE_PERCENT_PLUS);
    author = checkString(author, MODE_PERCENT_PLUS);
    
    tmpItem = createItem(name, type, author, getMaxObjId(firstItem) + 1);
    addObjToList((t_item *) getObj(getLastObjId(firstItem), firstItem), tmpItem);
    if (!testObj(firstItem))
        firstItem = tmpItem;
    appendObjToData("item", tmpItem);
    
    if (!testObj(tmpItem))
        error("Medium konnte nicht eingelesen werden bei 'inputItem()'!");
    else
        printAddSuccess("item");
    
    return tmpItem;
}

int testInputNewItem(char *name, char *type, char *author)
{
    if (strlen(name) > 0 && strlen(type) > 0)
        return 1;
    
    return 0;
}

int testInputDate(int tag, int monat, int jahr)
{
    if (tag > 0 && tag <= 31 && monat > 0 && monat <= 12 && jahr > 1900 && jahr <= 2050)
        return 1;
    
    return 0;
}

int testName(char *name)
{
    if (strlen(name) > 0)
        return 1;
    
    return 0;
}
