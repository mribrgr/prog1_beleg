//
//  print.c
//  beleg
//
//  Created by Mauritius Berger on 26.12.18.
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

void printError(char* msg)
{
    printf("Fehler: %s<br />", msg);
    return;
}

void printWarning(char* msg)
{
    printf("Warnung: %s<br />", msg);
    return;
}

void printPersonWithType(t_person* tmpPerson, char* type)
{
    if (!testObj(tmpPerson)) {
        error("Fehlerhafte Parameter&uuml;bergabe bei 'printPersonWithType()'!");
    }
    
    if (strcmp(type, "")) {
        printf(
            "%s%s%s%s%s%ld%s%s%s%ld%s%s%s%s%s%s%s%s%02d.%02d.%04d%s%s",
            "<tr>",
                "<td style='text-align:right;'>",
                    "<input type='", type, "' name='personId' value='", tmpPerson->id, "'>",
                "</td>",
                "<td style='text-align:right;'>",
                    tmpPerson->id,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpPerson->first_name,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpPerson->last_name,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpPerson->gebDatum->day ,tmpPerson->gebDatum->month, tmpPerson->gebDatum->year,
                "</td>",
            "</tr>"
        );
    } else {
        printf(
            "%s%s%10ld%s%s%15s%s%s%15s%s%s%02d.%02d.%04d%s%s",
            "<tr>",
                "<td style='text-align:right;'>",
                    tmpPerson->id,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpPerson->first_name,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpPerson->last_name,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpPerson->gebDatum->day ,tmpPerson->gebDatum->month, tmpPerson->gebDatum->year,
                "</td>",
            "</tr>"
        );
    }
    
    return;
}

void printAddSuccess(char* string)
{
    printf("%s added.<br />", string); // durch html eintauschen
    
    return;
}

void printListEmpty(char* string)
{
    printf("%s-list is empty!<br />", string);
    
    return;
}

void printNotFound(char* string)
{
    printf("%s was not found.<br />", string);
    
    return;
}

void printLoanWithType(t_loan* tmpLoan, char* type)
{ // wie siehts mit den items aus?
    if (!testObj(tmpLoan)) {
        error("Fehlerhafte Parameter&uuml;bergabe bei 'printLoan()'!");
    }
    
    if (strcmp(type, "")) {
        printf(
        "%s%s%s%s%s%ld%s%s%s%ld%s%s%ld%s%s%02d.%02d.%04d%s%s%02d.%02d.%04d%s%s",
        "<tr>",
            "<td style='text-align:right;'>",
               "<input type='", type, "' name='personId' value='", tmpLoan->id, "'>",
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->id,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->person->id,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->loan_begin->day, tmpLoan->loan_begin->month, tmpLoan->loan_begin->year,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->loan_end->day, tmpLoan->loan_end->month, tmpLoan->loan_end->year,
            "</td>",
        "</tr>"
        );
    } else {
        printf(
        "%s%s%ld%s%s%ld%s%s%02d.%02d.%04d%s%s%02d.%02d.%04d%s%s",
        "<tr>",
            "<td style='text-align:right;'>",
               tmpLoan->id,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->person->id,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->loan_begin->day, tmpLoan->loan_begin->month, tmpLoan->loan_begin->year,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->loan_end->day, tmpLoan->loan_end->month, tmpLoan->loan_end->year,
            "</td>",
        "</tr>"
        );
    }
    
    return;
}

void printItemWithType(t_item* tmpItem, char* type)
{
    if (!testObj(tmpItem)) {
        error("Fehlerhafte Parameter&uuml;bergabe bei 'printItemWithType()'!");
    }
    
    if (strcmp(type, "")) {
        printf(
            "%s%s%s%s%s%ld%s%s%s%ld%s%s%ld%s%s%s%s%s%s%s%s%s%s%s",
            "<tr>",
                "<td style='text-align:right;'>",
                    "<input type='", type, "' name='personId' value='", tmpItem->id, "'>",
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->id,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->person->id,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->name,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->type,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->author,
                "</td>",
            "</tr>"
        );
    } else {
        printf(
            "%s%s%ld%s%s%ld%s%s%s%s%s%s%s%s%s%s%s",
            "<tr>",
                "<td style='text-align:right;'>",
                    tmpItem->id,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->person->id,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->name,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->type,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->author,
                "</td>",
            "</tr>"
        );
    }
    
    return;
}
