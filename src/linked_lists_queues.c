#include "../include/linked_lists_queues.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>






struct TList* createListNode(char* new_name, char* new_def, char* new_dob, char* new_dod) {
    struct TList* newNode = (struct TList*)malloc(sizeof(struct TList));
    
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    memset(newNode, 0, sizeof(struct TList));
    
    strncpy(newNode->name, new_name, sizeof(newNode->name) - 1);
    strncpy(newNode->definition, new_def, sizeof(newNode->definition) - 1);
    strncpy(newNode->date_of_birth, new_dob, sizeof(newNode->date_of_birth) - 1);
    strncpy(newNode->date_of_death, new_dod, sizeof(newNode->date_of_death) - 1);
    
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}

struct TList* getPersonality(FILE *f) {
    if (f == NULL) {
        return NULL;
    }

    struct TList *head = NULL; 
    struct TList *tail = NULL; 
    char line[2048]; 
    //we declare the line and it increase because the fgets read line line 
    while (fgets(line, sizeof(line), f) != NULL) {
        char temp_name[256];
        char temp_def[1024];
        //temp_name is a temporary variable to store the name of the personality of the current line
        //temp_def is a temporary variable to store the definition of the personality of the current line
        memset(temp_name, 0, sizeof(temp_name));
        memset(temp_def, 0, sizeof(temp_def));

        char *eq_ptr = strchr(line, '=');
        //pointer of the first occurense of the carachter in a string 
        
        if (eq_ptr != NULL) {
            
            int name_len = eq_ptr - line;
            if (name_len > 255) 
            {
                name_len = 255;
            }
            strncpy(temp_name, line, name_len);
            //strncpy copy a string with a specified number of characters
            temp_name[name_len] = '\0';

            char *def_start = eq_ptr + 1;
            char *colon_ptr = strchr(def_start, ':');
            //pointer of the first occurense of the carachter in a string starting from def_start
            
            if (colon_ptr != NULL) {
                size_t def_len = colon_ptr - def_start;
                if (def_len >= sizeof(temp_def)) def_len = sizeof(temp_def) - 1;
                strncpy(temp_def, def_start, def_len);
                //char *strncpy(char *dest, const char *src, size_t n);
                temp_def[def_len] = '\0';
            } else {
                strncpy(temp_def, def_start, sizeof(temp_def) - 1);
                temp_def[sizeof(temp_def) - 1] = '\0';
                temp_def[strcspn(temp_def, "\r\n")] = '\0';
            }

            struct TList* newNode = createListNode(temp_name, temp_def, "", "");
            if (newNode != NULL) {
                if (head == NULL) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode; 
                }
            }
        }
    }
    return head; 
}

struct TList* getDatePersonality(FILE *f) {
    if (f == NULL) return NULL;

    struct TList *head = NULL; 
    struct TList *tail = NULL; 
    char line[2048]; 

    while (fgets(line, sizeof(line), f) != NULL) {
        char temp_name[256]; 
        char temp_dob[50]; 
        char temp_dod[50]; 

        memset(temp_name, 0, sizeof(temp_name));
        memset(temp_dob, 0, sizeof(temp_dob));
        memset(temp_dod, 0, sizeof(temp_dod));
        //this memset is used to initialize the memory to 0

        char *eq_ptr = strchr(line, '=');
        if (eq_ptr != NULL) {
            int name_len = eq_ptr - line;
            
            if (name_len >= sizeof(temp_name)) name_len = sizeof(temp_name) - 1;
            strncpy(temp_name, line, name_len);
            temp_name[name_len] = '\0'; 

            char *birth_ptr = strstr(eq_ptr, "irth"); 
            if (birth_ptr != NULL) {
                char *open_brace = strchr(birth_ptr, '{');
                char *close_brace;
                if (open_brace != NULL) {
                    close_brace = strchr(open_brace, '}');
                } else {
                    close_brace = NULL;
                }
                
                if (open_brace && close_brace) {
                    int dob_len = close_brace - open_brace - 1;
                    if (dob_len >= sizeof(temp_dob)) dob_len = sizeof(temp_dob) - 1;
                    strncpy(temp_dob, open_brace + 1, dob_len);
                    temp_dob[dob_len] = '\0';
                }
            }

            char *death_ptr = strstr(eq_ptr, "eath");
            if (death_ptr != NULL) {
                char *open_brace = strchr(death_ptr, '{');
                char *close_brace;
                if (open_brace != NULL) {
                    close_brace = strchr(open_brace, '}');
                } else {
                    close_brace = NULL;
                }
                
                if (open_brace && close_brace) {
                    int dod_len = close_brace - open_brace - 1;
                    if (dod_len >= sizeof(temp_dod)) dod_len = sizeof(temp_dod) - 1;
                    //if the length of the date of death is greater than the size of the temp_dod we get only the first 49
                    strncpy(temp_dod, open_brace + 1, dod_len);
                    temp_dod[dod_len] = '\0';
                }
            }

            struct TList* newNode = createListNode(temp_name, "", temp_dob, temp_dod);
            if (newNode != NULL) {
                if (head == NULL) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode; 
                }
            }
        }
    }
    return head; 
}

