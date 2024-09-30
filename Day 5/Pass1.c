#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeSymbolTable(char label[], int locctr) {
    FILE *symtab = fopen("symtab.txt", "a");
    if (!symtab) {
        printf("Error opening symtab.txt\n");
        return;
    }
    fprintf(symtab, "%s %04X\n", label, locctr); // Write label and location counter
    fclose(symtab);
}

int searchOpcode(char opcode[], int *size) {
    FILE *optab = fopen("optab.txt", "r");
    char op[10];
    int sz;

    if (!optab) {
        printf("Error opening optab.txt\n");
        return 0;
    }

    while (fscanf(optab, "%s %d", op, &sz) != EOF) {
        if (strcmp(op, opcode) == 0) {
            *size = sz;
            fclose(optab);
            return 1;
        }
    }

    fclose(optab);
    return 0;
}

void processing() {
    FILE *source = fopen("source.txt", "r");
    FILE *intermediate = fopen("intermediate.txt", "w");
    if (!source || !intermediate) {
        printf("can't open the files...\n");
        return;
    }

    char label[10], opcode[10], operand[10];
    int startAddr = 0, locctr = 0, size = 0;

    fscanf(source, "%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        startAddr = (int)strtol(operand, NULL, 16); // string to long int
        locctr = startAddr;
        fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand); 
        fscanf(source, "%s\t%s\t%s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        
        if (strcmp(label, "-") != 0) {
            writeSymbolTable(label, locctr);
        }

        if (searchOpcode(opcode, &size)) {
            locctr += size;
        } 
        else if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C') {
                locctr += strlen(operand) - 3; 
            } else if (operand[0] == 'X') {
                locctr += (strlen(operand) - 3) / 2;
            }
        } else {
            printf("invalid opcode %s...\n", opcode);
        }
        fscanf(source, "%s %s %s", label, opcode, operand);
    }

    fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    fclose(source);
    fclose(intermediate);
}

int main() {
    processSourceFile();
    printf("Pass 1 complete.\n");
    return 0;
}
