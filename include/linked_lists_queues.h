#ifndef LINKED_LISTS_QUEUES_H
#define LINKED_LISTS_QUEUES_H

#include <stdio.h>

// --- Structures ---

struct TList {
    char name[256];
    char definition[1024]; 
    char date_of_birth[50];          
    char date_of_death[50];          
    struct TList *next; 
    struct TList *prev; 
};

struct TStack {
    char name[256];
    char definition[1024]; 
    char date_of_birth[50];          
    char date_of_death[50];          
    struct TStack *next;    
};

struct TQueue {
    char name[256];
    char definition[1024]; 
    char date_of_birth[50];          
    char date_of_death[50];          
    struct TQueue *next;    
};

struct TTree {
    char name[256];
    char definition[1024]; 
    char date_of_birth[50];          
    char date_of_death[50];          
    struct TTree *left; 
    struct TTree *right; 
};

// --- Function Prototypes ---

struct TList* createListNode(char* new_name, char* new_def, char* new_dob, char* new_dod);
struct TList* getPersonality(FILE *f);
struct TList* getDatePersonality(FILE *f);
void getInfoByDates(struct TList *s, struct TList *DoB);
void getInfoByDates2(struct TList *s, struct TList *DoD);
struct TList* sortWord(struct TList *syn);
struct TList* sortWord2(struct TList *syn);
struct TList* sortPersonality(struct TList *syn);
struct TList* deletepersonality(FILE *f, struct TList *s, struct TList *a, char *name);
struct TList* updatePersonality(FILE *f, struct TList *s, struct TList *a, char *name, char *definition, char *DoB, char *DoD);
struct TList* similarPersonality(struct TList *s, char *word);
struct TList* countPersonality(struct TList *s, char *prt);
struct TList* palindromeName(struct TList *s);
struct TList* mergeNodes(struct TList *s, struct TList *a);
struct TList* merge2Nodes(struct TList *s, struct TList *a);
struct TList* addPersonality(struct TList *s, struct TList *a, char *name, char *DoB, char *DoD);
struct TList* addEvents(struct TList *b, char *namEvente, char *date);
struct TQueue* sName(struct TList *s);
struct TQueue* ageP(struct TList *a);
struct TQueue* toQueue(struct TList *merged);
struct TQueue* createQueueNode(char* name, char* def, char* dob, char* dod);

#endif
