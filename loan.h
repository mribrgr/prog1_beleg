//
//  loan.h
//  beleg
//
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef loan_h
#define loan_h

typedef struct loan {
    unsigned long   id;                // eineindeutiger identifier, nicht einstellbar, vom System durchnummeriert
    struct loan*    before;
    struct loan*    next;
    struct person*  person;
    struct date*    loan_begin;
    struct date*    loan_end;
    struct item**   items;
} t_loan;                               // t_loan = struct loan = Datenstruktur loan


/* view functions */
    void viewDelLoan(t_loan* firstLoan);
    void viewNewLoan(t_person* firstPerson);
    void viewSearchLoan(char* prefix); // unused?
    void viewLoanListWithType(t_loan* firstLoan, char* prefix, char* type);

/* print functions */
    void printLoanWithType(t_loan* tmpLoan, char* prefix, char* type);

/* person - handling */
    t_loan* getLoan(unsigned long identifier, t_loan* firstLoan);
    t_loan* createLoan(t_person* tmpPerson, t_date* loanBegin, t_date* loanEnd, t_item** items, unsigned long identifier);
/* ID - handling */
    unsigned long getMaxLoanId(t_loan* firstLoan);
    unsigned long getLastLoanId(t_loan* firstLoan);
/* memory - handling */
    void freeLoan(t_loan* tmpLoan);
    void freeLoanList(t_loan* firstLoan);
/* functions for verifications */
    int testLoan(t_loan* tmpLoan);
    int testLoanDataLine(char* line);
    int testInputNewLoan(t_person* tmpPerson, t_date* loanBegin, t_date* loanEnd, t_item** items);

/* functions for list- & datahandling */
    t_loan* addLoanToList(t_loan* beforeLoan, t_loan* inputLoan);
    t_loan* deleteLoanFromList(t_loan* tmpLoan, t_loan* firstLoan);
    void    writeLoanToData(FILE* filePointer, t_loan* tmpLoan);
    void    writeLoanListToData(t_loan* firstLoan);
    void    appendLoanToData(t_loan* tmpPerson);
    t_loan* getLoanFromData(FILE* filePointer, t_person* firstPerson, t_item* firstItem);
    t_loan* addLoanListDataToList(t_loan* firstLoan, t_loan* lastLoan, t_person* firstPerson, t_item* firstItem); // gibt firstLoan zurück

/* input functions */
//    t_loan* inputLoan(t_loan* firstLoan, t_loan* lastLoan, char* vorname, char* nachname, int tag, int monat, int jahr);


#endif /* loan_h */
