//
//  main.c
//  beleg
//
//  Created by mribrgr on 12.12.18.
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

/* Prints an error message if an error occurs. */
void error(char *msg)
{
    printError(msg);
    printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    printf("</body>");
    printf("</html>");
    exit(1);
    
    return;
}

/* Prints a warning. */
void warning(char *msg)
{
    printWarning(msg);
    
    return;
}

/* main function */
int main(void)
{
    int test;
    char *queryString = getenv("QUERY_STRING");
    
    printf("Content-Type: text/html\n\n");
    printf("<html>");
    printf("<head>");
    printf("<title>Library</title>");
    printf("<link href='style.css' rel='stylesheet' type='text/css'>");
    printf("</head>");
    printf("<body>");
    
    if (!queryString) error("Query-String is undefined!");
    
    char *input_radio = malloc(sizeof(char) * strlen(queryString));
    if (!input_radio) error("Storage couldn't get reserved in 'stringReplace()'!");
    
    t_person *firstPerson = malloc(sizeof(t_person));
    char *personId = malloc(sizeof(unsigned long));
    
    t_loan *firstLoan = malloc(sizeof(t_loan));
    char *loanId = malloc(sizeof(unsigned long));
    
    t_item *firstItem = malloc(sizeof(t_loan));
    char *itemId = malloc(sizeof(unsigned long));
    
    if (!firstPerson || !firstItem || !firstLoan || !personId || !loanId || !itemId) error("Storage couldn't get reserved in 'main()'!");
    firstPerson = (t_person *) addObjListDataToList("person", firstPerson, firstItem, firstLoan);
    firstItem = (t_item *) addObjListDataToList("item", firstPerson, firstItem, firstLoan);
    firstLoan = (t_loan *) addObjListDataToList("loan", firstPerson, firstItem, firstLoan);
    
    test = sscanf(queryString, "input_radio=%[^&]", input_radio);
    
    if (test == EOF || !test) {
        void *firstObj = parseQueryString(firstPerson, firstItem, firstLoan);
        if (firstObj) {
            if (!strncmp(queryString, "p", 1)) firstPerson = firstObj;
            if (!strncmp(queryString, "i", 1)) firstItem = firstObj;
            if (!strncmp(queryString, "l", 1)) firstLoan = firstObj;
        }
        
    } else {
        if (!strcmp(input_radio, "addLoan")) {
            if (!testObj(firstPerson)) viewInputPerson("addLoan");
            else viewExist("person", "addLoan", "");
        }
        if (!strcmp(input_radio, "viewLoan")) viewLoanListWithType(firstLoan, "viewLoan", "", 0);
        if (!strcmp(input_radio, "deleteLoan")) viewLoanListWithType(firstLoan, "deleteLoan", "checkbox", 0);
        
        if (!strcmp(input_radio, "addPerson")) viewInputPerson("addPerson");
        if (!strcmp(input_radio, "viewPerson")) viewPersonListWithType(firstPerson, "viewPerson", "", 0);
        if (!strcmp(input_radio, "deletePerson")) viewPersonListWithType(firstPerson, "deletePerson", "checkbox", 0);
        
        if (!strcmp(input_radio, "addItem")) viewInputItem("addItem", "");
        if (!strcmp(input_radio, "viewItem")) viewItemListWithType(firstItem, "viewItem", "", 0, firstPerson, "");
        if (!strcmp(input_radio, "deleteItem")) viewItemListWithType(firstItem, "deleteItem", "checkbox", 0, firstPerson, "");
        
        printf("<a href='https://www2.htw-dresden.de/~s79149/beleg.cgi'>back to the homepage</a><br />");
    }
    printf("</body>");
    printf("</html>");
    
    free(personId);
    free(itemId);
    free(loanId);
    
    free(input_radio);
    
    if (firstPerson) if (firstPerson->next) freeObjList("person", firstPerson);
    if (firstItem) if (firstItem->next) freeObjList("item", firstItem);
    if (firstLoan) if (firstLoan->next) freeObjList("loan", firstLoan);
    
    return 0;
}
