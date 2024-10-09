#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert string to integer
int str_to_int(const char *str) {
    int num = 0;
    
    // Convert string to integer (hexadecimal)
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        str += 2; // Skip the "0x" prefix
    }
    
    while ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F') || (*str >= 'a' && *str <= 'f')) {
        if (*str >= '0' && *str <= '9') {
            num = (num << 4) + (*str - '0');
        } else if (*str >= 'A' && *str <= 'F') {
            num = (num << 4) + (*str - 'A' + 10);
        } else {
            num = (num << 4) + (*str - 'a' + 10);
        }
        str++;
    }
    return num;
}

void passOne() {
    char label[10], opcode[10], operand[10], code[10], mnemonic[3];
    int locctr, start, length;
    
    FILE *fp1 = fopen("source.txt", "r");
    FILE *fp2 = fopen("optab.txt", "r"); 
    FILE *fp3 = fopen("symtab.txt", "w");
    FILE *fp4 = fopen("intermediate.txt", "w");
    FILE *fp5 = fopen("length.txt", "w"); 

    if (!fp1 || !fp2 || !fp3 || !fp4 || !fp5) {
        fprintf(stderr, "Error opening files.\n");
        exit(EXIT_FAILURE);
    }

    // Read first line
    if (fscanf(fp1, "%s\t%s\t%s", label, opcode, operand) != 3) {
        fprintf(stderr, "Error reading input file.\n");
        exit(EXIT_FAILURE);
    }
    
    // Check if the first opcode is START
    if (strcmp(opcode, "START") == 0) {
        start = str_to_int(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        if (fscanf(fp1, "%s\t%s\t%s", label, opcode, operand) != 3) {
            fprintf(stderr, "Error reading input file.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        locctr = 0;
    }

    // Process all lines until END
    while (strcmp(opcode, "END") != 0) {
        fprintf(fp4, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        if (strcmp(label, "-") != 0) {
            fprintf(fp3, "%s\t%X\n", label, locctr);
        }
        // Search opcode
        rewind(fp2);
        char found_opcode = 0;
        fscanf(fp2, "%s\t%s", code, mnemonic);
        while (!feof(fp2)) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
                found_opcode = 1;
                break;
            }
            fscanf(fp2, "%s\t%s", code, mnemonic);
        }
        // Handle directives - WORD, BYTE, RESW, RESB
        if (!found_opcode) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += (3 * str_to_int(operand));
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += str_to_int(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    locctr += (strlen(operand) - 3);
                } else if (operand[0] == 'X') {
                    locctr += (strlen(operand) - 3) / 2; 
                }
            } else if (opcode[0] == '+') {
                locctr += 4;
            }
        }
        // Read next line
        if (fscanf(fp1, "%s\t%s\t%s", label, opcode, operand) != 3) 
        { break; }
    }

    // Write final END
    fprintf(fp4, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    // Calculate program length
    length = locctr - start;
    fprintf(fp5, "%X", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    printf("\nProgram Size = %X\n", length);
}

int main() {
    passOne();
    return 0;
}
