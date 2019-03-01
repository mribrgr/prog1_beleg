//
//  loanListData.c
//  beleg
//
//  Created by mribrgr on 01.01.19.
//  Copyright © 2019 mribrgr. All rights reserved.
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

t_loan* getLoanFromData(FILE* filePointer, t_person* firstPerson, t_item* firstItem)
{
    char line[MAX_LINE_SIZE];
    
    t_loan* tmpLoan = malloc(sizeof(t_loan));
    if (!tmpLoan)
        error("Storage couldn't get reserved in 'getLoanFromData()'!");
    
    fgets(line, MAX_LINE_SIZE, filePointer);
    
    if (!testLoanDataLine(line)) {
        return NULL;
    }
    
    char* partId = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partPersonId = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partLoanBegin = malloc(sizeof(char) * MAX_LINE_SIZE);
    char* partLoanEnd = malloc(sizeof(char) * MAX_LINE_SIZE);
    
    if (!partId || !partPersonId || !partLoanBegin || !partLoanEnd)
        error("Storage couldn't get reserved in 'getLoanFromData()'!");
    
    strcpy(partId, strtok(line, ",\0"));
    strcpy(partPersonId, strtok(NULL, ",\0"));
    strcpy(partLoanBegin, strtok(NULL, ",\0"));
    strcpy(partLoanEnd, strtok(NULL, ",\0"));
    
    t_item *tmpItem = getItemByPerson(atol(partPersonId), firstItem);
    if (!tmpItem) {
        error("Item couldn't get found by person in 'getLoanFromData()'!");
    }
    
    tmpLoan = createLoan(
        getObj(atol(partPersonId), firstPerson),
        getDateFromString(partLoanBegin),
        getDateFromString(partLoanEnd),
        tmpItem,
        atol(partId)
    );
    
    free(partId);
    free(partPersonId);
    free(partLoanBegin);
    free(partLoanEnd);
    
    return tmpLoan;
}
