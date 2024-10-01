#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	char fname[20];
	struct node *next;
};

struct node *head, *tail, *ptr, *prev, *p;

void insert () {
	p = (struct node*)malloc(sizeof(struct node));
	
	printf("Enter file name: ");
	scanf(" %s", p->fname);
	p->next = NULL;
	
	if (head == NULL) {
		head = p;
		tail = p;
	} else {
		ptr = head;
		while (ptr != NULL) {
			if (strcmp(ptr->fname, p->fname) == 0) {
				printf("No duplicates, terminated...\n");
				free(p);
				return;
			}
			ptr = ptr->next;
		}
		tail->next = p;
		tail = p;
	}
	
	printf("File entered successfully...\n");
}

void display () {
	if (head == NULL) {
		printf ("no elements\n");
	} else {
		ptr = head;
		while (ptr != NULL) {
			printf (" %s |", ptr->fname);
			ptr = ptr->next;
		}
		printf (" end\n"); 
	}
}

void delete () {
    char filename[30];
    
	if (head == NULL) {
		printf("no elements\n");
	} else {
		ptr = head;
		printf ("Enter the file to delete: ");
		scanf (" %s", filename);
		
        while ((ptr != NULL) && (strcmp(filename,ptr->fname) != 0)) {
        	prev = ptr;
            ptr = ptr->next;
        }
        
        if (strcmp(filename, ptr->fname) == 0) {
        	if (ptr == head) {
        		head = ptr->next;
        		free(ptr);
        	} else if (ptr == tail) {
        		prev = tail;
        		prev->next = NULL;
        		free(ptr);
        	} else {
        		prev->next = ptr->next;
        		free(ptr);
        	}
        }
	} // else	
}

int main () {
	head = NULL; tail = NULL;
	int choice = -1;
	char file[20], directory[20];
	
	printf("Enter the directory name: ");
	scanf (" %s", directory);
	
	printf("MENU:\n1. Create File\t2. Delete File\n3. Search File\t4. Display File\n5. Exit\n");
	
	while (1) {
		printf ("\nEnter choice: ");
		scanf ("%d", &choice);
		
		switch(choice) {
			case 1: insert();
					break;
					
			case 2: delete();
					printf ("File has been deleted successfully...\n");
					break;
					
			case 3: printf ("Enter the file to search: ");
					scanf (" %s", file);
					printf ("Root/%s/%s\n", directory, file); 
					break;
					
			case 4: display();
					printf ("Files have been displayed successfully...\n");
					break;
			
			case 5: printf ("Terminated...\n");
					return 0;
					
			default: printf ("Wrong choice...\n");
		} // switch
	} // while

	return 0;
}
