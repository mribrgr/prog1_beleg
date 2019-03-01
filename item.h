//
//  item.h
//  beleg
//  46139
//  Created by Mauritius Berger on 31.12.18.
//  Copyright © 2018 Mauritius Berger. All rights reserved.
//

#ifndef item_h
#define item_h

typedef struct person t_person;

typedef struct item {
    unsigned long   id;       /* one-to-one identifier          */
    
    struct item     *before;
    struct item     *next;
    
    struct person   *person;  /* name of the connected person   */
    char            *name;    /* name of the item               */
    char            *type;    /* type of the item               */
    char            *author;  /* name of the author             */
} t_item;

/* view functions */
void viewInputItem       (char *function, char *prefix);
void viewItemListWithType(t_item *firstItem, char *function, char *type, unsigned long identifier, t_person *firstPerson, char *prefix);

/* print functions */
void printItemWithType(t_item *tmpItem, char *type, t_person *firstPerson, char *prefix);

/* item-handling */
t_item* createItem(char *name, char *type, char *author, unsigned long identifier);

/* functions for verifications */
int testItemDataLine(char *line);

/* functions for list-&datahandling */
t_item* getItemFromData     (FILE* filePointer, t_person* firstPerson, t_item* firstItem);
t_item* getItemsFromItemList(unsigned long personId, t_item* firstItem);

/* input functions */
t_item *inputItem(t_item *firstItem, char *name, char *type, char *author);

t_item *getItemByPerson(unsigned long identifier, t_item *firstItem);

#endif /* item_h */
