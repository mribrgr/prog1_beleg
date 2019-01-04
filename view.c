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
    if (!testPerson(firstPerson)) {
        viewInputPerson("aA_");
    } else {
        printf("<form method='get'>");
        printf("Ist die Person schon vorhanden?<br />");
        printf("<input type='radio' value='ja' name='aA_IS_personVorhanden'> Ja<br />");
        printf("<input type='radio' value='nein' name='aA_IS_personVorhanden'> Nein<br />");
        printf("<input type='submit' value='Abschicken'><br />");
        printf("</form>");
    }
    
    return;
}

void viewInputPerson(char* prefix)
{
    printf("<form method='get'>");
    printf("<table>"); // '\n'?
    printf("    <tr>");
    printf("        <td>Vorname der Person:</td><td><input type='text' value='' name='%sfirst_name'>", prefix);
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Nachname der Person:</td><td><input type='text' value='' name='%slast_name'></td>", prefix);
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Geburtsdatum der Person [DD.MM.YYYY]:</td><td><input type='text' value='' name='%sdate'></td>", prefix);
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Absenden'>");
    printf("</form>");
    
    return;
}

void viewInputItem(char* prefix)
{
    printf("<form method='get'>");
    printf("<table>");
    printf("    <tr>");
    printf("        <td>Name des Mediums:</td><td><input type='text' value='' name='%sname'>", prefix);
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Art des Mediums:</td><td><input type='text' value='' name='%stype'></td>", prefix); // radio element
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Autor / Interpret des Mediums:</td><td><input type='text' value='' name='%sauthor'></td>", prefix);
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Person-ID:</td><td><input type='text' value='' name='%spersonId'></td>", prefix); // radio element
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Absenden'>");
    printf("</form>");
    
    return;
}

// evtl. unused?
void viewSearchPerson(char* prefix)
{
    printf("ID der Person eingaben: <input type='text' value='' name='%spersonId'>", prefix);
    
    return;
}

// evtl. unused?
void viewSearchLoan(char* prefix)
{
    printf("ID der Person eingeben: <input type='text' value='' name='%spersonId'>", prefix);
    
    return;
}

// evtl. unused?
void viewSearchItem(char* prefix)
{
    printf("ID des Items eingaben: <input type='text' value='' name='%sitemId'>", prefix);
    
    return;
}

void viewMain(t_person* firstPerson, t_item* firstItem, t_loan* firstLoan)
{
    puts("<h2>Was soll geschehen?</h2><br />");
    
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
    if (testLoan(firstLoan)) {
        printf("        <td><input type='radio' value='aA' name='input_radio'> neue Ausleihe</td>");
        printf("        <td><input type='radio' value='vA' name='input_radio'> zeige alle Ausleihen</td>");
        printf("        <td><input type='radio' value='dA' name='input_radio'> Ausleihe l&ouml;schen / beenden</td>");
    } else {
        printf("        <td class='disabled-radio'><input type='radio' value='aA' name='input_radio' disabled='disabled'> neue Ausleihe</td>");
        printf("        <td class='disabled-radio'><input type='radio' value='vA' name='input_radio' disabled='disabled'> zeige alle Ausleihen</td>");
        printf("        <td class='disabled-radio'><input type='radio' value='dA' name='input_radio' disabled='disabled'> Ausleihe l&ouml;schen / beenden</td>");
    }
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Personen:</td>");
    if (testPerson(firstPerson)) {
        printf("        <td><input type='radio' value='aP' name='input_radio'> neue Person</td>");
        printf("        <td><input type='radio' value='vP' name='input_radio'> zeige alle Personen</td>");
        printf("        <td><input type='radio' value='dP' name='input_radio'> l&ouml;sche eine Person</td>");
    } else {
        printf("        <td class='disabled-radio'><input type='radio' value='aP' name='input_radio' disabled='disabled'> neue Person</td>");
        printf("        <td class='disabled-radio'><input type='radio' value='vP' name='input_radio' disabled='disabled'> zeige alle Personen</td>");
        printf("        <td class='disabled-radio'><input type='radio' value='dP' name='input_radio' disabled='disabled'> l&ouml;sche eine Person</td>");
    }
    printf("    </tr>");
    printf("    <tr>");
    printf("        <td>Medien:</td>");
    if (testItem(firstItem)) {
        printf("        <td><input type='radio' value='aM' name='input_radio'> neues Medium</td>");
        printf("        <td><input type='radio' value='vM' name='input_radio'> zeige alle Medien</td>");
        printf("        <td><input type='radio' value='dM' name='input_radio'> l&ouml;sche ein Medium</td>");
    } else {
        printf("        <td class='disabled-radio'><input type='radio' value='aM' name='input_radio' disabled='disabled'> neues Medium</td>");
        printf("        <td class='disabled-radio'><input type='radio' value='vM' name='input_radio' disabled='disabled'> zeige alle Medien</td>");
        printf("        <td class='disabled-radio'><input type='radio' value='dM' name='input_radio' disabled='disabled'> l&ouml;sche ein Medium</td>");
    }
    printf("    </tr>");
    printf("    <tr>"); // soll später gelöscht werden
    printf("        <td>Dateien:</td>");
    printf("        <td></td>");
    printf("        <td></td>");
    printf("        <td><input type='radio' value='resetFile' name='input_radio'> resette das File 'person.csv'</td>");
    printf("    </tr>");
    printf("</table>");
    printf("<input type='submit' value='Absenden'>");
    printf("</form>");
    
    return;
}

