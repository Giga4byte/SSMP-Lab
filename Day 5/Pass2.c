#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_OBJECT_CODE_LENGTH 100

// Function to convert string to integer
int str_to_int(const char *str) {
    int num = 0;

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

// Function to search the symbol table for the address of a label
int get_symbol_address(const char *label) {
    FILE *fp = fopen("symtab.txt", "r");
    char sym[10];
    int addr;

    while (fscanf(fp, "%s\t%X\n", sym, &addr) != EOF) {
        if (strcmp(sym, label) == 0) {
            fclose(fp);
            return addr;
        }
    }
    fclose(fp);
    return -1; // Label not found
}

// Function to process Pass Two
void passTwo() {
    char label[10], opcode[10], operand[10], object_code[MAX_OBJECT_CODE_LENGTH];
    int locctr, start_addr, length;
    FILE *fp1 = fopen("intermediate.txt", "r");
    FILE *fp2 = fopen("objpgm.txt", "w");

    if (!fp1 || !fp2) {
        fprintf(stderr, "Error opening files.\n");
        exit(EXIT_FAILURE);
    }

    // Read the first line for starting address
    fscanf(fp1, "%d\t%s\t%s\t%s\n", &locctr, label, opcode, operand);
    start_addr = locctr;

    // Write header record
    fprintf(fp2, "H %s %06X %06X\n", label, start_addr, length);

    // Text record
    fprintf(fp2, "T %06X ", locctr);
    int text_length = 0; // To count the length of object code

    // Process lines until END
    while (strcmp(opcode, "END") != 0) {
        // Skip empty labels
        if (strcmp(label, "-") != 0) {
            int address = get_symbol_address(operand); // Get address for operand

            // Handle object code generation
            if (address != -1) {
                // Assume opcode has been set accordingly in previous pass
                sprintf(object_code, "%s%03X", opcode + 1, address); // Creating object code
                fprintf(fp2, "%s", object_code); // Write object code to text record
                text_length += strlen(object_code) / 2; // Update text length (2 chars per byte)
            }
        }
        // Read next line
        fscanf(fp1, "%d\t%s\t%s\t%s\n", &locctr, label, opcode, operand);
    }

    // Finalize the text record
    fprintf(fp2, "\n");

    // Write end record
    fprintf(fp2, "E %06X\n", start_addr);

    // Close files
    fclose(fp1);
    fclose(fp2);
}

int main() {
    passTwo();
    return 0;
}
