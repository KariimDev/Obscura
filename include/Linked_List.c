#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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


struct TList* createListNode(char* new_name, char* new_def, char* new_dob, char* new_dod) {
    struct TList* newNode = (struct TList*)malloc(sizeof(struct TList));
    
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    strcpy(newNode->name, new_name);
    strcpy(newNode->definition, new_def);
    strcpy(newNode->date_of_birth, new_dob);
    strcpy(newNode->date_of_death, new_dod);
    
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}




int main() {
    // محاولة فتح الملف النصي في وضع القراءة ("r" = read)
    // Attempt to open the text file in read mode
    FILE *file = fopen("history.txt", "r");
    
    // التحقق مما إذا كان الملف غير موجود
    // Check if the file doesn't exist
    if (file == NULL) {
        printf("Error: Cannot open the file 'history.txt'. Please create it in the same folder.\n");
        return 1; // إنهاء البرنامج بوجود خطأ
    }
    
    printf("File opened successfully!\n");
    
    
    fclose(file);
    
    return 0; // إنهاء البرنامج بنجاح
}