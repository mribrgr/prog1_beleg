//
//  view.c
//  beleg
//  46139
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
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

void viewExist(char *structure, char *function, char *prefix)
{
    printf("<form method='get'>");
    printf("Is the %s already there?<br />", structure);
    printf("<input type='radio' value='true' name='%s_EXIST_%s'> Yes<br />", prefix, structure);
    printf("<input type='radio' value='false' name='%s_EXIST_%s'> No<br />", prefix, structure);
    printf("<input type='submit' value='Submit' name='%s'><br />", function);
    printf("</form>");
    
    return;
}

void viewInputLoan(char *function, char *personId, char *itemId)
{
    printf("<form method='get'>");
    printf("<table>");
    printf("    <tr>");
    printf("        <td>Begin-date of the loan [DD.MM.YYYY]:</td><td><input type='text' value='' name='%s_%s_loan_begin'>", personId, itemId);
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>End-date of the loan [DD.MM.YYYY]:</td><td><input type='text' value='' name='loan_end'></td>");
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Submit' name='%s'>", function);
    printf("</form>");
    
    return;
}

void viewInputPerson(char *function)
{
    printf("<form method='get'>");
    printf("<table>");
    printf("    <tr>");
    printf("        <td>first name of the person:</td><td><input type='text' value='' name='first_name'>");
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>last name of the person:</td><td><input type='text' value='' name='last_name'></td>");
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>date of birth of the person [DD.MM.YYYY]:</td><td><input type='text' value='' name='date'></td>");
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Submit' name='%s'>", function);
    printf("</form>");
    
    return;
}

void viewInputItem(char *function, char *prefix)
{
    printf("<form method='get'>");
    printf("<table>");
    printf("    <tr>");
    printf("        <td>name of the item:</td><td><input type='text' value='' name='%s_name'>", prefix);
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>type of the item:</td><td><input type='text' value='' name='type'></td>"); // radio element
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>author of the item:</td><td><input type='text' value='' name='author'></td>");
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Submit' name='%s'>", function);
    printf("</form>");
    
    return;
}

void viewMain(t_person *firstPerson, t_item *firstItem, t_loan *firstLoan)
{
    printf("<h2>What should happen?</h2><br />");
    
    printf("<form method='get'>");
    printf("<table>");
    printf("    <tr>");
    printf("        <td></td>");
    printf("        <td>Add:</td>");
    printf("        <td>View:</td>");
    printf("        <td>Delete:</td>");
    printf("    </tr>");
    
    printf("    <tr>");
    printf("        <td>loans:</td>");
    printf("        <td><input type='radio' value='addLoan' name='input_radio'> new loan</td>");
    if (testObj(firstLoan)) {
        printf("        <td><input type='radio' value='viewLoan' name='input_radio'> show all loans</td>");
        printf("        <td><input type='radio' value='deleteLoan' name='input_radio'> close a loan</td>");
    } else {
        printf("        <td title='loan-list is empty!' class='disabled-radio'><input type='radio' value='viewLoan' name='input_radio' disabled='disabled'> show all loans</td>");
        printf("        <td title='loan-list is empty!' class='disabled-radio'><input type='radio' value='deleteLoan' name='input_radio' disabled='disabled'> close a loan</td>");
    }
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>persons:</td>");
    printf("        <td><input type='radio' value='addPerson' name='input_radio'> new person</td>");
    if (testObj(firstPerson)) {
        printf("        <td><input type='radio' value='viewPerson' name='input_radio'> show all persons</td>");
        printf("        <td><input type='radio' value='deletePerson' name='input_radio'> delete a person</td>");
    } else {
        printf("        <td title='person-list is empty!' class='disabled-radio'><input type='radio' value='viewPerson' name='input_radio' disabled='disabled'> show all persons</td>");
        printf("        <td title='person-list is empty!' class='disabled-radio'><input type='radio' value='deletePerson' name='input_radio' disabled='disabled'> delete a person</td>");
    }
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>items:</td>");
    printf("        <td><input type='radio' value='addItem' name='input_radio'> new item</td>");
    if (testObj(firstItem)) {
        printf("        <td><input type='radio' value='viewItem' name='input_radio'> show all items</td>");
        printf("        <td><input type='radio' value='deleteItem' name='input_radio'> delete an item</td>");
    } else {
        printf("        <td title='item-list is empty!' class='disabled-radio'><input type='radio' value='viewItem' name='input_radio' disabled='disabled'> show all items</td>");
        printf("        <td title='item-list is empty!' class='disabled-radio'><input type='radio' value='deleteItem' name='input_radio' disabled='disabled'> delete an item</td>");
    }
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Submit' name='main'>");
    printf("</form>");
    
    return;
}

