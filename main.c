#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char data[50];
    struct node* next;
};

void push(struct node** head, char* data) {
    //  ( head = null ) ? or ( head_data > data ) ?
    //  yes:
    //      append new node as the new head
    //  no:
    //      start at the head
    //      find node (current) before the one that is greater than new node
    //      append new node after current (put it in the middle)
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (*head == NULL || strcmp((*head)->data, data) > 0) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct node* current = *head;
        while (!(current->next == NULL) && strcmp(current->next->data, data) <= 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Wrong amount of arguments!\n");
        return 1;
    }

    FILE *fptr;
    if ((fptr = fopen(argv[1], "r")) == NULL){
        printf("Error! File cannot be opened.");
        return 0;
    }

    struct node* head = NULL;
    char line[100];
    char *word;
    const char separator[5] = ".,: ";
    while (fgets(line, sizeof line, fptr) != NULL){
        word = strtok(line, separator);
        while (word != NULL){
            // fix bad chars
            if(strchr(word,'\n') != NULL){
                word[strlen(word)-1] = '\0';
            }
            // add word to linked list
            push(&head, word);
            word = strtok(NULL, separator);
        }
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("Output file cannot be created!");
        exit(1);
    }

    while (head != NULL) {
        fprintf(outputFile, "%s\n", head->data);
        head = head->next;
    }

    fclose(outputFile);

    return 0;
}