//
//  main.c
//  beleg
//
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

//
//  Prefixe: // sollten später noch ersetzt werden durch etwas besseres (unübersichtliche URL)
//  a._    add...    ||  .A_    ...Ausleihe
//  d._    del...    ||  .P_    ...Person
//  v._    view...   ||  .M_    ...Medium
//


// submit name="value" ausnutzen um prefixe loszuwerden (übersichtlichere URL!)
// getter und SETTER!!!!


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

void error(char* msg)
{
    printError(msg);
    printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
    exit (1); // bei CGI kann nicht so einfach rausgegangen werden (siehe Dwnld rechner_cgi.c)
    
    return;
}

void warning(char* msg)
{
    printWarning(msg);
    
    return;
}


void deletePersonenCSV() // sollte später noch geloescht werden; setzt nur den File Seek pointer auf den Anfang
{
    FILE* fp = fopen("person.csv", "w");
    fclose(fp);
    
    return;
}

int main(){
    /* Definitionen & Deklarationen */
        int test;
        char* queryString = getenv("QUERY_STRING");
    
    printf("Content-Type: text/html\n\n");
    printf("<html>");
    printf("<head>");
    printf("<title>Bibliothek</title>");
    printf("<link href='style.css' rel='stylesheet' type='text/css'>");
    printf("</head>");
    printf("<body>");
    
    if (!queryString) {
        error("Query-String ist nicht definiert!");
    }
    
    char* input_radio = malloc(sizeof(char) * strlen(queryString));
    
    /* Person - Definitionen */
        t_person* tmpPerson = NULL;
        t_person* firstPerson = malloc(sizeof(t_person));
        t_person* lastPerson = malloc(sizeof(t_person));
        char* personId = malloc(sizeof(char) * strlen(queryString));
    
        char* vorname = malloc(sizeof(char) * strlen(queryString));
        char* nachname = malloc(sizeof(char) * strlen(queryString));
        char* tag = malloc(sizeof(char) * strlen(queryString));
        char* monat = malloc(sizeof(char) * strlen(queryString));
        char* jahr = malloc(sizeof(char) * strlen(queryString));
    
    /* Loan - Definitionen */
        t_loan* tmpLoan = NULL;
        t_loan* firstLoan = malloc(sizeof(t_loan));
        t_loan* lastLoan = malloc(sizeof(t_loan));
        char* loanId = malloc(sizeof(char) * strlen(queryString));
    
    /* Item - Definitionen */
        t_item* tmpItem = NULL;
        t_item* firstItem = malloc(sizeof(t_loan));
        t_item* lastItem = malloc(sizeof(t_loan));
        char* itemId = malloc(sizeof(char) * strlen(queryString));
    
    /* Beginn Allgemeines Handling */
        if (!vorname || !nachname || !tag || !monat || !jahr || !input_radio) {
            error("Speicher konnte nicht reserviert werden f&uuml;r die einzugebene Person bei 'main()'!");
        }
    /* Ende Allgemeines Handling */
    
    /* begin person list handling */
        if (!firstPerson || !lastPerson) {
            error("Speicherreservierung fehlgeschlagen f&uuml;r person list bei 'main()'!");
        }
        firstPerson = addPersonListDataToList(firstPerson, lastPerson);
        lastPerson = getPerson(getLastPersonId(firstPerson), firstPerson);
        if (!testPerson(firstPerson)) {
            printListEmpty("person");
        }
    /* end person list handling */
    
    /* beginn loan list handling */
        if (!firstLoan || !lastLoan) {
            error("Speicherreservierung fehlgeschlagen f&uuml;r loan list bei 'main()'!");
        }
        firstLoan = addLoanListDataToList(firstLoan, lastLoan, firstPerson, firstItem);
        lastLoan = getLoan(getLastLoanId(firstLoan), firstLoan);
        if (!testLoan(firstLoan)) {
            printListEmpty("loan");
        }
    /* ende loan list handling */
    
    /* begin item list handling */
        if (!firstItem || !lastItem) {
            error("Speicherreservierung fehlgeschlagen f&uuml;r item list bei 'main()'!");
        }
        firstItem = addItemListDataToList(firstItem, lastItem, firstPerson);
        lastItem = getItem(getLastItemId(firstItem), firstItem);
        if (!testItem(firstItem)) {
            printListEmpty("item");
        }
printf("main: Id: %ld<br />", firstItem->id);
    /* end item list handling */
    
    test = sscanf(queryString, "input_radio=%[^&]", input_radio); // test = -1 = EOF wenn es nicht vorkommt, wenn es leer ist 0 und ansonsten Anz. d. Vars die zugeordnet wurden
    
    if (test == EOF || !test) {
        if (strstr(queryString, "aP_first_name=")) {
            test = sscanf(queryString, "aP_first_name=%[^&]&aP_last_name=%[^&]&aP_date=%[^.].%[^.].%[^&]", vorname, nachname, tag, monat, jahr);
            if (test != 5 && !testInputNewPerson(vorname, nachname, atoi(tag), atoi(monat), atoi(jahr)) ) {
                error("Ung&uuml;ltige Eingabe bei 'main()'!");
            }
            lastPerson = inputPerson(firstPerson, lastPerson, vorname, nachname, atoi(tag), atoi(monat), atoi(jahr));
            printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
        } else if (strstr(queryString, "aA_first_name=")) {
            test = sscanf(queryString, "aA_first_name=%[^&]&aA_last_name=%[^&]&aA_date=%[^.].%[^.].%[^&]", vorname, nachname, tag, monat, jahr);
            if (test != 5 && !testInputNewPerson(vorname, nachname, atoi(tag), atoi(monat), atoi(jahr)) ) {
                error("Ung&uuml;ltige Eingabe bei 'main()'!");
            }
            tmpPerson = lastPerson = inputPerson(firstPerson, lastPerson, vorname, nachname, atoi(tag), atoi(monat), atoi(jahr));
            
//            newLoan(firstPerson, lastPerson, tmpPerson);
            printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
        } else if (strstr(queryString, "aA_IS_personVorhanden=")) {
            if (strstr(queryString, "aA_IS_personVorhanden=ja")) {
                viewPersonListWithType(firstPerson, "aA_", "radio");
            } else if (strstr(queryString, "aA_IS_personVorhanden=nein")) {
                viewInputPerson("aA_");
            } else {
                error("Ung&uuml;ltiger Query-String bei 'main():aA_IS_personVorhanden'!");
            }
            printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
        } else if (strstr(queryString, "aA_personId=")) {
            test = sscanf(queryString, "aA_personId=%[^&]", personId);
            if (test != 1) {
                error("'sscanf()' - Fehler bei 'main():aA_personId'!");
            }
            tmpPerson = getPerson(atol(personId), firstPerson);
            if (!tmpPerson) {
                error("Person wurde nicht gefunden!");
            }
            printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
        } else if (strstr(queryString, "dP_personId=")) {
            if (strstr(queryString, "dP_personId=all")) {
                /* Schnellste Art alle Personen zu löschen. */
                firstPerson = NULL;
                writePersonListToData(firstPerson);
                printf("Es wurden erfolgreich alle Personen gel&ouml;scht.<br />");
            } else {
                test = sscanf(queryString, "dP_personId=%[^&]", personId);
                if (test != 1) {
                    error("'sscanf()' - Fehler bei 'main():dP_personId'!");
                }
                firstPerson = deletePersonFromList(getPerson(atol(personId), firstPerson), firstPerson);
                writePersonListToData(firstPerson);
                printf("Person wurde erfolgreich gel&ouml;scht.<br />"); // klappt noch nicht wie es sollte wenn die liste leer ist
                while(1) {
                    queryString = (queryString + strlen("dP_personId=") + strlen(personId) + 1);
                    test = sscanf(queryString, "dP_personId=%[^&]", personId);
                    if (test != 1) {
                        break;
                    }
                    firstPerson = deletePersonFromList(getPerson(atol(personId), firstPerson), firstPerson);
                    writePersonListToData(firstPerson);
                    printf("Person wurde erfolgreich gel&ouml;scht.<br />"); // klappt noch nicht wie es sollte wenn die liste leer ist
                }
            }
            printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
        } else {
            viewMain(firstPerson, firstItem, firstLoan);
        }
    } else {
        // %[^&] bedeutet jedes Zeichen ausgenommen von '&' bzw. '\n' bei sscanf(string, format, vars); wird jedoch nicht bei nur einem Parameter benoetigt
        if (!strcmp(input_radio, "aA")) viewNewLoan(firstPerson);
        if (!strcmp(input_radio, "vA")) viewLoanListWithType(firstLoan, "vA_", "");
        if (!strcmp(input_radio, "dA")) viewDelLoan(firstLoan);
        if (!strcmp(input_radio, "aP")) viewInputPerson("aP_");
        if (!strcmp(input_radio, "vP")) viewPersonListWithType(firstPerson, "", "");
        if (!strcmp(input_radio, "dP")) viewDelPerson(firstPerson); // achtung, kann man nur machen, wenn es keine offenen Ausleihen mehr gibt!
        if (!strcmp(input_radio, "aM")) viewInputItem("aM_");
        if (!strcmp(input_radio, "vM")) viewItemListWithType(firstItem, "", "");
        if (!strcmp(input_radio, "dM")) viewDelItem(firstItem);
        if (!strcmp(input_radio, "dF")) deletePersonenCSV();
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
    }
    
    printf("</body>");
    printf("</html>");
    
    free(personId);
    
    free(input_radio);
    
    free(vorname);
    free(nachname);
    free(tag);
    free(monat);
    free(jahr);
    // auch freePerson / freePersonList!
    //    freePerson(firstPerson);
    //    freePerson(lastPerson);
    
    return 0;
}
