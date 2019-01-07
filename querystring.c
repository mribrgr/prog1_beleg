//
//  querystring.c
//  beleg
//
//  Created by Mauritius Berger on 06.01.19.
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

char* parseQueryString(t_person* firstPerson, t_item* firstItem, t_loan* firstLoan)
{
    int test;
    char* queryString = getenv("QUERY_STRING");
    
    /* begin general handling */
        char* vorname = malloc(sizeof(char) * strlen(queryString));
        char* nachname = malloc(sizeof(char) * strlen(queryString));
        char* tag = malloc(sizeof(char) * strlen(queryString));
        char* monat = malloc(sizeof(char) * strlen(queryString));
        char* jahr = malloc(sizeof(char) * strlen(queryString));
    
        if (!vorname || !nachname || !tag || !monat || !jahr || !input_radio) {
            error("Speicher konnte nicht reserviert werden f&uuml;r die einzugebene Person bei 'main()'!");
        }
    /* end general handling */
    
    if (strstr(queryString, "addPerson_first_name=")) {
        test = sscanf(queryString, "addPerson_first_name=%[^&]&addPerson_last_name=%[^&]&addPerson_date=%[^.].%[^.].%[^&]", vorname, nachname, tag, monat, jahr);
        if (test != 5) {
            error("Ung&uuml;ltige Eingabe bei 'main()'!");
        }
        lastPerson = inputPerson(firstPerson, lastPerson, vorname, nachname, atoi(tag), atoi(monat), atoi(jahr));
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
        
    } else if (strstr(queryString, "addLoan_first_name=")) {
        test = sscanf(queryString, "addLoan_first_name=%[^&]&addLoan_last_name=%[^&]&addLoan_date=%[^.].%[^.].%[^&]", vorname, nachname, tag, monat, jahr);
        if (test != 5 && !testInputNewPerson(vorname, nachname, atoi(tag), atoi(monat), atoi(jahr)) ) {
            error("Ung&uuml;ltige Eingabe bei 'main()'!");
        }
        tmpPerson = lastPerson = inputPerson(firstPerson, lastPerson, vorname, nachname, atoi(tag), atoi(monat), atoi(jahr));
        
        //            newLoan(firstPerson, lastPerson, tmpPerson);
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
    } else if (strstr(queryString, "addLoan_IS_personVorhanden=")) {
        if (strstr(queryString, "addLoan_IS_personVorhanden=ja")) {
            viewPersonListWithType(firstPerson, "addLoan_", "radio");
        } else if (strstr(queryString, "addLoan_IS_personVorhanden=nein")) {
            viewInputPerson("addLoan_");
        }
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
    } else if (strstr(queryString, "addLoan_personId=")) {
        test = sscanf(queryString, "addLoan_personId=%[^&]", personId);
        if (test != 1) {
            error("'sscanf()' - Fehler bei 'main():aL_personId'!");
        }
        tmpPerson = getObj(atol(personId), firstPerson);
        if (!tmpPerson) {
            error("Person wurde nicht gefunden!");
        }
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
    
    } else if (!strstr(queryString, "deleteItem_itemId=")) {
        viewDelete("item");
    } else if (!strstr(queryString, "deletePerson_personId=")) {
        viewDelete("person");
    } else if (!strstr(queryString, "deleteLoan_loanId=")) {
        viewDelete("loan");
        
    } else {
        viewMain(firstPerson, firstItem, firstLoan);
    }
    
    free(vorname);
    free(nachname);
    free(tag);
    free(monat);
    free(jahr);
}

