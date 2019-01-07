//
//  view.c
//  beleg
//
//  Created by Mauritius Berger on 12.12.18.
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

void viewNewLoan(t_person* firstPerson)
{
    if (!testObj(firstPerson)) {
        viewInputPerson("addLoan");
    } else {
        printf("<form method='get'>");
        printf("Ist die Person schon vorhanden?<br />");
        printf("<input type='radio' value='true' name='EXIST_PERSON'> Ja<br />");
        printf("<input type='radio' value='false' name='EXIST_PERSON'> Nein<br />");
        printf("<input type='submit' value='Submit' name='addLoan'><br />");
        printf("</form>");
    }
    
    return;
}

void viewInputPerson(char* function)
{
    printf("<form method='get'>");
    printf("<table>"); // '\n'?
    printf("    <tr>");
    printf("        <td>Vorname der Person:</td><td><input type='text' value='' name='first_name'>");
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Nachname der Person:</td><td><input type='text' value='' name='last_name'></td>");
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Geburtsdatum der Person [DD.MM.YYYY]:</td><td><input type='text' value='' name='date'></td>");
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Absenden' name='%s'>", function);
    printf("</form>");
    
    return;
}

void viewInputItem(char* function)
{
    printf("<form method='get'>");
    printf("<table>");
    printf("    <tr>");
    printf("        <td>Name des Mediums:</td><td><input type='text' value='' name='name'>");
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Art des Mediums:</td><td><input type='text' value='' name='type'></td>"); // radio element
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Autor / Interpret des Mediums:</td><td><input type='text' value='' name='author'></td>");
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Person-ID:</td><td><input type='text' value='' name='personId'></td>"); // radio element
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Submit' name='%s'>", function);
    printf("</form>");
    
    return;
}

// evtl. unused?
void viewSearchPerson(void)
{
    printf("ID der Person eingaben: <input type='text' value='' name='personId'>");
    
    return;
}

// evtl. unused?
void viewSearchLoan(void)
{
    printf("ID der Person eingeben: <input type='text' value='' name='personId'>");
    
    return;
}

// evtl. unused?
void viewSearchItem(void)
{
    printf("ID des Items eingaben: <input type='text' value='' name='itemId'>");
    
    return;
}

void viewMain(t_person* firstPerson, t_item* firstItem, t_loan* firstLoan)
{
    printf("<h2>Was soll geschehen?</h2><br />");
    
    printf("<form method='get'>");
    printf("<table>"); // '\n'?
    printf("    <tr>");
    printf("        <td></td>");
    printf("        <td>Hinzuf&uuml;gen:</td>");
    printf("        <td>Anschauen:</td>");
    printf("        <td>L&ouml;schen:</td>");
    printf("    </tr>");
    
    printf("    <tr>");
    printf("        <td>Ausleihen:</td>");
    printf("        <td><input type='radio' value='addLoan' name='input_radio'> neue Ausleihe</td>");
    if (testObj(firstLoan)) {
        printf("        <td><input type='radio' value='viewLoan' name='input_radio'> zeige alle Ausleihen</td>");
        printf("        <td><input type='radio' value='deleteLoan' name='input_radio'> Ausleihe l&ouml;schen / beenden</td>");
    } else {
        printf("        <td title='Ausleih-Liste ist leer!' class='disabled-radio'><input type='radio' value='viewLoan' name='input_radio' disabled='disabled'> zeige alle Ausleihen</td>");
        printf("        <td title='Ausleih-Liste ist leer!' class='disabled-radio'><input type='radio' value='deleteLoan' name='input_radio' disabled='disabled'> Ausleihe l&ouml;schen / beenden</td>");
    }
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Personen:</td>");
    printf("        <td><input type='radio' value='addPerson' name='input_radio'> neue Person</td>");
    if (testObj(firstPerson)) {
        printf("        <td><input type='radio' value='viewPerson' name='input_radio'> zeige alle Personen</td>");
        printf("        <td><input type='radio' value='deletePerson' name='input_radio'> l&ouml;sche eine Person</td>");
    } else {
        printf("        <td title='Personen-Liste ist leer!' class='disabled-radio'><input type='radio' value='viewPerson' name='input_radio' disabled='disabled'> zeige alle Personen</td>");
        printf("        <td title='Personen-Liste ist leer!' class='disabled-radio'><input type='radio' value='deletePerson' name='input_radio' disabled='disabled'> l&ouml;sche eine Person</td>");
    }
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Medien:</td>");
    printf("        <td><input type='radio' value='addItem' name='input_radio'> neues Medium</td>");
    if (testObj(firstItem)) {
        printf("        <td><input type='radio' value='viewItem' name='input_radio'> zeige alle Medien</td>");
        printf("        <td><input type='radio' value='deleteItem' name='input_radio'> l&ouml;sche ein Medium</td>");
    } else {
        printf("        <td title='Medien-Liste ist leer!' class='disabled-radio'><input type='radio' value='viewItem' name='input_radio' disabled='disabled'> zeige alle Medien</td>");
        printf("        <td title='Medien-Liste ist leer!' class='disabled-radio'><input type='radio' value='deleteItem' name='input_radio' disabled='disabled'> l&ouml;sche ein Medium</td>");
    }
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Submit' name='main'>");
    printf("</form>");
    
    return;
}

