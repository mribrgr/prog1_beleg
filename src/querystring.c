//
//  querystring.c
//  beleg
//
//  Created by mribrgr on 06.01.19.
//  Copyright © 2019 mribrgr. All rights reserved.
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

/* Parses the query-string and redirects to the next functions. */
/* return-value: first Object of the list which got edited. */
void *parseQueryString(t_person* firstPerson, t_item* firstItem, t_loan* firstLoan)
{
    char *queryString = getenv("QUERY_STRING");
    void *firstObj = NULL;
    
    if (strstr(queryString, "search") && strstr(queryString, "id=") && !strstr(queryString, "id=&"))
        functionSearch(firstPerson, firstItem, firstLoan);
    
    else if (strstr(queryString, "viewItem=Submit"))
        functionView("item", firstPerson, firstItem, firstLoan);
    else if (strstr(queryString, "viewPerson=Submit"))
        functionView("person", firstPerson, firstItem, firstLoan);
    else if (strstr(queryString, "viewLoan=Submit"))
        functionView("loan", firstPerson, firstItem, firstLoan);
    
    else if (strstr(queryString, "addItem=Submit"))
        functionAdd("item", firstPerson, firstItem, firstLoan);
    else if (strstr(queryString, "addPerson=Submit"))
        functionAdd("person", firstPerson, firstItem, firstLoan);
    else if (strstr(queryString, "addLoan=Submit"))
        functionAdd("loan", firstPerson, firstItem, firstLoan);
    
    else if (strstr(queryString, "deleteItem=Submit"))
        firstObj = functionDelete("item" , firstPerson, firstItem, firstLoan);
    else if (strstr(queryString, "deletePerson=Submit"))
        firstObj = functionDelete("person", firstPerson, firstItem, firstLoan);
    else if (strstr(queryString, "deleteLoan=Submit"))
        firstObj = functionDelete("loan" , firstPerson, firstItem, firstLoan);
    
    else viewMain(firstPerson, firstItem, firstLoan);
    
    return firstObj;
}

/* structure == "person" | "item" | "loan" */
/* Displays the <structure>-list to the screen. */
void functionView(char *structure, t_person* firstPerson, t_item* firstItem, t_loan* firstLoan)
{
    if (!strcmp(structure, "person")) {
        viewPersonListWithType(firstPerson, "viewPerson", "", 0);
    }
    else if (!strcmp(structure, "item")) {
        viewItemListWithType(firstItem, "viewItem", "", 0, firstPerson, "");
    }
    else if (!strcmp(structure, "loan")) {
        viewLoanListWithType(firstLoan, "viewLoan", "", 0);
    }
    
    printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    
    return;
}

