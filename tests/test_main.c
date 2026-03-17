#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linked_lists_queues.h"

void printList(struct TList *head) {
    struct TList *curr = head;
    while (curr != NULL) {
        printf(" - %s (Birth: %s, Death: %s)\n", curr->name, curr->date_of_birth, curr->date_of_death);
        curr = curr->next;
        if (curr == head) break; // For circular lists
    }
}

void printQueue(struct TQueue *head) {
    struct TQueue *curr = head;
    while (curr != NULL) {
        printf(" - %s\n", curr->name);
        curr = curr->next;
    }
}

int main() {
    printf("=== Starting Tests for Linked Lists and Queues ===\n\n");

    FILE *f = fopen("data/history_data.txt", "r");
    if (f == NULL) {
        printf("Error opening history_data.txt\n");
        return 1;
    }

    // 1. Test getPersonality
    printf("1. Testing getPersonality:\n");
    struct TList *listS = getPersonality(f);
    printList(listS);
    rewind(f);

    // 2. Test getDatePersonality
    printf("\n2. Testing getDatePersonality:\n");
    struct TList *listA = getDatePersonality(f);
    printList(listA);
    fclose(f);

    // 3. Test sortWord (Alphabetical)
    printf("\n3. Testing sortWord (Alphabetical):\n");
    listS = sortWord(listS);
    printList(listS);

    // 4. Test sortWord2 (Length)
    printf("\n4. Testing sortWord2 (Name Length):\n");
    listS = sortWord2(listS);
    printList(listS);

    // 5. Test mergeNodes
    printf("\n5. Testing mergeNodes:\n");
    struct TList *merged = mergeNodes(listS, listA);
    printList(merged);

    // 6. Test merge2Nodes (Circular)
    printf("\n6. Testing merge2Nodes (Circular):\n");
    struct TList *circular = merge2Nodes(listS, listA);
    printf("Circular Head: %s, Next: %s\n", circular->name, circular->next->name);

    // 7. Test toQueue
    printf("\n7. Testing toQueue:\n");
    struct TQueue *q = toQueue(merged);
    printQueue(q);

    // 8. Test sName (Queue sorted by word count)
    printf("\n8. Testing sName (Word Count Sort):\n");
    struct TQueue *qWords = sName(listS);
    printQueue(qWords);

    // 9. Test addPersonality
    printf("\n9. Testing addPersonality (Adding 'Abane Ramdane'):\n");
    listS = addPersonality(listS, listA, "Abane Ramdane", "1920", "1957");
    // Verify last node
    struct TList *temp = listS;
    while(temp->next) temp = temp->next;
    printf("Added: %s, Birth: %s\n", temp->name, temp->date_of_birth);

    // 10. Test deletepersonality
    printf("\n10. Testing deletepersonality (Deleting 'Zabana Ahmed'):\n");
    FILE *f2 = NULL; 
    listS = deletepersonality(f2, listS, listA, "Zabana Ahmed");
    printf("List after deletion:\n");
    printList(listS);

    printf("\n=== Tests Completed Successfully ===\n");
    return 0;
}
