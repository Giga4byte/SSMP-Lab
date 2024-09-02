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

struct linked {
    int number;
    struct linked *next;
};
struct linked *head2, *tail2, *ptr2, *p2;

void insert (int alloc) {
	p2 = (struct linked*)malloc(sizeof(struct linked));
	p2->number = alloc;
	p2->next = NULL;
	if (head2 == NULL) {
		head2 = p2; tail2 = p2;
	} else {
		tail2->next = p2; tail2 = p2;
	}
}

void display () {
    if (head2 == NULL) { 
        printf ("empty list...\n"); 
    } else {
		ptr2 = head2;
		while (ptr2->next != NULL) {
			printf ("%d -> ", ptr2->number);
			ptr2 = ptr2->next;
		}
		printf ("%d", ptr2->number);
	}
}

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

    printf("\tFile %s has been allocated.\n", p->name);
    printf("\tBlocks allocated: ");
    for (int i = 0; i < allocated; i++) {
        insert (p->allocatedBlocks[i]);
    }
    display();
    printf("\n");
}

int main() {
    head = NULL; head2 = NULL;
    tail = NULL; tail2 = NULL;
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