/* structure == "person" | "item" | "loan" */
/* Adds one element from the <structure>-list. */
void functionAdd(char *structure, t_person* firstPerson, t_item* firstItem, t_loan* firstLoan)
{
    char *queryString = getenv("QUERY_STRING");
    int test = 0;
    
    if (strstr(queryString, "personId=")) {
        char *personId = malloc(sizeof(unsigned long));
        if (!personId) error("Storage couldn't get reserved in 'functionAdd()'!");
        test = sscanf(queryString, "personId=%[^&]", personId);
        if (test != 1) error("person-id not found at 'functionAdd()'!");
        viewExist("item", "addLoan", personId);
        free(personId);
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    } else if (strstr(queryString, "itemId=")) {
        char *personId = malloc(sizeof(unsigned long));
        char *itemId = malloc(sizeof(unsigned long));
        
        if (!itemId || !personId) error("Storage couldn't get reserved in 'functionAdd()'!");
        
        test = sscanf(queryString, "%[^_]_itemId=%[^&]", personId, itemId);
        if (test != 2) error("Invalid item-id!");
        viewInputLoan("addLoan", personId, itemId);
        
        free(personId);
        free(itemId);
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    } else if (strstr(queryString, "EXIST_person=")) {
        if (strstr(queryString, "EXIST_person=true")) viewPersonListWithType(firstPerson, "addLoan", "radio", 0);
        else if (strstr(queryString, "EXIST_person=false")) viewInputPerson("addLoan");
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    } else if (strstr(queryString, "EXIST_item=")) {
        char *personId = malloc(sizeof(unsigned long));
        if (!personId) error("Storage couldn't get reserved in 'functionAdd()'!");
        test = sscanf(queryString, "%[^_]_EXIST_item=", personId);
        if (test != 1) error("'sscanf()' - Fehler bei 'main():personId'!");
        if (strstr(queryString, "EXIST_item=true")) viewItemListWithType(firstItem, "addLoan", "radio", 0, firstPerson, personId);
        else if (strstr(queryString, "EXIST_item=false")) viewInputItem("addLoan", personId);
        free(personId);
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    } else if (strstr(queryString, "loan_begin=") && strstr(queryString, "loan_end=")) {
        t_person *tmpPerson = NULL;
        t_item *tmpItem = NULL;
        
        char *personId = malloc(sizeof(unsigned long));
        char *itemId = malloc(sizeof(unsigned long));
        char *loan_begin_day = malloc(sizeof(char) * strlen(queryString));
        char *loan_begin_month = malloc(sizeof(char) * strlen(queryString));
        char *loan_begin_year = malloc(sizeof(char) * strlen(queryString));
        char *loan_end_day = malloc(sizeof(char) * strlen(queryString));
        char *loan_end_month = malloc(sizeof(char) * strlen(queryString));
        char *loan_end_year = malloc(sizeof(char) * strlen(queryString));
        
        if (!personId||!itemId||!loan_begin_day||!loan_begin_month||!loan_begin_year||!loan_end_day||!loan_end_month||!loan_end_year)
            error("Storage couldn't get reserved in 'functionAdd()'!");
        
        test = sscanf(queryString, "%[^_]_%[^_]_loan_begin=%[^.].%[^.].%[^&]&loan_end=%[^.].%[^.].%[^&]", personId, itemId, loan_begin_day, loan_begin_month, loan_begin_year, loan_end_day, loan_end_month, loan_end_year);
        if (test != 8) error("Invalid input at 'functionAdd()'!");
        
        tmpPerson = (t_person *) getObj(atol(personId), firstPerson);
        tmpItem = (t_item *) getObj(atol(itemId), firstItem);
        if (!tmpPerson) error("person couldn't get found at 'functionAdd()'!");
        if (!tmpItem) error("item couldn't get found at 'functionAdd()'!");
        
        inputLoan(firstLoan, tmpPerson, tmpItem, atoi(loan_begin_day), atoi(loan_begin_month), atoi(loan_begin_year), atoi(loan_end_day), atoi(loan_end_month), atoi(loan_end_year), firstItem);
        
        free(personId);
        free(itemId);
        free(loan_begin_day);
        free(loan_begin_month);
        free(loan_begin_year);
        free(loan_end_day);
        free(loan_end_month);
        free(loan_end_year);
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    } else if (strstr(queryString, "first_name=") && strstr(queryString, "last_name=") && strstr(queryString, "date=")) {
        char *vorname = malloc(sizeof(char) * strlen(queryString));
        char *nachname = malloc(sizeof(char) * strlen(queryString));
        char *tag = malloc(sizeof(char) * strlen(queryString));
        char *monat = malloc(sizeof(char) * strlen(queryString));
        char *jahr = malloc(sizeof(char) * strlen(queryString));

        if (!vorname || !nachname || !tag || !monat || !jahr)
            error("Storage couldn't get reserved in 'functionAdd()'!");
        
        test = sscanf(queryString, "first_name=%[^&]&last_name=%[^&]&date=%[^.].%[^.].%[^&]", vorname, nachname, tag, monat, jahr);
        if (test != 5) error("Invalid input at 'functionAdd()'!");
        if (!strcmp(structure, "loan")) {
            t_person* tmpPerson = NULL;
            tmpPerson = inputPerson(firstPerson, vorname, nachname, atoi(tag), atoi(monat), atoi(jahr));
            char *buf = malloc(sizeof(char) * 64);
            sprintf(buf, "%ld", tmpPerson->id);
            viewExist("item", "addLoan", buf);
            free(buf);
        }
        if (!strcmp(structure, "person")) {
            inputPerson(firstPerson, vorname, nachname, atoi(tag), atoi(monat), atoi(jahr));
        }
        free(vorname);
        free(nachname);
        free(tag);
        free(monat);
        free(jahr);
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    } else if (strstr(queryString, "name=") && strstr(queryString, "type=") && strstr(queryString, "author=")) {
        char *name = malloc(sizeof(char) * strlen(queryString));
        char *type = malloc(sizeof(char) * strlen(queryString));
        char *author = malloc(sizeof(char) * strlen(queryString));
        char *personId = malloc(sizeof(unsigned long));
    
        if (!personId || !name || !type || !author) error("Storage couldn't get reserved in 'functionAdd()'!");
    
        test = sscanf(queryString, "%[^_]_name=%[^&]&type=%[^&]&author=%[^&]", personId, name, type, author);
        if (!test) {
            test = sscanf(queryString, "_name=%[^&]&type=%[^&]&author=%[^&]", name, type, author);
            if (test < 2) error("Invalid input given to 'functionAdd()'!");
        } else {
            if (test < 3) error("Invalid input given to 'functionAdd()'!");
        }
        if (!strcmp(structure, "loan")) {
            t_item *tmpItem = NULL;
            tmpItem = inputItem(firstItem, name, type, author);
            char *itemId = malloc(sizeof(unsigned long));
            sprintf(itemId, "%ld", tmpItem->id);
            viewInputLoan("addLoan", personId, itemId);
            free(itemId);
        }
        if (!strcmp(structure, "item")) {
            inputItem(firstItem, name, type, author);
        }
        
        free(personId);
        free(name);
        free(type);
        free(author);
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    }
    
    else viewMain(firstPerson, firstItem, firstLoan);
    
    return;
}

