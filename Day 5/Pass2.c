#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert string to integer
int str_to_int(const char *str) {
    int num = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        num = num * 10 + (*str - '0');
        str++;
    }
    return sign * num;
}

// Function to find the address of a symbol in the symbol table
int get_symbol_address(const char *symbol) {
    char sym[10];
    int address;

    FILE *fp = fopen("symtab.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening symtab.txt.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s\t%d", sym, &address) != EOF) {
        if (strcmp(sym, symbol) == 0) {
            fclose(fp);
            return address;
        }
    }

    fclose(fp);
    return -1; // if not found
}

void passTwo() {
    char label[10], opcode[10], operand[10];
    int locctr;
    FILE *fp1 = fopen("intermediate.txt", "r");
    FILE *fp2 = fopen("objectcode.txt", "w");

    // Check if files opened successfully
    if (!fp1 || !fp2) {
        fprintf(stderr, "Error opening files.\n");
        exit(EXIT_FAILURE);
    }

    // Read the intermediate file
    while (fscanf(fp1, "%d\t%s\t%s\t%s", &locctr, label, opcode, operand) != EOF) {
        char object_code[20];
        if (opcode[0] == '+') {
            int address = get_symbol_address(operand);
            if (address != -1) {
                sprintf(object_code, "%s%03X", opcode + 1, address);
                fprintf(fp2, "%d\t%s\t%s\t%s\n", locctr, label, opcode, object_code);
            }
        } else { 
            int address = get_symbol_address(operand);
            if (address != -1) {
                sprintf(object_code, "%s%03X", opcode, address);
                fprintf(fp2, "%d\t%s\t%s\t%s\n", locctr, label, opcode, object_code);
            }
        }
    }

    // Close all files
    fclose(fp1);
    fclose(fp2);
    printf("Object code generated in objectcode.txt\n");
}

int main() {
    passTwo();
    return 0;
}
