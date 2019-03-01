//
//  main.h
//  beleg
//  46139
//  Created by Mauritius Berger on 31.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef main_h
#define main_h

#define MAX_LINE_SIZE 64
#define MAX_SIZE_STRING 128

#define MODE_PERCENT_PLUS 0
#define MODE_COMMA_DOT 1

typedef struct item t_item;
typedef struct person t_person;
typedef struct date t_date;
typedef struct loan t_loan;

/* Print error / warnings */
void error(char *msg);      void printError(char *msg);
void warning(char *msg);    void printWarning(char *msg);

/* general view functions */
void viewMain (t_person *firstPerson, t_item *firstItem, t_loan* firstLoan);
void viewExist(char *structure, char *function, char *prefix);

/* general functions */
void *functionDelete(char *structure, t_person* firstPerson, t_item* firstItem, t_loan* firstLoan);
void  functionAdd   (char *structure, t_person *firstPerson, t_item *firstItem, t_loan *firstLoan);
void  functionView  (char *structure, t_person *firstPerson, t_item *firstItem, t_loan *firstLoan);
void  functionSearch(t_person *firstPerson, t_item *firstItem, t_loan *firstLoan);

/* parse the querystring */
void *parseQueryString(t_person* firstPerson, t_item* firstItem, t_loan* firstLoan);

/* print messages to the screen */
void printAddSuccess(char *string);
void printListEmpty(char *string);

/* validate inputs */
int testInputNewPerson(char *vorname, char *nachname, int tag, int monat, int jahr);
int testInputNewItem  (char *name, char *type, char *author);
int testInputNewLoan  (int tag, int monat, int jahr, int tag2, int monat2, int jahr2);
int testInputDate     (int tag, int monat, int jahr);
int testName          (char *name);
int testObj           (void *input);

/* general list & data management */
void *getObj              (unsigned long identifier, void *firstObj);
void  appendObjToData     (char *structure, void *tmp);
void  writeObjToData      (char *structure, FILE *filePointer, void *tmpObj);
void  writeObjListToData  (char *structure, void *tmp);
void  addObjToList        (void *beforeObj, void *inputObj);
void *addObjListDataToList(char *structure, t_person *firstPerson, t_item *firstItem, t_loan *firstLoan);
void *deleteObjFromList   (char *structure, void *tmpObj, void *firstObj);

/* functions for clearing the storage */
void freeObj    (char *structure, void *tmpObj);
void freeObjList(char *structure, void *firstObj);

/* ID-handling */
unsigned long getMaxObjId (void *firstObj);
unsigned long getLastObjId(void *firstObj);

/* string handling */
char *stringReplace(char *string, int position, char *new);
char *checkString  (char *string, int mode);

#endif /* main_h */
