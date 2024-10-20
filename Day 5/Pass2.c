#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchOptab(char opcode[], char objCode[]) {
    FILE *fp = fopen("optab.txt", "r");
    char code[10], mnemonic[10];
    if (!fp) {
        printf("Error opening optab.txt\n");
        return 0;
    }
    while (fscanf(fp, "%s\t%s", code, mnemonic) != EOF) {
        if (strcmp(opcode, code) == 0) {
            strcpy(objCode, mnemonic);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int searchSymtab(char symbol[], int *address) {
    FILE *fp = fopen("symtab.txt", "r");
    char label[10];
    int loc;
    if (!fp) {
        printf("Error opening symtab.txt\n");
        return 0;
    }
    while (fscanf(fp, "%s\t%X", label, &loc) != EOF) {
        if (strcmp(symbol, label) == 0) {
            *address = loc;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void passTwo() {
    char label[10], opcode[10], operand[10], objCode[10];
    int address, locctr;
    FILE *fp1 = fopen("intermediate.txt", "r");
    FILE *fp2 = fopen("objpgm.txt", "w");
    
    if (!fp1 || !fp2) {
        printf("Error opening files\n");
        exit(1);
    }

    fscanf(fp1, "\t%s\t%s\t%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp2, "H^%s^%06X\n", label, strtol(operand, NULL, 16));
        fscanf(fp1, "%X\t%s\t%s\t%s", &locctr, label, opcode, operand);
    }
    
    fprintf(fp2, "T^%06X^", locctr);  
    
    while (strcmp(opcode, "END") != 0) {
        if (searchOptab(opcode, objCode)) {
            fprintf(fp2, "^%s", objCode); 
            
            if (strcmp(operand, "-") != 0) {
                if (searchSymtab(operand, &address)) {
                    fprintf(fp2, "%04X", address); 
                } else {
                    printf("Error: Undefined symbol %s\n", operand);
                }
            } else {
                fprintf(fp2, "0000");
            }
        } else {
            if (strcmp(opcode, "WORD") == 0) {
                fprintf(fp2, "^%06X", strtol(operand, NULL, 16));
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    for (int i = 2; operand[i] != '\''; i++) {
                        fprintf(fp2, "^%02X", operand[i]);
                    }
                } else if (operand[0] == 'X') {
                    fprintf(fp2, "^%02X", (int)strtol(operand + 2, NULL, 16));
                }
            }
        }

        if (fscanf(fp1, "%X\t%s\t%s\t%s", &locctr, label, opcode, operand) != 4) {
            break;
        }
    }

    fprintf(fp2, "\nE^%06X\n", locctr);
    
    fclose(fp1);
    fclose(fp2);
    printf("Object program generated successfully.\n");
}

int main() {
    passTwo();
    return 0;
}
