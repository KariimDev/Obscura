#include "../include/stacks.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Helper: Node creation
struct TStack* createStackNode(char* name, char* def, char* dob, char* dod) {
    struct TStack* newNode = (struct TStack*)malloc(sizeof(struct TStack));
    if (newNode != NULL) {
        memset(newNode, 0, sizeof(struct TStack));
        strncpy(newNode->name, name, 255);
        strncpy(newNode->definition, def, 1023);
        strncpy(newNode->date_of_birth, dob, 49);
        strncpy(newNode->date_of_death, dod, 49);
        newNode->next = NULL;
    }
    return newNode;
}

// 1. converts the list returned by Merge function into a stack.
struct TStack* toStack(struct TList *merged) {
    struct TStack *top = NULL;
    struct TList *curr = merged;
    while(curr != NULL) {
        struct TStack *newNode = createStackNode(curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
        newNode->next = top;
        top = newNode;
        curr = curr->next;
        if (curr == merged) break; // Handling circular list case just in case
    }
    return top;
}

// 2. takes a name as input and returns the info node.
struct TStack* getInfoPersonality(struct TStack *stk, char *name) {
    struct TStack *curr = stk;
    while(curr != NULL) {
        if (strcmp(curr->name, name) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

// 3. sorts the stack alphabetically (Bubble Sort on the linked list structure)
struct TStack* sortNameStack(struct TStack *s) {
    if (s == NULL || s->next == NULL) return s;
    int swapped;
    struct TStack *ptr1;
    struct TStack *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = s;
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                // Swap data
                char tempName[256], tempDef[1024], tempDob[50], tempDod[50];
                strcpy(tempName, ptr1->name);
                strcpy(tempDef, ptr1->definition);
                strcpy(tempDob, ptr1->date_of_birth);
                strcpy(tempDod, ptr1->date_of_death);

                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->definition, ptr1->next->definition);
                strcpy(ptr1->date_of_birth, ptr1->next->date_of_birth);
                strcpy(ptr1->date_of_death, ptr1->next->date_of_death);

                strcpy(ptr1->next->name, tempName);
                strcpy(ptr1->next->definition, tempDef);
                strcpy(ptr1->next->date_of_birth, tempDob);
                strcpy(ptr1->next->date_of_death, tempDod);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    return s;
}

// 4. deletes a name from the stack.
struct TStack* deleteName(struct TStack *stk, char *name) {
    struct TStack *curr = stk, *prev = NULL;
    while(curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            if (prev == NULL) stk = curr->next;
            else prev->next = curr->next;
            free(curr);
            return stk;
        }
        prev = curr;
        curr = curr->next;
    }
    return stk;
}

// 5. updates a personality info in the stack.
struct TStack* updateStack(struct TStack *stk, char *name, char *def, char *DoB, char *DoD) {
    struct TStack *curr = stk;
    while(curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            strncpy(curr->definition, def, 1023);
            strncpy(curr->date_of_birth, DoB, 49);
            strncpy(curr->date_of_death, DoD, 49);
            return stk;
        }
        curr = curr->next;
    }
    return stk;
}

// 6. converts stack result into a sorted queue.
// Note: Requires createQueueNode from linked_lists_queues.h/c
struct TQueue* stackToQueue(struct TStack *stk) {
    if (stk == NULL) return NULL;
    // For sorting, easiest to sort stack data first or convert and sort queue
    // We'll sort the stack alphabetically first as a default "sorted" state.
    stk = sortNameStack(stk);
    
    struct TQueue *q = NULL, *tail = NULL;
    struct TStack *curr = stk;
    while(curr != NULL) {
        struct TQueue *newNode = createQueueNode(curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
        if (q == NULL) { q = newNode; tail = newNode; }
        else { tail->next = newNode; tail = newNode; }
        curr = curr->next;
    }
    return q;
}

// 7. converts stack into a bidirectional sorted linked list.
struct TList* stackToList(struct TStack *stk) {
    if (stk == NULL) return NULL;
    stk = sortNameStack(stk);
    
