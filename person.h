//
//  person.h
//  beleg
//
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef person_h
#define person_h

typedef struct loan t_loan; // nur um zu zeigen, dass es später noch definiert wird

typedef struct person {
    unsigned long    id;            // eineindeutiger identifier
    struct person*      before;
    struct person*      next;
    
    char*  last_name;               // Nachname der Person
    char*  first_name;              // Vorname der Person
    struct date*       gebDatum;   // Geburtstdatum der Person
    struct loan**       loans;
} t_person;                         // t_person = struct person

/* view functions */
    void viewDelPerson(t_person* firstPerson);
    void viewInputPerson(char* function);
    void viewSearchPerson(void);
    void viewPersonListWithType(t_person* firstPerson, char* function, char* type);

/* print functions */
    void printPersonWithType(t_person* tmpPerson, char* type);

/* person - handling */
    t_person* createPerson(char* firstname, char* lastname, t_date* gebDatum, unsigned long identifier);
/* functions for verifications */
    int testPersonDataLine(char* line);

/* functions for list- & datahandling */
    t_person* getPersonFromData(FILE* filePointer);
/* input functions */
    t_person* inputPerson(t_person* firstPerson, t_person* lastPerson, char* vorname, char* nachname, int tag, int monat, int jahr);

#endif /* person_h */
