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

void delete (int status[]) {
    char processName[20];
    printf("Enter the process name to delete: ");
    scanf(" %s", processName);

    ptr = head;
    struct node *prev = NULL;

    while (ptr != NULL) {
        if (strcmp(ptr->name, processName) == 0) {
            for (int i = 0; i < (ptr->size / frameSize) + (ptr->size % frameSize != 0 ? 1 : 0); i++) {
                status[ptr->frames[i]] = 0;
            }
            remFrames += (ptr->size / frameSize) + (ptr->size % frameSize != 0 ? 1 : 0); // Update remaining frames

            if (prev == NULL) {
                head = ptr->next;
            } else {
                prev->next = ptr->next;
            }

            if (ptr == tail) {
                tail = prev;
            }

            free(ptr);
            printf("Process %s has been deleted.\n", processName);
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    printf("Process %s not found.\n", processName);
}

/*void totalFrag() {
	int totalFragmentation = 0;
	ptr = head;
	while (ptr != NULL) {
		totalFragmentation += ptr->fragmentation;
	}
	printf("\nTOTAL FRAGMENTATION = %d\n", totalFragmentation);
}*/

void display() {
	int totalFragmentation = 0;
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
            totalFragmentation += ptr->fragmentation;
            ptr = ptr->next;
        }
    }
    printf ("TOTAL FRAGMENTATION = %d\n", totalFragmentation);
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
        printf("\nMENU\n1. Insert Process\n2. Delete Process\n3. Display Memory Allocation\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert(totalMem, frameSize, totalFrames, status);
                break;
            case 2:
            	delete(status);
            	break;
            case 3:
                display(); 
                break;
            case 4:
                printf("Terminating...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
