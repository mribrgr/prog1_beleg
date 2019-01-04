//
//  date.h
//  beleg
//
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef date_h
#define date_h

typedef struct date {
    int day;
    int month;
    int year;
} t_date;                      // t_date = struct date

/* Funktionen zum Handling mit Datumswerten */
t_date* createDate(int tag, int monat, int jahr);

t_date* getDateFromString(char* string);

int testDate(t_date* tmpDate);

#endif /* date_h */