void viewPersonListWithType(t_person* firstPerson, char* prefix, char* type)
{
    /* Deklarationen */
    t_person* tmpPerson;
    
    if (!testPerson(firstPerson)) {
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    if (!strcmp(type, "checkbox")) {
        printf("<tr><td>(alle)<input type='%s' name='%spersonId' value='all'></td><td>Person-ID:</td><td>Vorname:</td><td>Nachname:</td><td>Geb.-Datum:</td></tr>", type, prefix);
    } else {
        printf("<tr><td></td><td>Person-ID:</td><td>Vorname:</td><td>Nachname:</td><td>Geb.-Datum:</td></tr>");
    }
    
    printPersonWithType(firstPerson, prefix, type);
    if (firstPerson->next) {
        printPersonWithType(firstPerson->next, prefix, type);
        tmpPerson = firstPerson->next;
        while (tmpPerson->next) {
            printPersonWithType(tmpPerson->next, prefix, type);
            tmpPerson = tmpPerson->next;
        }
    }
    
    printf("</table>");
    // eventuell zu Filter Einstellungen wie bei Ebay ändern
    // eventuell in Funktion auslagern und richtige Suchmaske erstellen, wo auch innerhalb von Namen etc. gesucht werden kann
    // die Funktion hier sollte danach trotzdem aufgerufen werden, jedoch muss bei printPerson erst überprüft werden ob der Name / ID etc. stimmt
    printf("Personen-Suche (ID): <input type='text' value='' name='%spersonSearchId'><br />", prefix);
    printf("<input type='submit' value='Abschicken'>");
    printf("</form>");
    
    return;
}

void viewLoanListWithType(t_loan* firstLoan, char* prefix, char* type)
{ // wie siehts mit den items aus?
    /* Deklarationen */
    t_loan* tmpLoan;
    
    if (!testLoan(firstLoan)) {
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    if (!strcmp(type, "checkbox")) {
        printf("<tr><td>(alle)<input type='%s' name='%sloanId' value='all'></td><td>Loan-ID:</td><td>Person-ID:</td><td>Loan-begin:</td><td>Loan-end:</td></tr>", type, prefix);
    } else {
        printf("<tr><td></td><td>Loan-ID:</td><td>Person-ID:</td><td>Loan-begin:</td><td>Loan-end:</td></tr>");
    }
    
    printLoanWithType(firstLoan, prefix, type);
    if (firstLoan->next) {
        printLoanWithType(firstLoan->next, prefix, type);
        tmpLoan = firstLoan->next;
        while (tmpLoan->next) {
            printLoanWithType(tmpLoan->next, prefix, type);
            tmpLoan = tmpLoan->next;
        }
    }
    
    printf("</table>");
    // eventuell zu Filter Einstellungen wie bei Ebay ändern
    // eventuell in Funktion auslagern und richtige Suchmaske erstellen, wo auch innerhalb von Namen etc. gesucht werden kann
    // die Funktion hier sollte danach trotzdem aufgerufen werden, jedoch muss bei printPerson erst überprüft werden ob der Name / ID etc. stimmt
    printf("Loan-Suche (ID): <input type='text' value='' name='%sloanSearchId'><br />", prefix);
    printf("<input type='submit' value='Abschicken'>");
    printf("</form>");
    
    return;
}

void viewItemListWithType(t_item* firstItem, char* prefix, char* type)
{
    /* Deklarationen */
    t_item* tmpItem;
    
    if (!testItem(firstItem)) {
        return;
    }
    
    printf("<form method='get'>");
    printf("<table>");
    
    if (!strcmp(type, "checkbox")) {
        printf("<tr><td>(alle)<input type='%s' name='%sitemId' value='all'></td><td>Item-ID:</td><td>Person-ID:</td><td>Name:</td><td>Type:</td><td>Author:</td></tr>", type, prefix);
    } else {
        printf("<tr><td></td><td>Item-ID:</td><td>Person-ID:</td><td>Name:</td><td>Type:</td><td>Author:</td></tr>");
    }
    
    printItemWithType(firstItem, prefix, type);
    if (firstItem->next) {
        printItemWithType(firstItem->next, prefix, type);
        tmpItem = firstItem->next;
        while (tmpItem->next) {
            printItemWithType(tmpItem->next, prefix, type);
            tmpItem = tmpItem->next;
        }
    }
    
    printf("</table>");
    // eventuell zu Filter Einstellungen wie bei Ebay ändern
    // eventuell in Funktion auslagern und richtige Suchmaske erstellen, wo auch innerhalb von Namen etc. gesucht werden kann
    // die Funktion hier sollte danach trotzdem aufgerufen werden, jedoch muss bei printPerson erst überprüft werden ob der Name / ID etc. stimmt
    printf("Item-Suche (ID): <input type='text' value='' name='%sitemSearchId'><br />", prefix);
    printf("<input type='submit' value='Abschicken'>");
    printf("</form>");
    
    return;
}



void viewDelPerson(t_person* firstPerson)
{
    //viewSearchPerson("del_");
    viewPersonListWithType(firstPerson, "dP_", "checkbox");
    
    return;
}

void viewDelLoan(t_loan* firstLoan)
{
    //viewSearchPerson("del_");
    viewLoanListWithType(firstLoan, "dA_", "radio");
    
    return;
}

void viewDelItem(t_item* firstItem)
{
    //viewSearchPerson("del_");
    viewItemListWithType(firstItem, "dM_", "radio");
    
    return;
}
