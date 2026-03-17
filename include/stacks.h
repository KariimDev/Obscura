#ifndef STACKS_H
#define STACKS_H

#include "linked_lists_queues.h"
#include <stdbool.h>

// --- Stack Function Prototypes ---

// Requirement 1: Converts the list returned by Merge function into a stack.
struct TStack* toStack(struct TList *merged);

// Requirement 2: Takes a name as input and returns the node (info) from the stack stk.
struct TStack* getInfoPersonality(struct TStack *stk, char *name);

// Requirement 3: Sorts the stack alphabetically.
struct TStack* sortNameStack(struct TStack *s);

// Requirement 4: Deletes a name from the stack.
struct TStack* deleteName(struct TStack *stk, char *name);

// Requirement 5: Updates personality name, definition, DoB, and DoD in the stack.
struct TStack* updateStack(struct TStack *stk, char *name, char *def, char *DoB, char *DoD);

// Requirement 6: Converts stack to a sorted queue.
struct TQueue* stackToQueue(struct TStack *stk);

// Requirement 7: Converts stack to a bidirectional sorted linked list.
struct TList* stackToList(struct TStack *stk);

// Requirement 8: Adds personality name with definition and dates into a sorted stack.
struct TStack* addNameStack(struct TStack *stk, char *name, char *definition, char *DoB, char *DoD);

// Requirement 9: Sorts names according to word count in definition.
struct TStack* definitionStack(struct TStack *stk);

// Requirement 10: Sorts events into two stacks based on description length.
struct TStack* pronunciationStack(struct TStack *stk);

// Requirement 11: Returns the smallest definition in the stack.
char* getSmallest(struct TStack *stk);

// Requirement 12: Prints continuous events where dates are overlapping.
void continuousSearch(struct TStack *stk);

// Requirement 13: Checks if a personality was killed.
bool isPersonalityKilled(char *word);

// Requirement 14: Reverses a stack using recursion.
struct TStack* recRevStack(struct TStack *stk);

// Helper function for stack creation
struct TStack* createStackNode(char* name, char* def, char* dob, char* dod);

#endif
