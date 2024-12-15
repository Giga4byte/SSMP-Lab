// relocating loader
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bitmask[4];
char binary_mask[13];

void convert_binary(char bitmask[4]) {
    strcpy(binary_mask, "");
    for (int i = 0; i < strlen(bitmask); i++) {
        switch (bitmask[i]) {
            case '0': strcat(binary_mask, "0000"); break;
            case '1': strcat(binary_mask, "0001"); break;
            case '2': strcat(binary_mask, "0010"); break;
            case '3': strcat(binary_mask, "0011"); break;
            case '4': strcat(binary_mask, "0100"); break;
            case '5': strcat(binary_mask, "0101"); break;
            case '6': strcat(binary_mask, "0110"); break;
            case '7': strcat(binary_mask, "0111"); break;
            case '8': strcat(binary_mask, "1000"); break;
            case '9': strcat(binary_mask, "1001"); break;
            case 'A': strcat(binary_mask, "1010"); break;
            case 'B': strcat(binary_mask, "1011"); break;
            case 'C': strcat(binary_mask, "1100"); break;
            case 'D': strcat(binary_mask, "1101"); break;
            case 'E': strcat(binary_mask, "1110"); break;
            case 'F': strcat(binary_mask, "1111"); break;
        }
    }
}

int main() {
    int start_addr, address;
    int opcode, operand;
    char col_one[10];
    char prog_name[10];

    FILE *fp = fopen("relocatingOBJ.txt", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter starting address: ");
    scanf("%x", &start_addr);

    printf("\nRelocated Address\tObject Code");

    fscanf(fp, "%s", col_one);
    
    while (strcmp(col_one, "E") != 0) {
        if (strcmp(col_one, "H") == 0) {
            fscanf(fp, "%s %*s %*s", prog_name);  // Skip record address and length
            fscanf(fp, "%s", col_one);
        }
        if (strcmp(col_one, "T") == 0) {
            fscanf(fp, "%x %*x %s", &address, bitmask);
            address += start_addr;
            convert_binary(bitmask);

            int mask_index = 0;
            while (fscanf(fp, "%02x%04x", &opcode, &operand) == 2) {
                if (binary_mask[mask_index] == '1') {
                    operand += start_addr; // Relocate operand if bit is 1
                }

                printf("\n%06x\t\t\t%02x%04x", address, opcode, operand);
                address += 3;
                mask_index++;


                if (getc(fp) == '$') {
                    break;
                }
            }

            fscanf(fp, "%s", col_one); // Move
        }
    }

    fclose(fp);
    printf("\nEnd of program.\n");
    return 0;
}

// credits to Serah Grace Kurien