void viewPersonListWithType(t_person* firstPerson, char* function, char* type)
{
    /* Deklarationen */
    t_person* tmpPerson;
    
    if (!testObj(firstPerson)) {
        printListEmpty("person");
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    if (!strcmp(type, "checkbox")) {
        printf("<tr><td>(alle)<input type='%s' name='personId' value='all'></td><td>Person-ID:</td><td>Vorname:</td><td>Nachname:</td><td>Geb.-Datum:</td></tr>", type);
    } else {
        printf("<tr><td></td><td>Person-ID:</td><td>Vorname:</td><td>Nachname:</td><td>Geb.-Datum:</td></tr>");
    }
    
    printPersonWithType(firstPerson, type);
    if (firstPerson->next) {
        printPersonWithType(firstPerson->next, type);
        tmpPerson = firstPerson->next;
        while (tmpPerson->next) {
            printPersonWithType(tmpPerson->next, type);
            tmpPerson = tmpPerson->next;
        }
    }
    
    printf("</table>");
    // eventuell zu Filter Einstellungen wie bei Ebay ändern
    // eventuell in Funktion auslagern und richtige Suchmaske erstellen, wo auch innerhalb von Namen etc. gesucht werden kann
    // die Funktion hier sollte danach trotzdem aufgerufen werden, jedoch muss bei printPerson erst überprüft werden ob der Name / ID etc. stimmt
    printf("Personen-Suche (ID): <input type='text' value='' name='personSearchId'><br />");
    printf("<input type='submit' value='Submit' name='%s'>", function);
    printf("</form>");
    
    return;
}

void viewLoanListWithType(t_loan* firstLoan, char* function, char* type)
{ // wie siehts mit den items aus?
    /* Deklarationen */
    t_loan* tmpLoan;
    
    if (!testObj(firstLoan)) {
        printListEmpty("loan");
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    if (!strcmp(type, "checkbox")) {
        printf("<tr><td>(alle)<input type='%s' name='loanId' value='all'></td><td>Loan-ID:</td><td>Person-ID:</td><td>Loan-begin:</td><td>Loan-end:</td></tr>", type);
    } else {
        printf("<tr><td></td><td>Loan-ID:</td><td>Person-ID:</td><td>Loan-begin:</td><td>Loan-end:</td></tr>");
    }
    
    printLoanWithType(firstLoan, type);
    if (firstLoan->next) {
        printLoanWithType(firstLoan->next, type);
        tmpLoan = firstLoan->next;
        while (tmpLoan->next) {
            printLoanWithType(tmpLoan->next, type);
            tmpLoan = tmpLoan->next;
        }
    }
    
    printf("</table>");
    // eventuell zu Filter Einstellungen wie bei Ebay ändern
    // eventuell in Funktion auslagern und richtige Suchmaske erstellen, wo auch innerhalb von Namen etc. gesucht werden kann
    // die Funktion hier sollte danach trotzdem aufgerufen werden, jedoch muss bei printPerson erst überprüft werden ob der Name / ID etc. stimmt
    printf("Loan-Suche (ID): <input type='text' value='' name='loanSearchId'><br />");
    printf("<input type='submit' value='Submit' name='%s'>", function);
    printf("</form>");
    
    return;
}

void viewItemListWithType(t_item* firstItem, char* function, char* type)
{
    /* Deklarationen */
    t_item* tmpItem;
    
    if (!testObj(firstItem)) {
        printListEmpty("item");
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    if (!strcmp(type, "checkbox")) {
        printf("<tr><td>(alle)<input type='%s' name='itemId' value='all'></td><td>Item-ID:</td><td>Person-ID:</td><td>Name:</td><td>Type:</td><td>Author:</td></tr>", type);
    } else {
        printf("<tr><td></td><td>Item-ID:</td><td>Person-ID:</td><td>Name:</td><td>Type:</td><td>Author:</td></tr>");
    }
    
    printItemWithType(firstItem, type);
    if (firstItem->next) {
        printItemWithType(firstItem->next, type);
        tmpItem = firstItem->next;
        while (tmpItem->next) {
            printItemWithType(tmpItem->next, type);
            tmpItem = tmpItem->next;
        }
    }
    
    printf("</table>");
    // eventuell zu Filter Einstellungen wie bei Ebay ändern
    // eventuell in Funktion auslagern und richtige Suchmaske erstellen, wo auch innerhalb von Namen etc. gesucht werden kann
    // die Funktion hier sollte danach trotzdem aufgerufen werden, jedoch muss bei printPerson erst überprüft werden ob der Name / ID etc. stimmt
    printf("Item-Suche (ID): <input type='text' value='' name='itemSearchId'><br />");
    printf("<input type='submit' value='Submit' name='%s'>", function);
    printf("</form>");
    
    return;
}

void viewDelPerson(t_person* firstPerson)
{
    //viewSearchPerson("del_");
    viewPersonListWithType(firstPerson, "deletePerson", "checkbox");
    
    return;
}

void viewDelLoan(t_loan* firstLoan)
{
    //viewSearchPerson("del_");
    viewLoanListWithType(firstLoan, "deleteLoan", "checkbox");
    
    return;
}

void viewDelItem(t_item* firstItem)
{
    //viewSearchPerson("del_");
    viewItemListWithType(firstItem, "deleteItem", "checkbox");
    
    return;
}
