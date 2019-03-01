//
//  date.h
//  beleg
//  46139
//  Created by Mauritius Berger on 12.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef date_h
#define date_h

typedef struct date {
    int day;
    int month;
    int year;
} t_date;

/* date-handling */
t_date* createDate(int tag, int monat, int jahr);

t_date* getDateFromString(char* string);

#endif /* date_h */
