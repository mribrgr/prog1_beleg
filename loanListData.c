//
//  loanList.c
//  beleg
//
//  Created by Mauritius Berger on 01.01.19.
//  Copyright © 2019 Mauritius Berger. All rights reserved.
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

/* parst die Daten aus dem eingegebenen File und gibt die Daten als Loan zurück */
t_loan* getLoanFromData(FILE* filePointer, t_person* firstPerson, t_item* firstItem)
{
    /* Deklarationen & Definitionen */
    char line[64];
    
    t_loan* tmpLoan = malloc(sizeof(t_loan));
    if (!tmpLoan) {
        error("Speicherreservierungen fehlgeschlagen bei 'getOneLoanToPerson()'!");
    }
    
    fgets(line, 64, filePointer);
    
    if (!testLoanDataLine(line)) {
        return NULL; // eigentlich sollte er nur abbrechen wenn das file zu ende ist und nicht beim ersten ungültigen
    }
    
    char* partId = malloc(sizeof(char) * 64);
    char* partPersonId = malloc(sizeof(char) * 64);
    char* partLoanBegin = malloc(sizeof(char) * 64);
    char* partLoanEnd = malloc(sizeof(char) * 64);
    
    if (!partId || !partPersonId || !partLoanBegin || !partLoanEnd) {
        error("Speicher konnte nicht reserviert werden bei 'getOneLoanDataToLoan()'!");
    }
    
    strcpy(partId, strtok(line, ",\0"));
    strcpy(partPersonId, strtok(NULL, ",\0"));
    strcpy(partLoanBegin, strtok(NULL, ",\0"));
    strcpy(partLoanEnd, strtok(NULL, ",\0"));
    
    tmpLoan = createLoan(
        getObj(atol(partPersonId), firstPerson),
        getDateFromString(partLoanBegin),
        getDateFromString(partLoanEnd),
        getItemsFromItemList(atol(partPersonId), firstItem),
        atol(partId)
    );
    
    free(partId);
    free(partPersonId);
    free(partLoanBegin);
    free(partLoanEnd);
    
    return tmpLoan;
}