viewDelete(char* function, char* structure, char* firstPerson, char* firstItem, char* firstLoan)
{
    char* queryString = getenv("QUERY_STRING");
    void* firstObj = NULL;

    if (strstr(queryString, "Id=all")) {
        /* Schnellste Art alle Personen zu löschen. */
        if (!strcmp(structure, "person") || !strcmp(structure, "item")) {
            if (testObj(firstLoan)) {
                printf("Es konnten nicht alle %ss gel&ouml;scht werden, da es noch offenen Ausleihen gibt!<br />", structure); // am besten werden hier alle offenen Ausleihen angezeigt!
            }
        } else {
            // wenn eine loan gelöscht wird, sollte auch person->loans beachtet werden!
            writeObjListToData(structure, NULL); //hier weitermachen das zu generalisieren
            printf("Es wurden erfolgreich alle %ss gel&ouml;scht.<br />", structure);
        }
    } else {
        if (!strcmp(structure, "item")) firstObj = firstItem;
        if (!strcmp(structure, "person")) firstObj = firstPerson;
        if (!strcmp(structure, "loan")) firstObj = firstLoan;
        
        test = sscanf(queryString, "Id=%[^&]", identifier);
        if (test != 1) error("'sscanf()' - Fehler bei 'main():%sId'!", structure);
        
        if (strcmp(structure, "loan") && !getObj(atol(identifier), firstLoan)) printf("%s konnte nicht gel&ouml;scht werden, da es noch dazu geh&ouml;rige, offene Ausleihen gibt!", structure);
        else {
            firstObj = deleteObjFromList(structure, getObj(atol(identifier), firstObj), firstObj);
            writeObjListToData(structure, firstObj);
            printf("%s %ld wurde erfolgreich gel&ouml;scht.<br />", structure, atol(identifier)); // klappt noch nicht wie es sollte wenn die liste leer ist
            while (1) {
                queryString = (queryString + strlen(structure) + strlen("Id=") + strlen(identifier) + 1);
                test = sscanf(queryString, "Id=%[^&]", identifier);
                if (test != 1) {
                    break;
                }
                if (strcmp(structure, "loan") && !getObj(atol(identifier), firstLoan)) printf("%s konnte nicht gel&ouml;scht werden, da es noch dazu geh&ouml;rige, offene Ausleihen gibt!", structure);
                else {
                    firstObj = deleteObjFromList(structure, getObj(atol(identifier), firstObj), firstObj);
                    writeObjListToData(structure, firstObj);
                    printf("%s %ld wurde erfolgreich gel&ouml;scht.<br />", structure, atol(identifier)); // klappt noch nicht wie es sollte wenn die liste leer ist
                }
            }
        }
    }
    printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
    
    
    
    
    if (strstr(queryString, "deletePerson_personId=all")) {
        if (!testObj(firstLoan)) {
            /* Schnellste Art alle Personen zu löschen. */
            firstPerson = NULL;
            writeObjListToData("person", firstPerson);
            printf("Es wurden erfolgreich alle Personen gel&ouml;scht.<br />");
        } else {
            printf("Es konnten nicht alle Personen gel&ouml;scht werden, da es noch offenen Ausleihen gibt!"); // am besten werden hier alle offenen Ausleihen angezeigt!
        }
    } else {
        test = sscanf(queryString, "dP_personId=%[^&]", personId);
        if (test != 1) {
            error("'sscanf()' - Fehler bei 'main():dP_personId'!");
        }
        if (!getObj(atol(personId), firstLoan)) {
            firstPerson = (t_person*) deleteObjFromList("person", getObj(atol(personId), firstPerson), firstPerson);
            writeObjListToData("person", firstPerson);
            printf("Person wurde erfolgreich gel&ouml;scht.<br />"); // klappt noch nicht wie es sollte wenn die liste leer ist
            while (1) {
                queryString = (queryString + strlen("dP_personId=") + strlen(personId) + 1);
                test = sscanf(queryString, "dP_personId=%[^&]", personId);
                if (test != 1) {
                    break;
                }
                firstPerson = (t_person*) deleteObjFromList("person", getObj(atol(personId), firstPerson), firstPerson);
                writeObjListToData("person", firstPerson);
                printf("Person wurde erfolgreich gel&ouml;scht.<br />"); // klappt noch nicht wie es sollte wenn die liste leer ist
            }
        } else {
            printf("Die Person %ld konnte nicht gel&ouml;scht werden, da es noch offenen Ausleihen gibt!", atol(personId)); // am besten werden hier die offenen Ausleihen angezeigt!
        }
    }
    printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
}
