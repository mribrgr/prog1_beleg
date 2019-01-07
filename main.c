//
//  main.c
//  beleg
//
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

//
//  Prefixe: // sollten später noch ersetzt werden durch etwas besseres (unübersichtliche URL)
//  .A_    add...    ||  a._    ...loan
//  .D_    del...    ||  p._    ...person
//  .V_    view...   ||  m._    ...item
//


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
    
    /* begin person list handling */
        if (!firstPerson || !lastPerson) {
            error("Speicherreservierung fehlgeschlagen f&uuml;r person list bei 'main()'!");
        }
        firstPerson = (t_person*) addObjListDataToList("person", firstPerson, firstItem, firstLoan, lastPerson);
        lastPerson = getObj(getLastObjId(firstPerson), firstPerson);
    /* end person list handling */
    
    /* beginn loan list handling */
        if (!firstLoan || !lastLoan) {
            error("Speicherreservierung fehlgeschlagen f&uuml;r loan list bei 'main()'!");
        }
        firstLoan = (t_loan*) addObjListDataToList("loan", firstPerson, firstItem, firstLoan, lastLoan);
        lastLoan = getObj(getLastObjId(firstLoan), firstLoan);
    /* ende loan list handling */
    
    /* begin item list handling */
        if (!firstItem || !lastItem) {
            error("Speicherreservierung fehlgeschlagen f&uuml;r item list bei 'main()'!");
        }
        firstItem = (t_item*) addObjListDataToList("item", firstPerson, firstItem, firstLoan, lastPerson);
        lastItem = getObj(getLastObjId(firstItem), firstItem);
    /* end item list handling */
    
    test = sscanf(queryString, "input_radio=%[^&]", input_radio); // test = -1 = EOF wenn es nicht vorkommt, wenn es leer ist 0 und ansonsten Anz. d. Vars die zugeordnet wurden
    
    if (test == EOF || !test) {
        parseQueryString(firstPerson, firstItem, firstLoan);
        
    } else {
        // %[^&] bedeutet jedes Zeichen ausgenommen von '&' bzw. '\n' bei sscanf(string, format, vars); wird jedoch nicht bei nur einem Parameter benoetigt
        if (!strcmp(input_radio, "addLoan")) viewNewLoan(firstPerson);
        if (!strcmp(input_radio, "viewLoan")) viewLoanListWithType(firstLoan, "viewLoan", "");
        if (!strcmp(input_radio, "deleteLoan")) viewDelLoan(firstLoan);
        
        if (!strcmp(input_radio, "addPerson")) viewInputPerson("addPerson");
        if (!strcmp(input_radio, "viewPerson")) viewPersonListWithType(firstPerson, "viewPerson", "");
        if (!strcmp(input_radio, "deletePerson")) viewDelPerson(firstPerson); // achtung, kann man nur machen, wenn es keine offenen Ausleihen mehr gibt!
        
        if (!strcmp(input_radio, "addItem")) viewInputItem("addItem");
        if (!strcmp(input_radio, "viewItem")) viewItemListWithType(firstItem, "viewItem", "");
        if (!strcmp(input_radio, "deleteItem")) viewDelItem(firstItem);
        
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>zur&uuml;ck zur Startseite</a><br />");
    }
    
    printf("</body>");
    printf("</html>");
    
    free(personId);
    free(itemId);
    free(loanId);
    
    free(input_radio);
    // auch freePerson / freePersonList!
    //    freePerson(firstPerson);
    //    freePerson(lastPerson);
    
    return 0;
}