void getInfoByDates(struct TList *s, struct TList *DoB) {
    char search_date[50];
    int found = 0;

    printf("\nEnter the Date of Birth to search for: ");
    scanf(" %[^\n]", search_date); 
    //mean read everything before the new line

    struct TList *current_date = DoB;


    while (current_date != NULL) {
        if (strcmp(current_date->date_of_birth, search_date) == 0) {
            char *name_to_find = current_date->name;
            printf("\n the date found for personality: %s\n", name_to_find);
            struct TList *current_info = s;
            while (current_info != NULL) {
                if (strcmp(current_info->name, name_to_find) == 0) {
                    printf("information: %s\n", current_info->definition);
                    found = 1;
                    break;
                }
                current_info = current_info->next;
            }
        }
        current_date = current_date->next;
    }

    if (!found) {
        printf("No personality found with the Date of Birth: %s\n", search_date);
    }
}

void getInfoByDates2(struct TList *s, struct TList *DoD) {
    char search_date[50];
    int found = 0;

    printf("\nEnter the Date of Death to search for: ");
    scanf(" %[^\n]", search_date); 

    struct TList *current_date = DoD;

    while (current_date != NULL) {
        if (strcmp(current_date->date_of_death, search_date) == 0) {
            char *name_to_find = current_date->name;
            printf("\n the date found for personality: %s\n", name_to_find);

            struct TList *current_info = s;
            while (current_info != NULL) {
                if (strcmp(current_info->name, name_to_find) == 0) {
                    printf("information: %s\n", current_info->definition);
                    found = 1;
                    break;
                }
                current_info = current_info->next;
            }
        }
        current_date = current_date->next;
    }

    if (!found) {
        printf("No personality found with the Date of Death: %s\n", search_date);
    }
}

struct TList* sortWord(struct TList *syn) {
    if (syn == NULL || syn->next == NULL) {
        return syn;
    }

    int swapped;
    struct TList *ptr1;
    struct TList *last_ptr = NULL;

    do {
        swapped = 0;
        ptr1 = syn;

        while (ptr1->next != last_ptr) {

            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                //this mean the first name is greater than the second name

                char temp_name[256];
                char temp_def[1024];
                char temp_dob[50];
                char temp_dod[50];

                strcpy(temp_name, ptr1->name);
                strcpy(temp_def, ptr1->definition);
                strcpy(temp_dob, ptr1->date_of_birth);
                strcpy(temp_dod, ptr1->date_of_death);

                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->definition, ptr1->next->definition);
                strcpy(ptr1->date_of_birth, ptr1->next->date_of_birth);
                strcpy(ptr1->date_of_death, ptr1->next->date_of_death);

                
                strcpy(ptr1->next->name, temp_name);
                strcpy(ptr1->next->definition, temp_def);
                strcpy(ptr1->next->date_of_birth, temp_dob);
                strcpy(ptr1->next->date_of_death, temp_dod);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        last_ptr = ptr1;
    } while (swapped);

    return syn;
}

struct TList* sortWord2(struct TList *syn) {
    if (syn == NULL || syn->next == NULL) {
        return syn;
    }

    int swapped;
    struct TList *ptr1;
    struct TList *last_ptr = NULL;

