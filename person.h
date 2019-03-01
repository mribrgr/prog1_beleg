//
//  person.h
//  beleg
//  46139
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef person_h
#define person_h

typedef struct loan t_loan;

typedef struct person {
    unsigned long id;           /* one-to-one identifier    */
    
    struct person *before;
    struct person *next;
    
    char          *first_name;  /* first name of the person */
    char          *last_name;   /* last name of the person  */
    struct date   *gebDatum;    /* Geburtstdatum der Person */
} t_person;

/* view functions */
void viewInputPerson       (char *function);
void viewPersonListWithType(t_person *firstPerson, char *function, char *type, unsigned long identifier);

/* print functions */
void printPersonWithType(t_person *tmpPerson, char *type);

/* person-handling */
t_person* createPerson(char *firstname, char *lastname, t_date* gebDatum, unsigned long identifier);

/* functions for verifications */
int testPersonDataLine(char *line);

/* functions for list-&datahandling */
t_person* getPersonFromData(FILE* filePointer);

/* input functions */
t_person* inputPerson(t_person* firstPerson, char *vorname, char *nachname, int tag, int monat, int jahr);

#endif /* person_h */
