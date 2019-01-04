//
//  main.h
//  beleg
//
//  Created by Mauritius Berger on 31.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef main_h
#define main_h

typedef struct item t_item;
typedef struct person t_person;
typedef struct date t_date;
typedef struct loan t_loan;

/* Funktionen zur Anzeige von Fehlermeldungen und Warnungen */
void error(char* msg);
void warning(char* msg);

/* Funktionen für die Anzeige */
void viewMain(t_person* firstPerson, t_item* firstItem, t_loan* firstLoan);

/* Print Funktionen */
void printError(char* msg);
void printWarning(char* msg);

void printAddSuccess(char* string);
void printListEmpty(char* string);
void printNotFound(char* string);

/* input functions */
int testInputNewPerson(char* vorname, char* nachname, int tag, int monat, int jahr);

#endif /* main_h */
