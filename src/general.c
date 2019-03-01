//
//  general.c
//  beleg
//
//  Created by mribrgr on 04.01.19.
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

/* Tests the <input>-object. */
int testObj (void *input)
{
    t_loan *tmp = input;
    if (tmp) {
        if (tmp->id) {
            return 1;
        }
    }
    
    return 0;
}

/* Returns the <firstObj>-Object with the id <identifier>. */
void *getObj (unsigned long identifier, void *firstObj)
{
    if (!testObj((t_loan*) firstObj)) {
        return NULL;
    }
    
    t_loan *currObj = (t_loan*) firstObj;
    if (currObj->id == identifier) {
        return currObj;
    }
    currObj = currObj->next;
    while(currObj) {
        if (currObj->id == identifier) {
            return currObj;
        }
        currObj = currObj->next;
    }
    
    return NULL;
}

void appendObjToData (char *structure, void *tmp)
{
    FILE *filePointer;
    char buf[64];
    
    if (!testObj(tmp)) {
        return;
    }
    sprintf(buf, "%s.csv", structure);
    
    filePointer = fopen(buf, "a");
    if (!filePointer) {
        sprintf(buf, "'%s.csv' couldn't get opened at 'appendObjToData()'!", structure);
        error(buf);
    }
    
    if (!strcmp(structure, "item")) {
        t_item *tmpObj = (t_item*) tmp;
        writeObjToData(structure, filePointer, tmpObj);
        fprintf(filePointer, "\n");
    } else if (!strcmp(structure, "loan")) {
        t_loan *tmpObj = (t_loan*) tmp;
        writeObjToData(structure, filePointer, tmpObj);
    } else if (!strcmp(structure, "person")) {
        t_person *tmpObj = (t_person*) tmp;
        writeObjToData(structure, filePointer, tmpObj);
    }
    
    fclose(filePointer);
    
    return;
}

/* Writes the <structure>-list to the <structure>.csv. */
void writeObjListToData (char *structure, void *tmp)
{
    FILE *filePointer;
    char buf[64];
    
    sprintf(buf, "%s.csv", structure);
    filePointer = fopen(buf, "w");
    if (!filePointer) {
        sprintf(buf, "'%s.csv' couldn't get opened at 'writeObjListToData()'!", structure);
        error(buf);
    }
    
    if (testObj(tmp)) {
        if (!strcmp(structure, "item")) writeObjToData(structure, filePointer, (t_item*) tmp);
        else if (!strcmp(structure, "loan")) writeObjToData(structure, filePointer, (t_loan*) tmp);
        else if (!strcmp(structure, "person")) writeObjToData(structure, filePointer, (t_person*) tmp);
        
        while(((t_loan*) tmp)->next) {
            tmp = ((t_loan*) tmp)->next;
            if (testObj(tmp)) {
                if (!strcmp(structure, "item")) writeObjToData(structure, filePointer, (t_item*) tmp);
                else if (!strcmp(structure, "loan")) writeObjToData(structure, filePointer, (t_loan*) tmp);
                else if (!strcmp(structure, "person")) writeObjToData(structure, filePointer, (t_person*) tmp);
            }
        }
    }
    
    fclose(filePointer);
    
    return;
}

void writeObjToData(char *structure, FILE *filePointer, void *tmpObj)
{
    if (!strcmp(structure, "loan")) {
        fprintf(filePointer,"%ld", ((t_loan*) tmpObj)->id);
        fprintf(filePointer,",%ld", ((t_loan*) tmpObj)->person->id);
        fprintf(filePointer,",%d.%d.%d", ((t_loan*) tmpObj)->loan_begin->day, ((t_loan*) tmpObj)->loan_begin->month, ((t_loan*) tmpObj)->loan_begin->year);
        fprintf(filePointer,",%d.%d.%d", ((t_loan*) tmpObj)->loan_end->day, ((t_loan*) tmpObj)->loan_end->month, ((t_loan*) tmpObj)->loan_end->year);
    }
    if (!strcmp(structure, "item")) {
        fprintf(filePointer,"%ld", ((t_item*) tmpObj)->id);
        if (!((t_item *) tmpObj)->person) fprintf(filePointer, ",0");
        else fprintf(filePointer,",%ld", ((t_item*) tmpObj)->person->id);
        fprintf(filePointer,",%s", ((t_item*) tmpObj)->name);
        fprintf(filePointer,",%s", ((t_item*) tmpObj)->type);
        fprintf(filePointer,",%s", ((t_item*) tmpObj)->author);
    }
    if (!strcmp(structure, "person")) {
        fprintf(filePointer,"%ld", ((t_person*) tmpObj)->id);
        fprintf(filePointer,",%s", ((t_person*) tmpObj)->first_name);
        fprintf(filePointer,",%s", ((t_person*) tmpObj)->last_name);
        fprintf(filePointer,",%d.%d.%d", ((t_person*) tmpObj)->gebDatum->day, ((t_person*) tmpObj)->gebDatum->month, ((t_person*) tmpObj)->gebDatum->year);
    }
    if (!strcmp(structure, "loan") || !strcmp(structure, "person")) fprintf(filePointer, "\n");
    
    return;
}

