//
//  loan.h
//  beleg
//  46139
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef loan_h
#define loan_h

typedef struct loan {
    unsigned long   id;           /* one-to-one identifier              */
    
    struct loan     *before;
    struct loan     *next;
    
    struct person   *person;      /* the connected person               */
    struct item     *item;        /* the connected item                 */
    struct date     *loan_begin;  /* date of the beginning of the loan  */
    struct date     *loan_end;    /* date of the ending of the loan     */
} t_loan;


/* view functions */
void viewInputLoan       (char *function, char *personId, char *itemId);
void viewLoanListWithType(t_loan *firstLoan, char *function, char *type, unsigned long identifier);

/* print functions */
void printLoanWithType(t_loan *tmpLoan, char *type);

/* loan-handling */
t_loan* createLoan(t_person* tmpPerson, t_date *loanBegin, t_date *loanEnd, t_item *item, unsigned long identifier);

/* functions for verifications */
int testLoanObj     (t_loan *firstLoan, char *structure, unsigned long identifier);
int testLoanDataLine(char* line);
int testInputNewLoan(int tag, int monat, int jahr, int tag2, int monat2, int jahr2);

/* functions for list-&datahandling */
t_loan *getLoanFromData(FILE* filePointer, t_person* firstPerson, t_item* firstItem);

/* input functions */
void inputLoan(t_loan *firstLoan, t_person *tmpPerson, t_item *tmpItem, int loan_begin_day, int loan_begin_month, int loan_begin_year, int loan_end_day, int loan_end_month, int loan_end_year, t_item *firstItem);

#endif /* loan_h */