    do {
        swapped = 0;
        ptr1 = syn;

        while (ptr1->next != last_ptr) {
        
            if (strlen(ptr1->name) > strlen(ptr1->next->name)) {
                
                char temp_name[256];
                char temp_def[1024];
                char temp_dob[50];
                char temp_dod[50];

                strcpy(temp_name, ptr1->name);
                strcpy(temp_def, ptr1->definition);
                strcpy(temp_dob, ptr1->date_of_birth);
                strcpy(temp_dod, ptr1->date_of_death);

                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->definition, ptr1->next->definition);
                strcpy(ptr1->date_of_birth, ptr1->next->date_of_birth);
                strcpy(ptr1->date_of_death, ptr1->next->date_of_death);

                strcpy(ptr1->next->name, temp_name);
                strcpy(ptr1->next->definition, temp_def);
                strcpy(ptr1->next->date_of_birth, temp_dob);
                strcpy(ptr1->next->date_of_death, temp_dod);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        last_ptr = ptr1;
    } while (swapped);

    return syn;
}

struct TList* sortPersonality(struct TList *syn) {
    if (syn == NULL || syn->next == NULL) {
        return syn;
    }

    int swapped;
    struct TList *ptr1;
    struct TList *last_ptr = NULL;

    do {
        swapped = 0;
        ptr1 = syn;

        while (ptr1->next != last_ptr) {
            int age1 = atoi(ptr1->date_of_death) - atoi(ptr1->date_of_birth);
            //we need atoi because the date is stored as a string in the computer
            int age2 = atoi(ptr1->next->date_of_death) - atoi(ptr1->next->date_of_birth);

            if (age1 > age2) {
                char temp_name[256];
                char temp_def[1024];
                char temp_dob[50];
                char temp_dod[50];

                strcpy(temp_name, ptr1->name);
                strcpy(temp_def, ptr1->definition);
                strcpy(temp_dob, ptr1->date_of_birth);
                strcpy(temp_dod, ptr1->date_of_death);

                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->definition, ptr1->next->definition);
                strcpy(ptr1->date_of_birth, ptr1->next->date_of_birth);
                strcpy(ptr1->date_of_death, ptr1->next->date_of_death);

                strcpy(ptr1->next->name, temp_name);
                strcpy(ptr1->next->definition, temp_def);
                strcpy(ptr1->next->date_of_birth, temp_dob);
                strcpy(ptr1->next->date_of_death, temp_dod);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        last_ptr = ptr1;
    } while (swapped);

    return syn;
}

struct TList* deleteFromList(struct TList *head, char *name) {
    struct TList *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            
            if (curr->prev != NULL) {
                curr->prev->next = curr->next;
            } else {
                head = curr->next;
            }


            if (curr->next != NULL) {
                curr->next->prev = curr->prev;
            }

            free(curr);
            break;
        }
        curr = curr->next;
    }
    return head;
}

struct TList* deletepersonality(FILE *f, struct TList *s, struct TList *a, char *name) {
    s = deleteFromList(s, name);
    a = deleteFromList(a, name);
    // this for opening the file in the write mode
    f = fopen("data/history_data.txt", "w");
    if (f == NULL) {
        printf("error opening file\n");
        return s;
    }
    
