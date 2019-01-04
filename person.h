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
    char*  last_name;               // Nachname der Person
    char*  first_name;              // Vorname der Person
    struct date*       gebDatum;   // Geburtstdatum der Person
    struct person*      before;
    struct person*      next;
    struct loan**       loans;
} t_person;                         // t_person = struct person

/* view functions */
    void viewDelPerson(t_person* firstPerson);
    void viewInputPerson(char* prefix);
    void viewSearchPerson(char* prefix);
    void viewPersonListWithType(t_person* firstPerson, char* prefix, char* type);

/* print functions */
    void printPersonWithType(t_person* tmpPerson, char* prefix, char* type);

/* person - handling */
    t_person* getPerson(unsigned long identifier, t_person* firstPerson);
    t_person* createPerson(char* firstname, char* lastname, t_date* gebDatum, unsigned long identifier);
/* ID - handling */
    unsigned long getMaxPersonId(t_person* firstPerson);
    unsigned long getLastPersonId(t_person* firstPerson);
/* memory - handling */
    void freePerson(t_person* tmpPerson);
    void freePersonList(t_person* firstPerson);
/* functions for verifications */
    int testPerson(t_person* tmpPerson);
    int testPersonDataLine(char* line);

/* functions for list- & datahandling */
    t_person* addPersonToList(t_person* tmpPerson, t_person* tmpPerson2);
    t_person* deletePersonFromList(t_person* tmpPerson, t_person* firstPerson);
    void writePersonToData(FILE* filePointer, t_person* tmpPerson);
    void writePersonListToData(t_person* firstPerson);
    void appendPersonToData(t_person* tmpPerson);
    t_person* getPersonFromData(FILE* filePointer);
    t_person* addPersonListDataToList(t_person* firstPerson, t_person* lastPerson); // gibt firstPerson zurück

/* input functions */
    t_person* inputPerson(t_person* firstPerson, t_person* lastPerson, char* vorname, char* nachname, int tag, int monat, int jahr);

#endif /* person_h */