/* structure == "person" | "item" | "loan" */
/* Deletes one element from the <structure>-list. */
void *functionDelete(char *structure, t_person* firstPerson, t_item* firstItem, t_loan* firstLoan)
{
    char *queryString = getenv("QUERY_STRING");
    void *firstObj = NULL;
    
    if (strstr(queryString, "Id=")) {
        if (strstr(queryString, "Id=all")) {
            /* Fastest way to clean up everything. */
            if ((!strcmp(structure, "person") || !strcmp(structure, "item")) && testObj(firstLoan)) {
                printf("All %ss couldn't get deleted, 'cause there are connected loans left!<br />", structure);
            } else {
                writeObjListToData(structure, NULL);
                printf("All %ss deleted successfully.<br />", structure);
                
                if (!strcmp(structure, "loan")) {
                    t_item *tmpItem = firstItem;
                    while (tmpItem) {
                        tmpItem->person = NULL;
                        tmpItem = tmpItem->next;
                    }
                    writeObjListToData("item", firstItem);
                }
            }
        } else {
            int test = 0;
            char *identifier = malloc(sizeof(unsigned long));
            if (!identifier) error("Storage couldn't get reserved in 'functionDelete()'!");
            
            if (!strcmp(structure, "item")) firstObj = firstItem;
            if (!strcmp(structure, "person")) firstObj = firstPerson;
            if (!strcmp(structure, "loan")) firstObj = firstLoan;
            
            char buf[64], *token;
            token = strtok(queryString, "&\0");
            sprintf(buf, "_%sId=", structure);
            strcat(buf, "%[^&]");
            test = sscanf(token, buf, identifier);
            if (test != 1)
            {
                sprintf(buf, "%sId=", structure);
                strcat(buf, "%[^&]");
                test = sscanf(token, buf, identifier);
                if (test != 1) error("Invalid !");
            }
            
            if (firstLoan->id && (!strcmp(structure, "person") || !strcmp(structure, "item")) && !testLoanObj(firstLoan, structure, atol(identifier))) {
                printf("The %s with the id %s couldn't get deleted, 'cause there are connected loans left!<br />", structure, identifier);
            } else {
                firstObj = deleteObjFromList(structure, getObj(atol(identifier), firstObj), firstObj);
                writeObjListToData(structure, firstObj);
                printf("%s %ld deleted successfully.<br />", structure, atol(identifier));
                while (1) {
                    token = strtok(NULL, "&\0");
                    if (!token) {
                        break;
                    }
                    sprintf(buf, "_%sId=", structure);
                    strcat(buf, "%[^&]");
                    test = sscanf(token, buf, identifier);
                    if (test != 1)
                    {
                        sprintf(buf, "%sId=", structure);
                        strcat(buf, "%[^&]");
                        test = sscanf(token, buf, identifier);
                        if (test != 1) break;
                    }
                    if (firstLoan->id && (!strcmp(structure, "person") || !strcmp(structure, "item")) && !testLoanObj(firstLoan, structure, atol(identifier)))
                        printf("The %s with the id %s couldn't get deleted, 'cause there are connected loans left!<br />", structure, identifier);
                    else {
                        firstObj = deleteObjFromList(structure, getObj(atol(identifier), firstObj), firstObj);
                        writeObjListToData(structure, firstObj);
                        
                        printf("%s %ld deleted successfully.<br />", structure, atol(identifier));
                    }
                }
            }
            if (!strcmp(structure, "loan")) writeObjListToData("item", firstItem);
            free(identifier);
        }
    }
    printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    
    return firstObj;
}

