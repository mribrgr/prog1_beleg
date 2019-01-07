//
//  item.h
//  beleg
//
//  Created by Mauritius Berger on 31.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//


 // was ist, wenn es die Person nicht mehr gibt? Am besten nicht löschbar machen



#ifndef item_h
#define item_h

typedef struct person t_person; // nur für den Linker

// man könnte später noch die Anzahl speichern
typedef struct item {         // name sollte noch übersetzt werden
    unsigned long   id;                     // eineindeutiger identifier
    struct item*    before;
    struct item*    next;
    
    struct person*  person;   // Name der Person die es ausleiht, wenn NULL, dann ist es noch zu haben
    char*           name;         // Name des Mediums
    char*           type;         // Art des Mediums
    char*           author;         // Name des/der Autors / Interprets / Band       / könnte man noch zu einer t_person machen
} t_item;                     // t_item = struct item

/* view functions */
    void viewDelItem(t_item* firstItem);
    void viewInputItem(char* function);
    void viewSearchItem(void); // unused?
    void viewItemListWithType(t_item* firstLoan, char* function, char* type);

/* print functions */
    void printItemWithType(t_item* tmpItem, char* type);

/* person - handling */
    t_item* createItem(char* name, char* type, char* author, unsigned long identifier);
/* functions for verifications */
    int testItemDataLine(char* line);

/* functions for list- & datahandling */
    t_item* getItemFromData(FILE* filePointer, t_person* firstPerson, t_item* firstItem);

t_item** getItemsFromItemList(unsigned long personId, t_item* firstItem);

//int countItemsWithPersonId(unsigned long personId, t_item* firstItem); // evtl. unused

#endif /* item_h */
