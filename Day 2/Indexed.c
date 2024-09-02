#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node {
    char name[30];
    int blocks;
    int allocatedBlocks[20];  // Adjust size if needed
    struct node *next;
};
struct node *head, *tail, *ptr, *p;

void allocateFile(int totalBlocks, int status[]) {
    p = (struct node*)malloc(sizeof(struct node));
    printf("Enter the name of the file: ");
    scanf(" %s", p->name);
    printf("Enter the number of blocks for it: ");
    scanf("%d", &p->blocks);

    int freeBlocks = 0;
    for (int i = 0; i < totalBlocks; i++) {
        if (status[i] == 0) {
            freeBlocks++;
        }
    }

    if (p->blocks > freeBlocks) {
        printf("\tFile %s cannot be allocated...\n", p->name);
        free(p);
        return;
    }

    int allocated = 0, index = 0;
    for (int i = 0; i < totalBlocks && allocated < p->blocks; i++) {
        if (status[i] == 0) {
            index = rand() % (totalBlocks-1);
            if (index != p->blocks - allocated) {
                p->allocatedBlocks[allocated] = i;
                status[i] = 1;
                allocated++;
            }
        }
    }

    if (head == NULL) {
        p->next = NULL;
        head = tail = p;
    } else {
        p->next = NULL;
        tail->next = p;
        tail = p;
    }

    printf("\tFile %s has been allocated with index %d.\n", p->name, index);
    printf("\tBlocks allocated: ");
    for (int i = 0; i < allocated; i++) {
        printf("%d ", p->allocatedBlocks[i]);
    }
    printf("\n");
}

int main() {
    head = NULL;
    tail = NULL;
    char choice[4];
    int totalBlocks;

    printf("Enter the total number of blocks: ");
    scanf("%d", &totalBlocks);

    int status[totalBlocks];
    for (int i = 0; i < totalBlocks; i++) {
        status[i] = 0;
    }

    //srand(time(0));

    while (1) {
        printf("Do you want to enter a file: ");
        scanf(" %s", choice);

        if (strcmp(choice, "yes") == 0) {
            allocateFile(totalBlocks, status);
        } else if (strcmp(choice, "no") == 0) {
            printf("\tTerminating...\n");
            return 0;
        } else {
            printf("\tInvalid input. Please enter 'yes' or 'no'.\n");
        }
    }

    return 0;
}
