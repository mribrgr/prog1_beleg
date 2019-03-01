//
//  print.c
//  beleg
//
//  Created by mribrgr on 26.12.18.
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

void printError(char *msg)
{
    printf("Error: %s<br />", msg);
    return;
}

void printWarning(char *msg)
{
    printf("Warning: %s<br />", msg);
    return;
}

void printPersonWithType(t_person *tmpPerson, char *type)
{
    if (!testObj(tmpPerson)) {
        error("Invalid input given to 'printPersonWithType()'!");
    }
    
    if (strcmp(type, "")) {
        printf(
            "%s%s%s%s%ld%s%s%s%ld%s%s%s%s%s%s%s%s%02d.%02d.%04d%s",
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
            "</td>"
        );
    } else {
        printf(
            "%s%10ld%s%s%15s%s%s%15s%s%s%02d.%02d.%04d%s",
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
            "</td>"
        );
    }
    
    return;
}

void printAddSuccess(char *string)
{
    printf("%s added.<br />", string);
    
    return;
}

void printListEmpty(char *string)
{
    printf("%s-list is empty!<br />", string);
    
    return;
}

void printLoanWithType(t_loan *tmpLoan, char *type)
{
    if (!testObj(tmpLoan)) {
        error("Invalid input given to 'printLoanWithType()'!");
    }
    
    if (strcmp(type, "")) {
        printf(
            "%s%s%s%s%ld%s%s%s%ld%s%s%ld%s%s%ld%s%s%02d.%02d.%04d%s%s%02d.%02d.%04d%s",
            "<td style='text-align:right;'>",
               "<input type='", type, "' name='loanId' value='", tmpLoan->id, "'>",
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->id,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->person->id,
            "</td>",
           "<td style='text-align:right;'>",
               tmpLoan->item->id,
           "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->loan_begin->day, tmpLoan->loan_begin->month, tmpLoan->loan_begin->year,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->loan_end->day, tmpLoan->loan_end->month, tmpLoan->loan_end->year,
            "</td>"
        );
    } else {
        printf(
            "%s%ld%s%s%ld%s%s%ld%s%s%02d.%02d.%04d%s%s%02d.%02d.%04d%s",
            "<td style='text-align:right;'>",
               tmpLoan->id,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->person->id,
            "</td>",
           "<td style='text-align:right;'>",
               tmpLoan->item->id,
           "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->loan_begin->day, tmpLoan->loan_begin->month, tmpLoan->loan_begin->year,
            "</td>",
            "<td style='text-align:right;'>",
               tmpLoan->loan_end->day, tmpLoan->loan_end->month, tmpLoan->loan_end->year,
            "</td>"
        );
    }
    
    return;
}

void printItemWithType(t_item *tmpItem, char *type, t_person *firstPerson, char *prefix)
{
    if (!testObj(tmpItem)) {
        error("Invalid input given to 'printItemWithType()'!");
    }
    
    unsigned long temp = 0;
    if (tmpItem->person) temp = tmpItem->person->id;
    t_person *tmpPerson;
    tmpPerson = getObj(temp, firstPerson);
    
    if (strcmp(type, "")) {
        if (strcmp(prefix, "")) {
            if (tmpPerson)
                printf(
                   "%s%s%s%s%s%s%ld%s%s%s%ld%s%s%s%s%s%s%s%s%s%s",
                   "<td style='text-align:right;'>",
                       "<input type='", type, "' name='", prefix, "_itemId' value='", tmpItem->id, "' disabled='disabled'>",
                   "</td>",
                   "<td style='text-align:right;' class='disabled-radio'>",
                       tmpItem->id,
                   "</td>",
                   "<td style='text-align:right;' class='disabled-radio'>",
                       tmpItem->name,
                   "</td>",
                   "<td style='text-align:right;' class='disabled-radio'>",
                       tmpItem->type,
                   "</td>",
                   "<td style='text-align:right;' class='disabled-radio'>",
                       tmpItem->author,
                   "</td>"
               );
            else
                printf(
                   "%s%s%s%s%s%s%ld%s%s%s%ld%s%s%s%s%s%s%s%s%s%s",
                   "<td style='text-align:right;'>",
                       "<input type='", type, "' name='", prefix, "_itemId' value='", tmpItem->id, "'>",
                   "</td>",
                   "<td style='text-align:right;'>",
                       tmpItem->id,
                   "</td>",
                   "<td style='text-align:right;'>",
                       tmpItem->name,
                   "</td>",
                   "<td style='text-align:right;'>",
                       tmpItem->type,
                   "</td>",
                   "<td style='text-align:right;'>",
                       tmpItem->author,
                   "</td>"
               );
        } else {
            printf(
                "%s%s%s%s%s%s%ld%s%s%s%ld%s%s%s%s%s%s%s%s%s%s",
                "<td style='text-align:right;'>",
                    "<input type='", type, "' name='", prefix, "_itemId' value='", tmpItem->id, "'>",
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->id,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->name,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->type,
                "</td>",
                "<td style='text-align:right;'>",
                    tmpItem->author,
                "</td>"
            );
            if (tmpPerson) printPersonWithType(tmpPerson, "");
            else printf("<td style='text-align:right;'>(none)</td>");
        }
    } else {
        printf(
            "%s%ld%s%s%s%s%s%s%s%s%s%s",
            "<td style='text-align:right;'>",
                tmpItem->id,
            "</td>",
            "<td style='text-align:right;'>",
                tmpItem->name,
            "</td>",
            "<td style='text-align:right;'>",
                tmpItem->type,
            "</td>",
            "<td style='text-align:right;'>",
                tmpItem->author,
            "</td>"
        );
        if (tmpPerson) printPersonWithType(tmpPerson, "");
        else printf("<td style='text-align:right;'>(none)</td>");
    }
    
    return;
}
