//
//  loan.c
//  beleg
//
//  Created by mribrgr on 29.12.18.
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

t_loan *createLoan(t_person* tmpPerson, t_date* loanBegin, t_date* loanEnd, t_item *item, unsigned long identifier)
{
    if (!tmpPerson || !item)
        error("Invalid parameters at 'createLoan()'!");
    
    t_loan *tmpLoan = malloc(sizeof(t_loan));
    if (!tmpLoan)
        error("Storage couldn't get reserved in 'createLoan()'!");
    
    tmpLoan->id = identifier;
    tmpLoan->person = tmpPerson;
    tmpLoan->loan_begin = loanBegin;
    tmpLoan->loan_end = loanEnd;
    tmpLoan->item = item;
    tmpLoan->before = tmpLoan->next = NULL;
    
    return tmpLoan;
}

int testLoanDataLine(char* line)
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
        if ((diff == 0 && countComma == 1) || (diff == 1 && i != 1 && last != 1))
            return 0;
    }
    if (countComma == 3 && countDot == 4)
        return 1;
    
    return 0;
}

int testLoanObj(t_loan *firstLoan, char *structure, unsigned long identifier)
{
    if (!testObj(firstLoan)) return 0;
    
    if (!strcmp(structure, "item"))
        if (firstLoan->item->id == identifier) return 0;
    if (!strcmp(structure, "person"))
        if (firstLoan->person->id == identifier) return 0;
    
    t_loan *tmpObj = ((t_loan *) firstLoan)->next;
    
    while (tmpObj) {
        if (!strcmp(structure, "item"))
            if (firstLoan->item->id == identifier) return 0;
        if (!strcmp(structure, "person"))
            if (firstLoan->person->id == identifier) return 0;
        tmpObj = tmpObj->next;
    }
    
    return 1;
}
