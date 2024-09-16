#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char name[20];
    int size;
    int frames[20];
    int fragmentation;
    struct node *next;
};

struct node *head, *tail, *p, *ptr;

int totalMem, totalFrames, frameSize, remFrames;

void insert(int totalMem, int frameSize, int totalFrames, int status[]) {
    p = (struct node*)malloc(sizeof(struct node));
    printf("Enter the process name: ");
    scanf(" %s", p->name);
    printf("Enter the process size (in KB): ");
    scanf("%d", &p->size);
    
    int framesRequired = p->size / frameSize;
    if (p->size % frameSize != 0) {
        framesRequired++;
    }

    if (framesRequired > remFrames) {
        printf("\tno free frames...\n");
        free(p);
        return;
    }

    int allocated = 0;
    for (int i = 0; i < totalFrames && allocated < framesRequired; i++) {
        if (status[i] == 0) { 
            p->frames[allocated] = i;
            status[i] = 1;
            allocated++;
        }
    }
    
    p->fragmentation = (frameSize * framesRequired) - p->size;
    remFrames -= framesRequired;
    
    if (head == NULL) {
        head = tail = p;
        p->next = NULL;
    } else {
        tail->next = p;
        p->next = NULL;
        tail = p;
    }
    
    printf("Process %s has been allocated.\n", p->name);
    printf("Frames allocated: ");
    for (int i = 0; i < framesRequired; i++) {
        printf("%d ", p->frames[i]);
    }
    printf("\nInternal fragmentation: %d KB\n", p->fragmentation);
}

void display() {
    ptr = head;
    if (ptr == NULL) {
        printf("No processes in memory.\n");
    } else {
        printf("\nCurrent memory allocation:\n");
        while (ptr != NULL) {
            printf("Process %s - Size: %d KB - Frames: ", ptr->name, ptr->size);
            int framesRequired = ptr->size / frameSize + (ptr->size % frameSize != 0 ? 1 : 0);
            for (int i = 0; i < framesRequired; i++) {
                printf("%d ", ptr->frames[i]);
            }
            printf("- Internal Fragmentation: %d KB\n", ptr->fragmentation);
            ptr = ptr->next;
        }
    }
}

int main() {
    int choice;
    head = NULL;
    tail = NULL;

    printf("Enter the total memory (in KB): ");
    scanf("%d", &totalMem);
    printf("Enter the frame size (in KB): ");
    scanf("%d", &frameSize);

    totalFrames = totalMem / frameSize;
    remFrames = totalFrames;

    printf("Total frames available: %d\n", totalFrames);

    int status[totalFrames];
    for (int i = 0; i < totalFrames; i++) {
        status[i] = 0;
    }

    while (1) {
        printf("\nMENU\n1. Insert Process\n2. Display Memory Allocation\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert(totalMem, frameSize, totalFrames, status);
                break;
            case 2:
                display();
                break;
            case 3:
                printf("Terminating...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
