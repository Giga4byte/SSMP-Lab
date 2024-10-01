#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	char dname[20];
	char fname[20];
	struct node *next;
};

struct node *head, *tail, *ptr, *prev, *p;

void insert () {
	p = (struct node*)malloc(sizeof(struct node));
	
	printf("Enter directory name: ");
	scanf(" %s", p->dname);
	
	printf("Enter file name: ");
	scanf(" %s", p->fname);
	p->next = NULL;
	
	if (head == NULL) {
		head = p;
		tail = p;
	} else {
		ptr = head;
		while (ptr != NULL) {
			if (strcmp(ptr->dname, p->dname) == 0 && strcmp(ptr->fname, p->fname) == 0) {
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
	char dir[20];
	if (head == NULL) {
		printf ("no elements\n");
	} else {
		ptr = head;
		printf ("Enter directory name: ");
		scanf (" %s", dir);
		while (ptr != NULL) {
			if (strcmp(dir, ptr->dname) == 0) {
				printf ("%s|%s   ", ptr->dname, ptr->fname);
				ptr = ptr->next;
			} else {
				ptr = ptr->next;
			}
		}
		printf("\n");
	}
}

void deleteFile () {
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

void deleteDir() {
    char dirname[30];
    int found = 0;
    
    if (head == NULL) {
        printf("no elements\n");
        return;
    }

    printf("Enter the name of the directory: ");
    scanf(" %s", dirname);

    ptr = head; prev = NULL;

    while (ptr != NULL) {
        if (strcmp(ptr->dname, dirname) == 0) {
            found = 1;
            printf("Deleting file %s...\n", ptr->fname);

            if (ptr == head) {
                head = ptr->next;
                free(ptr);
                ptr = head;
            } else {
                prev->next = ptr->next;
                free(ptr);
                ptr = prev->next;
            }
        } else {
            prev = ptr;
            ptr = ptr->next;
        }
    }
    if (!found) {
        printf("Directory %s not found or no files in the directory.\n", dirname);
    } else {
        printf("Directory %s and all its files have been deleted...\n", dirname);
    }
}

void search (char mainDir[5]) {
	char filename[20];
	printf ("Enter the file to search: ");
	scanf (" %s", filename);
	
	ptr = head;
	
	while ((ptr != NULL)) {
        prev = ptr;
        if (strcmp(filename, ptr->fname) == 0) {
    		printf ("%s/%s/%s\n", mainDir, ptr->dname, ptr->fname);
   		}
   		ptr = ptr->next;
    }
}

int main () {
	char mainDir[5];
	printf ("Enter the main directory: ");
	scanf (" %s", mainDir);
	
	head = NULL; tail = NULL;
	int choice = -1;
	char file[20], directory[20];
	
	printf("MENU:\n1. Create\t\t\t2. Delete File\n3. Delete Direc\t\t4. Search\n5. Display\t\t\t6. Exit\n");
	
	while (1) {
		printf ("\nEnter choice: ");
		scanf ("%d", &choice);
		
		switch(choice) {
			case 1: insert();
					break;
					
			case 2: deleteFile();
					printf ("File has been deleted successfully...\n");
					break;
			
			case 3: deleteDir();
			        //printf ("Directory has been deleted successfully...\n");
					break;
					
			case 4: search(mainDir); 
					break;
					
			case 5: display();
					printf ("Files have been displayed successfully...\n");
					break;
			
			case 6: printf ("Terminated...\n");
					return 0;
					
			default: printf ("Wrong choice...\n");
		} // switch
	} // while

	return 0;
}