    if (f != NULL) {
        struct TList *curr = s;
        while (curr != NULL) {
            fprintf(f, "%s=%s:Birth{%s}Death{%s}\n", curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
            curr = curr->next;
        }
        fclose(f);
    }
    return s;
}

struct TList* updatePersonality(FILE *f, struct TList *s, struct TList *a, char *name, char *definition, char *DoB, char *DoD) {
    struct TList *curr_s = s;
    while (curr_s != NULL) {
        if (strcmp(curr_s->name, name) == 0) {
            strncpy(curr_s->definition, definition, sizeof(curr_s->definition) - 1);
            strncpy(curr_s->date_of_birth, DoB, sizeof(curr_s->date_of_birth) - 1);
            strncpy(curr_s->date_of_death, DoD, sizeof(curr_s->date_of_death) - 1);
            break;
        }
        curr_s = curr_s->next;
    }
    struct TList *curr_a = a;
    while (curr_a != NULL) {
        if (strcmp(curr_a->name, name) == 0) {
            strncpy(curr_a->date_of_birth, DoB, sizeof(curr_a->date_of_birth) - 1);
            strncpy(curr_a->date_of_death, DoD, sizeof(curr_a->date_of_death) - 1);
            break;
        }
        curr_a = curr_a->next;
    }
    f = fopen("data/history_data.txt", "w");
    if (f != NULL) {
        struct TList *curr = s;
        while (curr != NULL) {
            fprintf(f, "%s=%s:Birth{%s}Death{%s}\n", curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
            curr = curr->next;
        }
        fclose(f);
    }
    return s;
}

struct TList* similarPersonality(struct TList *s, char *word) {
    struct TList *newList = NULL;
    struct TList *tail = NULL;
    struct TList *curr = s;
    while (curr != NULL) {
        if (strcmp(curr->date_of_birth, word) == 0 || strcmp(curr->date_of_death, word) == 0) {
            struct TList *newNode = createListNode(curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
            if (newList == NULL) {
                newList = newNode; 
                tail = newNode; 
            }
            else {
                tail->next = newNode; 
                newNode->prev = tail; 
                tail = newNode; 
            }
        }
        curr = curr->next;
    }
    return newList;
}

struct TList* countPersonality(struct TList *s, char *prt) {
    struct TList *newList = NULL;
    struct TList *tail = NULL;
    struct TList *curr = s;
    while (curr != NULL) {
        if (strstr(curr->date_of_birth, prt) || strstr(curr->date_of_death, prt) || strstr(curr->definition, prt)) {
            struct TList *newNode = createListNode(curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
            if (newList == NULL) { newList = newNode; tail = newNode; }
            else { tail->next = newNode; newNode->prev = tail; tail = newNode; }
        }
        curr = curr->next;
    }
    return newList;
}

int isPalindrome(char *str) {
    int len = strlen(str);
    if (len <= 1) return 0;
    for (int i = 0; i < len / 2; i++) {
        if (tolower(str[i]) != tolower(str[len - 1 - i])) return 0;
    }
    return 1;
}

struct TList* palindromeName(struct TList *s) {
    struct TList *newList = NULL;
    struct TList *curr = s;
    while (curr != NULL) {
        char def_copy[1024];
        strcpy(def_copy, curr->definition);
        char *token = strtok(def_copy, " ,.:;!?");
        while (token != NULL) {
            if (isPalindrome(token)) {
                struct TList *newNode = createListNode(token, "", "", "");
                if (newList == NULL) { newList = newNode; }
                else {
                    struct TList *temp = newList;
                    struct TList *prev_temp = NULL;
                    while (temp != NULL && strcmp(temp->name, token) < 0) {
                        prev_temp = temp;
                        temp = temp->next;
                    }
                    if (prev_temp == NULL) { newNode->next = newList; newList->prev = newNode; newList = newNode; }
                    else { newNode->next = temp; if (temp) temp->prev = newNode; newNode->prev = prev_temp; prev_temp->next = newNode; }
                }
            }
            token = strtok(NULL, " ,.:;!?");
        }
        curr = curr->next;
    }
    return newList;
}

struct TList* mergeNodes(struct TList *s, struct TList *a) {
    struct TList *newList = NULL;
    struct TList *tail = NULL;
    struct TList *curr_s = s;
    while (curr_s != NULL) {
        struct TList *curr_a = a;
        while (curr_a != NULL) {
            if (strcmp(curr_s->name, curr_a->name) == 0) {
                struct TList *newNode = createListNode(curr_s->name, curr_s->definition, curr_a->date_of_birth, curr_a->date_of_death);
                if (newList == NULL) { newList = newNode; tail = newNode; }
                else { tail->next = newNode; newNode->prev = tail; tail = newNode; }
                break;
            }
            curr_a = curr_a->next;
        }
        curr_s = curr_s->next;
    }
    return newList;
}

struct TList* merge2Nodes(struct TList *s, struct TList *a) {
    struct TList *head = mergeNodes(s, a);
    if (head == NULL) return NULL;
    struct TList *tail = head;
    while (tail->next != NULL) tail = tail->next;
    tail->next = head;
    head->prev = tail;
    return head;
}

struct TList* addPersonality(struct TList *s, struct TList *a, char *name, char *DoB, char *DoD) {
    struct TList *newNodeS = createListNode(name, "", DoB, DoD);
    struct TList *newNodeA = createListNode(name, "", DoB, DoD);
    if (s == NULL) {
        s = newNodeS;
    }
    else {
        struct TList *t = s;
        while(t->next) {
            t = t->next;
        }
        t->next = newNodeS;
        newNodeS->prev = t;
    }
    if (a == NULL) {
        a = newNodeA;
    }
    else {
        struct TList *t = a;
        while(t->next) {
            t = t->next;
        }
        t->next = newNodeA;
        newNodeA->prev = t;
    }
    FILE *f = fopen("data/history_data.txt", "a");
    // a mean add without deleting the old data
    if (f != NULL) {
        fprintf(f, "%s=:Birth{%s}Death{%s}\n", name, DoB, DoD);
        fclose(f);
    }
    return s;
}

struct TList* addEvents(struct TList *b, char *namEvente, char *date) {
    struct TList *newNode = createListNode(namEvente, "", date, "");
    if (b == NULL) {
        b = newNode;
    }
    else {
        struct TList *t = b;
        while(t->next) {
            t = t->next;
        }
        t->next = newNode;
        newNode->prev = t;
    }
    FILE *f = fopen("data/history_data.txt", "a");
    if (f != NULL) {
        fprintf(f, "Event:%s{%s}\n", namEvente, date);
        fclose(f);
    }
    return b;
}

struct TQueue* createQueueNode(char* name, char* def, char* dob, char* dod) {
    struct TQueue* newNode = (struct TQueue*)malloc(sizeof(struct TQueue));
    if (newNode != NULL) {
        memset(newNode, 0, sizeof(struct TQueue));
        strncpy(newNode->name, name, 255);
        strncpy(newNode->definition, def, 1023);
        strncpy(newNode->date_of_birth, dob, 49);
        strncpy(newNode->date_of_death, dod, 49);
        newNode->next = NULL;
    }
    return newNode;
}

int countWords(char *str) {
    int count = 0;
    char copy[256];
    strncpy(copy, str, 255);
    copy[255] = '\0';
    char *token = strtok(copy, " ");
    while (token != NULL) { count++; token = strtok(NULL, " "); }
    return count;
}

struct TQueue* sName(struct TList *s) {
    struct TQueue *q = NULL, *tail = NULL;
    struct TList *curr = s;
    while (curr != NULL) {
        struct TQueue *newNode = createQueueNode(curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
        if (q == NULL) { q = newNode; tail = newNode; }
        else { tail->next = newNode; tail = newNode; }
        curr = curr->next;
    }
    struct TQueue *i, *j;
    for (i = q; i != NULL && i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (countWords(i->name) > countWords(j->name)) {
                struct TQueue temp;
                memcpy(&temp, i, sizeof(struct TQueue) - sizeof(struct TQueue*));
                memcpy(i, j, sizeof(struct TQueue) - sizeof(struct TQueue*));
                memcpy(j, &temp, sizeof(struct TQueue) - sizeof(struct TQueue*));
            }
        }
    }
    return q;
}

struct TQueue* ageP(struct TList *a) {
    struct TQueue *q = NULL, *tail = NULL;
    struct TList *curr = a;
    while (curr != NULL) {
        struct TQueue *newNode = createQueueNode(curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
        if (q == NULL) { q = newNode; tail = newNode; }
        else { tail->next = newNode; tail = newNode; }
        curr = curr->next;
    }
    struct TQueue *i, *j;
    for (i = q; i != NULL && i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            int age1 = atoi(i->date_of_death) - atoi(i->date_of_birth);
            int age2 = atoi(j->date_of_death) - atoi(j->date_of_birth);
            if (age1 > age2) {
                struct TQueue temp;
                memcpy(&temp, i, sizeof(struct TQueue) - sizeof(struct TQueue*));
                memcpy(i, j, sizeof(struct TQueue) - sizeof(struct TQueue*));
                memcpy(j, &temp, sizeof(struct TQueue) - sizeof(struct TQueue*));
            }
        }
    }
    return q;
}

struct TQueue* toQueue(struct TList *merged) {
    struct TQueue *q = NULL, *tail = NULL;
    struct TList *curr = merged;
    while (curr != NULL) {
        struct TQueue *newNode = createQueueNode(curr->name, curr->definition, curr->date_of_birth, curr->date_of_death);
        if (q == NULL) { q = newNode; tail = newNode; }
        else { tail->next = newNode; tail = newNode; }
        if (merged->next == merged) break; 
        curr = curr->next;
        if (curr == merged) break;
    }
    return q;
}