void *addObjListDataToList(char *structure, t_person *firstPerson, t_item *firstItem, t_loan *firstLoan)
{
    FILE *filePointer;
    void *tmpObj = NULL;
    int first = 0;
    char buf[128];
    
    if ( !strcmp(structure, "item") && (!firstItem) ) return NULL;
    else if ( !strcmp(structure, "person") && (!firstPerson) ) return NULL;
    else if ( !strcmp(structure, "loan") && (!firstLoan) ) return NULL;
    
    sprintf(buf, "%s.csv", structure);
    filePointer = fopen(buf, "r");
    if (!filePointer) {
        sprintf(buf, "'%s.csv' couldn't get opened at 'addObjListDataToList()'.", structure);
        warning(buf);
        return NULL;
    }
    while (1) {
        if (!strcmp(structure, "item")) tmpObj = getItemFromData(filePointer, firstPerson, firstItem);
        if (!strcmp(structure, "loan")) tmpObj = getLoanFromData(filePointer, firstPerson, firstItem);
        if (!strcmp(structure, "person")) tmpObj = getPersonFromData(filePointer);
        if (!tmpObj) {
            break;
        }
        if (!first) {
            if (!strcmp(structure, "item")) firstItem = tmpObj;
            if (!strcmp(structure, "loan")) firstLoan = tmpObj;
            if (!strcmp(structure, "person")) firstPerson = tmpObj;
            first = 1;
        } else {
            if (!strcmp(structure, "item")) addObjToList((t_item*) getObj(getLastObjId(firstItem), firstItem), (t_item*) tmpObj);
            if (!strcmp(structure, "loan")) addObjToList((t_loan*) getObj(getLastObjId(firstLoan), firstLoan), (t_loan*) tmpObj);
            if (!strcmp(structure, "person")) addObjToList((t_person*) getObj(getLastObjId(firstPerson), firstPerson), (t_person*) tmpObj);
        }
    }
    
    fclose(filePointer);
    
    if (!strcmp(structure, "item")) return firstItem;
    else if (!strcmp(structure, "loan")) return firstLoan;
    else if (!strcmp(structure, "person")) return firstPerson;
    
    return NULL;
}

void *deleteObjFromList(char *structure, void *tmpObj, void *firstObj)
{
    if (!testObj(tmpObj)) {
        return firstObj;
    }
    
    if (!strcmp(structure, "loan")) {
        ((t_loan *) tmpObj)->item->person = NULL;
    }
    
    if (!((t_loan*) tmpObj)->before && ((t_loan*) tmpObj)->next) { /* begin of the list */
        firstObj = ((t_loan*) tmpObj)->next;
        ((t_loan*) tmpObj)->next->before = NULL;
    } else if (((t_loan*) tmpObj)->before && !((t_loan*) tmpObj)->next) { /* end of the list */
        ((t_loan *) tmpObj)->before->next = NULL;
        ((t_loan*) tmpObj)->before = NULL;
    } else if (((t_loan*) tmpObj)->before && ((t_loan*) tmpObj)->next) { /* in the mid of the list */
        ((t_loan*) tmpObj)->before->next = ((t_loan*) tmpObj)->next;
        ((t_loan*) tmpObj)->next->before = ((t_loan*) tmpObj)->before;
    } else { /* tmpObj is the first element from the list */
        firstObj = NULL;
    }
    
    freeObj(structure, tmpObj);
    
    return firstObj;
}

/* Clears the storage for the <tmpObj>. */
void freeObj(char *structure, void *tmpObj)
{
    if (!testObj(tmpObj)) {
        return;
    }
    
    if (!strcmp(structure, "item")) {
        free(((t_item*) tmpObj)->name);
        free(((t_item*) tmpObj)->type);
        if (strlen(((t_item *) tmpObj)->author) > 0) free(((t_item*) tmpObj)->author);
    }
    if (!strcmp(structure, "person")) {
        free(((t_person*) tmpObj)->first_name);
        free(((t_person*) tmpObj)->last_name);
    }
    
    ((t_loan *)tmpObj)->id = 0;
    free(tmpObj);
    tmpObj = NULL;
    
    return;
}

