#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char name[30];
    int blocks;
    int size;
    struct node *next;
};
struct node *head, *tail, *ptr, *p;

void allocateFile (int totalBlocks) {
    p = (struct node*)malloc(sizeof(struct node));
    printf ("Enter the name of the file: ");
    scanf (" %s", p->name);
    printf ("Enter the no of blocks for it: ");
    scanf ("%d", &p->blocks);
    
    int available = totalBlocks;
    ptr = head;
    while (ptr != NULL) {
        available -= ptr->blocks;
        ptr = ptr->next;
    }
    
    if (p->blocks > available) {
        printf("\tFile %s cannot be allocated...\n", p->name);
        free(p);
        return;
    }
    
    if (head == NULL) {
        p->size = p->blocks;  
        head = tail = p;
    } else {
        p->size = tail->size + p->blocks;
        tail->next = p;
        tail = p;
    }
    p->next = NULL;

    printf("\tFile %s has been allocated.\n\tRemaining blocks = %d\n", p->name, available - p->blocks);
}

int main () {
    head = NULL; tail = NULL;
    char choice[4]; int totalBlocks;
    
    printf("Enter the total number of blocks: ");
    scanf("%d", &totalBlocks);
    
    while (1) {
        printf("Do you want to enter a file: ");
        scanf(" %s", choice);
        
        if (strcmp(choice, "yes") == 0) {
            allocateFile(totalBlocks);
        } else if (strcmp(choice, "no") == 0) {
            printf("\tTerminating...\n");
            return 0;
        } else {
            printf("\tInvalid input. Please enter 'yes' or 'no'.\n");
        }
    }
    
    return 0;
}
