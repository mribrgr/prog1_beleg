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

/* schiebt inputLoan in die Liste nach beforeLoan ein
 Rückgabewert: Ende der Liste! // was soll damit gemacht werden?
 */
t_loan* addLoanToList(t_loan* beforeLoan, t_loan* inputLoan)
{
    if (!testLoan(inputLoan)) {
        return NULL;
    }
    
    if (!beforeLoan && inputLoan) {
        return inputLoan;
    }
    
    if (beforeLoan->next) {
        beforeLoan->next->before = inputLoan;
        inputLoan->next = beforeLoan->next;
    }
    inputLoan->before = beforeLoan;
    beforeLoan->next = inputLoan;
    
    return inputLoan;
}

/* Rückgabewert: Erstes Element der Liste */
t_loan* deleteLoanFromList(t_loan* tmpLoan, t_loan* firstLoan)
{
    if (!testLoan(tmpLoan)) {
        printNotFound("loan");
        return firstLoan; // die Person gibt s nicht, d.h. nichts tun
    }
    
    if (!tmpLoan->before && tmpLoan->next) { // kein davor; beginn der liste
        firstLoan = tmpLoan->next;
        tmpLoan->next->before = NULL;
    } else if (tmpLoan->before && !tmpLoan->next) { // nur kein element danach; ende der liste
        tmpLoan->before = NULL;
    } else if (tmpLoan->before && tmpLoan->next) { // mittendrin
        tmpLoan->before->next = tmpLoan->next;
        tmpLoan->next->before = tmpLoan->before;
    } else { // bedeutet es gibt weder ein Element davor noch danach === komplette Liste ist nur ein Element
        firstLoan = NULL;
    }
    
    freeLoan(tmpLoan);
    
    return firstLoan;
}

void writeLoanToData(FILE* filePointer, t_loan* tmpLoan)
{
    fprintf(
        filePointer,
        "%ld,%ld,%d.%d.%d,%d.%d.%d\n",
        tmpLoan->id,
        tmpLoan->person->id,
        tmpLoan->loan_begin->day, tmpLoan->loan_begin->month, tmpLoan->loan_begin->year,
        tmpLoan->loan_end->day, tmpLoan->loan_end->month, tmpLoan->loan_end->year
    );
    
    return;
}

void writeLoanListToData(t_loan* firstLoan)
{
    /* Deklarationen */
    FILE* filePointer;
    t_loan* tmpLoan;
    
    filePointer = fopen("loan.csv", "w"); /* Beim Modus 'w' wird eine eventuelle schon vorhandene Datei ueberschrieben */
    if (filePointer == NULL) {
        error("Schreiben der 'loan.csv' nicht moeglich bei 'deleteLoanFromData()'!");
    }
    
    if (testLoan(firstLoan)) {
        tmpLoan = firstLoan;
        writeLoanToData(filePointer, tmpLoan);
        while(tmpLoan->next) {
            tmpLoan = tmpLoan->next;
            /* Stellt sicher, dass auch wirklich nur richtige Daten in die Datei geschrieben werden. */
            if (testLoan(tmpLoan)) {
                writeLoanToData(filePointer, tmpLoan);
            }
        }
    }
    
    fclose(filePointer);
    
    return;
}

void appendLoanToData(t_loan* tmpLoan)
{
    /* Deklarationen */
    FILE* filePointer;
    
    if (!testLoan(tmpLoan)) {
        return;
    }
    
    filePointer = fopen("loan.csv", "a");
    if (!filePointer) {
        error("&Ouml;ffnen der 'loan.csv' nicht moeglich bei 'appendLoanToData()'!");
    }
    writeLoanToData(filePointer, tmpLoan);
    fclose(filePointer);
    
    return;
}

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
        getPerson(atol(partPersonId), firstPerson),
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

/* holt sich die Daten aus der loan.csv-Datei
 und gibt das erste Element, falls vorhanden, zurück */
t_loan* addLoanListDataToList(t_loan* firstLoan, t_loan* lastLoan, t_person* firstPerson, t_item* firstItem)
{
    /* Deklarationen & Definitionen */
    FILE* filePointer;
    t_loan* tmpLoan;
    int first = 0;
    
    if (!firstLoan || !lastLoan) {
        return NULL;
    }
    
    filePointer = fopen("loan.csv", "r");
    if (!filePointer) {
        warning("'loan.csv' konnte nicht ge&ouml;ffnet werden bei 'addLoanListDataToList()'.");
        return NULL;
    }
    while(1) {
        tmpLoan = getLoanFromData(filePointer, firstPerson, firstItem);
        if (!tmpLoan) {
            break;
        }
        if (!first) {
            lastLoan = firstLoan = tmpLoan;
            first = 1;
        } else {
            lastLoan = addLoanToList(lastLoan, tmpLoan);
        }
    }
    fclose(filePointer);
    
    return firstLoan;
}