void viewPersonListWithType(t_person *firstPerson, char *function, char *type, unsigned long identifier)
{
    t_person* tmpPerson;
    
    if (!testObj(firstPerson)) {
        printListEmpty("person");
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    if (!strcmp(type, "checkbox")) {
        printf("<tr><td>(all)<input type='%s' name='personId' value='all'></td><td>person-ID:</td><td>first name:</td><td>last name:</td><td>date of birth:</td></tr>", type);
    } else {
        printf("<tr><td>person-ID:</td><td>first name:</td><td>last name:</td><td>date of birth:</td></tr>");
    }
    
    printf("<tr%s>", (firstPerson->id==identifier)?" id='bold'":""); printPersonWithType(firstPerson, type); printf("</tr>");
    if (firstPerson->next) {
        printf("<tr%s>", (firstPerson->next->id==identifier)?" id='bold'":""); printPersonWithType(firstPerson->next, type); printf("</tr>");
        tmpPerson = firstPerson->next;
        while (tmpPerson->next) {
            printf("<tr%s>", (tmpPerson->next->id==identifier)?" id='bold'":""); printPersonWithType(tmpPerson->next, type); printf("</tr>");
            tmpPerson = tmpPerson->next;
        }
    }
    
    printf("</table>");
    
    printf("person-search (by ID): <input type='text' value='' name='search_%s_%s_person_id'><br />", " ", (!strcmp(type,""))?" ":type);
    printf("<input type='submit' value='Submit' name='%s'>", function);
    
    printf("</form>");
    
    return;
}

void viewLoanListWithType(t_loan *firstLoan, char *function, char *type, unsigned long identifier)
{
    t_loan* tmpLoan;
    
    if (!testObj(firstLoan)) {
        printListEmpty("loan");
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    if (!strcmp(type, "checkbox"))
        printf("<tr><td>(all)<input type='%s' name='loanId' value='all'></td><td>loan-ID:</td><td>person-ID:</td><td>Item-ID:</td><td>loan-begin:</td><td>loan-end:</td></tr>", type);
    else
        printf("<tr><td>loan-ID:</td><td>person-ID:</td><td>item-ID:</td><td>loan-begin:</td><td>loan-end:</td></tr>");
    
    printf("<tr%s>", (firstLoan->id==identifier)?" id='bold'":""); printLoanWithType(firstLoan, type); printf("</tr>");
    if (firstLoan->next) {
        printf("<tr%s>", (firstLoan->next->id==identifier)?" id='bold'":""); printLoanWithType(firstLoan->next, type); printf("</tr>");
        tmpLoan = firstLoan->next;
        while (tmpLoan->next) {
            printf("<tr%s>", (tmpLoan->next->id==identifier)?" id='bold'":""); printLoanWithType(tmpLoan->next, type); printf("</tr>");
            tmpLoan = tmpLoan->next;
        }
    }
    
    printf("</table>");
    
    printf("loan-search (by ID): <input type='text' value='' name='search_%s_%s_loan_id'><br />", " ", (!strcmp(type,""))?" ":type);
    printf("<input type='submit' value='Submit' name='%s'>", function);
    
    printf("</form>");
    
    return;
}

void viewItemListWithType(t_item *firstItem, char *function, char *type, unsigned long identifier, t_person *firstPerson, char *prefix)
{
    t_item* tmpItem;
    
    if (!testObj(firstItem)) {
        printListEmpty("item");
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    char buf[64];
    if (strcmp(type, "")) {
        strcpy(buf, "<td></td>");
    }
    
    if (!strcmp(type, "checkbox")) {
        printf("<tr><td>(all)<input type='%s' name='itemId' value='all'></td><td>item-ID:</td><td>name:</td><td>type:</td><td>author:</td><td>connected person-ID:</td><td>first name:</td><td>last name:</td><td>date of birth:</td></tr>", type);
    } else {
        if (!strcmp(prefix, ""))
            printf("<tr>%s<td>item-ID:</td><td>name:</td><td>type:</td><td>author:</td><td>connected person-ID:</td><td>first name:</td><td>last name:</td><td>date of birth:</td></tr>", buf);
        else
            printf("<tr>%s<td>item-ID:</td><td>name:</td><td>type:</td><td>author:</td></tr>", buf);
    }
    
    printf("<tr%s>", (firstItem->id==identifier)?" id='bold'":""); printItemWithType(firstItem, type, firstPerson, prefix); printf("</tr>");
    if (firstItem->next) {
        printf("<tr%s>", (firstItem->next->id==identifier)?" id='bold'":""); printItemWithType(firstItem->next, type, firstPerson, prefix); printf("</tr>");
        tmpItem = firstItem->next;
        while (tmpItem->next) {
            printf("<tr%s>", (tmpItem->next->id==identifier)?" id='bold'":""); printItemWithType(tmpItem->next, type, firstPerson, prefix); printf("</tr>");
            tmpItem = tmpItem->next;
        }
    }
    
    printf("</table>");
    
    printf("item-search (by ID): <input type='text' value='' name='search_%s_%s_item_id'><br />", (!strcmp(prefix,""))?" ":prefix, (!strcmp(type,""))?" ":type);
    printf("<input type='submit' value='Submit' name='%s'>", function);
    
    printf("</form>");
    
    return;
}
