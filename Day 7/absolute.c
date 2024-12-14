// absolute loader
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
  FILE * fp;
  int i,j, staddr1;
  char name[10], line[50], name1[10],staddr[10];
  fp = fopen("absoluteOBJ.txt", "r");
  fscanf(fp, "%s", line);
  
  printf ("Address\tObjectCode\n");
  
  if(line[0]=='H')
  {
    do {
      fscanf(fp, "%s", line);
      if (line[0] == 'T') {
        for (i = 2, j = 0; i < 8, j < 6; i++, j++)
          staddr[j] = line[i];
        staddr[j] = '\0';
        staddr1 = atoi(staddr);
        i = 12;
        while (line[i] != '$') {
          if (line[i] != '^') {
            printf("%d\t%c%c\n", staddr1, line[i], line[i + 1]);
            staddr1++;
            i = i + 2;
          } else i++;
        }
      }
      else if (line[0] = 'E') {
        fclose(fp);
        exit(0);
      }
    } while (!feof(fp));
  }
}