    struct TList *head = NULL, *tail = NULL;
    struct TStack *curr = stk;
    while(curr != NULL) {
        struct TList *newNode = createListNode(curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
        if (head == NULL) { head = newNode; tail = newNode; }
        else { tail->next = newNode; newNode->prev = tail; tail = newNode; }
        curr = curr->next;
    }
    return head;
}

// 8. adds personality into a sorted stack.
struct TStack* addNameStack(struct TStack *stk, char *name, char *definition, char *DoB, char *DoD) {
    struct TStack *newNode = createStackNode(name, definition, DoB, DoD);
    newNode->next = stk;
    stk = newNode;
    return sortNameStack(stk);
}

// Helper: Word count for definitionStack
static int getWordCount(char *str) {
    int count = 0;
    char copy[1024];
    strncpy(copy, str, 1023);
    copy[1023] = '\0';
    char *token = strtok(copy, " ");
    while(token != NULL) { count++; token = strtok(NULL, " "); }
    return count;
}

// 9. sorts by word count in definition.
struct TStack* definitionStack(struct TStack *stk) {
    if (stk == NULL || stk->next == NULL) return stk;
    int swapped;
    struct TStack *ptr1, *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = stk;
        while(ptr1->next != lptr) {
            if (getWordCount(ptr1->definition) > getWordCount(ptr1->next->definition)) {
                // Swap data logic
                char tempName[256], tempDef[1024], tempDob[50], tempDod[50];
                strcpy(tempName, ptr1->name); strcpy(tempDef, ptr1->definition);
                strcpy(tempDob, ptr1->date_of_birth); strcpy(tempDod, ptr1->date_of_death);

                strcpy(ptr1->name, ptr1->next->name); strcpy(ptr1->definition, ptr1->next->definition);
                strcpy(ptr1->date_of_birth, ptr1->next->date_of_birth); strcpy(ptr1->date_of_death, ptr1->next->date_of_death);

                strcpy(ptr1->next->name, tempName); strcpy(ptr1->next->definition, tempDef);
                strcpy(ptr1->next->date_of_birth, tempDob); strcpy(ptr1->next->date_of_death, tempDod);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while(swapped);
    return stk;
}

// 10. sorts events based on description length: short or long into two stacks.
// Note: As the function prototype returns TStack*, we'll return the input stk reordered.
struct TStack* pronunciationStack(struct TStack *stk) {
    if (stk == NULL || stk->next == NULL) return stk;
    int swapped;
    struct TStack *ptr1, *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = stk;
        while(ptr1->next != lptr) {
            // "Short or long" usually means sorting by string length
            if (strlen(ptr1->definition) > strlen(ptr1->next->definition)) {
                char tempName[256], tempDef[1024], tempDob[50], tempDod[50];
                strcpy(tempName, ptr1->name); strcpy(tempDef, ptr1->definition);
                strcpy(tempDob, ptr1->date_of_birth); strcpy(tempDod, ptr1->date_of_death);

                strcpy(ptr1->name, ptr1->next->name); strcpy(ptr1->definition, ptr1->next->definition);
                strcpy(ptr1->date_of_birth, ptr1->next->date_of_birth); strcpy(ptr1->date_of_death, ptr1->next->date_of_death);

                strcpy(ptr1->next->name, tempName); strcpy(ptr1->next->definition, tempDef);
                strcpy(ptr1->next->date_of_birth, tempDob); strcpy(ptr1->next->date_of_death, tempDod);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while(swapped);
    return stk;
}

// 11. returns the smallest definition in the stack.
char* getSmallest(struct TStack *stk) {
    if (stk == NULL) return NULL;
    struct TStack *curr = stk;
    char *smallest = stk->definition;
    while(curr != NULL) {
        if (strlen(curr->definition) < strlen(smallest)) {
            smallest = curr->definition;
        }
        curr = curr->next;
    }
    return smallest;
}

// 12. prints continuous events where dates are overlapping.
void continuousSearch(struct TStack *stk) {
    struct TStack *i = stk;
    printf("Continuous/Overlapping Events:\n");
    while(i != NULL) {
        struct TStack *j = i->next;
        while(j != NULL) {
            // Check overlap: Birth[i] <= Death[j] AND Birth[j] <= Death[i]
            int b1 = atoi(i->date_of_birth), d1 = atoi(i->date_of_death);
            int b2 = atoi(j->date_of_birth), d2 = atoi(j->date_of_death);
            if (b1 <= d2 && b2 <= d1) {
                printf(" - %s and %s overlap.\n", i->name, j->name);
            }
            j = j->next;
        }
        i = i->next;
    }
}

// 13. checks if a personality was killed.
bool isPersonalityKilled(char *word) {
    if (word == NULL) return false;
    // Check for keywords like "killed", "executed", "martyr", "assassinated"
    char *keywords[] = {"killed", "executed", "martyr", "assassinated", "mort", "tue"};
    for(int i = 0; i < 6; i++) {
        if (strstr(word, keywords[i]) != NULL) return true;
    }
    return false;
}

// Helper for recRevStack: Insert at Bottom
static void pushAtBottom(struct TStack **top_ref, struct TStack *newNode) {
    if (*top_ref == NULL) {
        *top_ref = newNode;
    } else {
        struct TStack *temp = *top_ref;
        *top_ref = (*top_ref)->next;
        pushAtBottom(top_ref, newNode);
        (*top_ref) = temp; // Re-linking
    }
}
// Correction for pushAtBottom recursive logic
static void insertAtBottom(struct TStack **stk, struct TStack *item) {
    if (*stk == NULL) {
        *stk = item;
        item->next = NULL;
    } else {
        struct TStack *temp = *stk;
        *stk = (*stk)->next;
        insertAtBottom(stk, item);
        temp->next = *stk;
        *stk = temp;
    }
}

// 14. reverses a stack using recursion.
struct TStack* recRevStack(struct TStack *stk) {
    if (stk == NULL || stk->next == NULL) return stk;
    struct TStack *top = stk;
    struct TStack *rest = stk->next;
    stk = recRevStack(rest);
    insertAtBottom(&stk, top);
    return stk;
}