/* Clears the storage for the Object-list given into with the first Element <firstObj>. */
void freeObjList(char *structure, void *firstObj)
{
    if (!testObj(firstObj)) {
        return;
    }
    
    t_loan *tmpObj = ((t_loan*) firstObj)->next;
    if (tmpObj) {
        while (((t_loan *) tmpObj)->next) {
            tmpObj = ((t_loan *) tmpObj)->next;
            if (!testObj(((t_loan*) tmpObj)->before)) freeObj(structure, ((t_loan*) tmpObj)->before);
        }
        if (!testObj(tmpObj)) freeObj(structure, tmpObj);
    }
    if (!testObj(tmpObj)) freeObj(structure, firstObj);
    
    return;
}

void addObjToList(void *beforeObj, void *inputObj)
{
    if (!testObj(inputObj) || ((!beforeObj && inputObj))) {
        return;
    }
    
//    if (((t_loan*) beforeObj)->next) {
//        ((t_loan*) beforeObj)->next->before = inputObj;
//        ((t_loan*) inputObj)->next = ((t_loan*) beforeObj)->next;
//    }
    ((t_loan*) inputObj)->before = beforeObj;
    ((t_loan*) beforeObj)->next = inputObj;
    
    return;
}

/* returns the highest id */
unsigned long getMaxObjId(void *firstObj)
{
    unsigned long curr;
    t_loan *tmpObj = firstObj;
    
    if (!testObj(firstObj)) {
        return 0;
    }
    
    curr = tmpObj->id;
    
    while (tmpObj) {
        if (curr < tmpObj->id) {
            curr = tmpObj->id;
        }
        tmpObj = tmpObj->next;
    }
    
    return curr;
}

/* returns the last id */
unsigned long getLastObjId(void *firstObj)
{
    t_loan *tmpObj = firstObj;
    
    if (!testObj(firstObj)) {
        return 0;
    }
    
    while (tmpObj->next) {
        tmpObj = tmpObj->next;
    }
    
    return tmpObj->id;
}

/* converts %XX or + to valid characters and returns the valid string or "" else. */
/*  see modes in main.h */
char *checkString(char *string, int mode)
{
    int i;
    
    for (i=0; i<MAX_SIZE_STRING && string[i]!='\0'; i++) {
        switch (mode) {
            case MODE_PERCENT_PLUS:
                if (!isalnum(string[i]) && string[i]!='%' && string[i]!='+') {
                    return "";
                }
                if (string[i]=='+') {
                    string[i] = ' ';
                }
                if (string[i]=='%') {
                    char hex[3];
                    hex[0] = string[i+1];
                    hex[1] = string[i+2];
                    hex[2] = '\0';
                    char comp[7];
                    comp[0] = '&';
                    strcpy((comp+2), "uml;");
                    
                    if (!strcmp(hex, "E4\0"))
                        comp[1] = 'a';
                    else if (!strcmp(hex, "F6\0"))
                        comp[1] = 'o';
                    else if (!strcmp(hex, "FC\0"))
                        comp[1] = 'u';
                    else if (!strcmp(hex, "C4\0"))
                        comp[1] = 'A';
                    else if (!strcmp(hex, "D6\0"))
                        comp[1] = 'O';
                    else if (!strcmp(hex, "DC\0"))
                        comp[1] = 'U';
                    else
                        error("Invalid letter at 'checkString()'!");
                    
                    string = stringReplace(string, i, comp);
                    i+=6;
                }
                break;
            case MODE_COMMA_DOT:
                if (!isalnum(string[i]) && string[i]!=',' && string[i]!='.' && string[i]!='\n' && string[i]!='&' && string[i]!=';' && string[i]!=' ') {
                    return "";
                }
                break;
                
            default:
                break;
        }
        
    }
    
    return string;
}

char *stringReplace(char *string, int position, char *new)
{
    char *temp = malloc(sizeof(char) * MAX_SIZE_STRING + 3);
    if (!temp)
        error("Storage couldn't get reserved in 'stringReplace()'!");
    
    strcpy(temp, string);
    strcpy((temp+position), new);
    strcpy((temp+position+6), (string+position+3));
    
    free(string);
    
    return temp;
}