/* Searches for an element and prints the searched element in bold-text-style. */
void functionSearch(t_person *firstPerson, t_item *firstItem, t_loan *firstLoan)
{
    char *queryString = getenv("QUERY_STRING");
    int test = 0;
    
    char *prefix = malloc(sizeof(char) * strlen(queryString));
    char *function = malloc(sizeof(char) * strlen(queryString));
    char *structure = malloc(sizeof(char) * strlen(queryString));
    char *type = malloc(sizeof(char) * strlen(queryString));
    char *searchId = malloc(sizeof(unsigned long));
    
    if (!prefix||!function||!structure||!type) {
        error("Storage couldn't get reserved in 'stringReplace()'!");
    }
    
    queryString = strstr(queryString, "search");
    sscanf(queryString, "search_%[^_]_%[^_]_%[^_]_id=%[^&]&%[^=]=Submit", prefix, type, structure, searchId, function);
    if (strcmp(prefix, "+")) test++;
    if (strcmp(function, "+")) test++;
    if (strcmp(type, "+")) test++;
    if (strcmp(structure, "+")) test++;
    if (atoi(searchId)) test++;
    
    printf("<a href='#bold'>Jump to searched element</a><br />");
    
    switch (test) {
        case 3:
            if (!strcmp(structure, "person")) {
                viewPersonListWithType(firstPerson, function, "", atoi(searchId));
            }
            else if (!strcmp(structure, "item")) {
                viewItemListWithType(firstItem, function, "", atoi(searchId), firstPerson, prefix);
            }
            else if (!strcmp(structure, "loan")) {
                viewLoanListWithType(firstLoan, function, "", atoi(searchId));
            }
            else error("Invalid structure given to 'functionSearch()'!");
            break;
        case 4:
            if (!strcmp(structure, "person")) {
                viewPersonListWithType(firstPerson, function, type, atoi(searchId));
            }
            else if (!strcmp(structure, "item")) {
                viewItemListWithType(firstItem, function, type, atoi(searchId), firstPerson, "");
            }
            else error("Invalid structure given to 'functionSearch()'!");
            break;
        case 5:
            if (!strcmp(structure, "item")) {
                viewItemListWithType(firstItem, function, type, atoi(searchId), firstPerson, prefix);
            }
            else error("Invalid structure given to 'functionSearch()'!");
            break;
        default:
            error("Invalid input given to 'functionSearch()'!");
            break;
    }
    
    printf("<a href='#bold'>Jump to searched element</a><br />");
    
    printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    
    free(prefix);
    free(function);
    free(structure);
    free(type);
    free(searchId);
    
    return;
}
