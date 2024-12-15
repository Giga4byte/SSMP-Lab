#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    int prog_len, length, objc_len, text_rec_len = 0, text_rec_addr;
    char start_addr[10], loc[10], label[10], opcode[10], operand[10];
    char opc[10], val[10], sym_name[10], sym_addr[10];
    char text_header[10], obj_code[100] = "", temp_objc[100];
    FILE *intermediate_ptr = fopen("intermediatefile.txt", "r");
    FILE *optab_ptr = fopen("OPTAB.txt", "r");
    FILE *symtab_ptr = fopen("symtab.txt", "r");
    FILE *size_ptr = fopen("prgsize.txt", "r");
    FILE *object_ptr = fopen("pass2_objectcode.txt", "w");

    if (!intermediate_ptr || !optab_ptr || !symtab_ptr || !size_ptr || !object_ptr) {
        printf("Could not open one or more files.\n");
        exit(1);
    }

    fscanf(intermediate_ptr, "%s %d %s %s %s", loc, &length, label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        strcpy(start_addr, operand);
        text_rec_addr = (int)strtol(start_addr, NULL, 16);
        fscanf(size_ptr, "%x", &prog_len);
    }

    printf("H^%s^%06X^%06X\n", label, (int)strtol(start_addr, NULL, 16), prog_len);
    fprintf(object_ptr, "H^%s^%06X^%06X\n", label, (int)strtol(start_addr, NULL, 16), prog_len);
    snprintf(text_header, sizeof(text_header), "T^%06X", text_rec_addr);

    while (strcmp(opcode, "END") != 0) {
        fscanf(intermediate_ptr, "%s %d %s %s %s", loc, &length, label, opcode, operand);
        objc_len = 0;
        strcpy(temp_objc, "");
        int opcode_found = 0;
        fseek(optab_ptr, 0, SEEK_SET);

        while (fscanf(optab_ptr, "%s %s", opc, val) != EOF) {
            char newopc[20] = "+";
            strcat(newopc, opc);
            if (strcmp(opcode, opc) == 0 || strcmp(opcode, newopc) == 0) {
                int operand_found = 0;
                fseek(symtab_ptr, 0, SEEK_SET);
                while (fscanf(symtab_ptr, "%s %s", sym_name, sym_addr) != EOF) {
                    if (strcmp(operand, sym_name) == 0) {
                        snprintf(temp_objc, sizeof(temp_objc), "^%s%s", val, sym_addr);
                        objc_len = 3;
                        operand_found = 1;
                        break;
                    }
                }
                if (operand_found) break;
                opcode_found = 1;
            }
        }
        if (strcmp(opcode, "BYTE") == 0) {
            strcpy(temp_objc, "^");
            for (int i = 2; i < strlen(operand) - 1; i++) {
                char hex_val[3];
                snprintf(hex_val, sizeof(hex_val), "%02X", operand[i]);
                strcat(temp_objc, hex_val);
                objc_len++;
            }
            objc_len--;
        }
        if (strcmp(opcode, "WORD") == 0) {
            snprintf(temp_objc, sizeof(temp_objc), "^%06X", (int)strtol(operand, NULL, 10));
            objc_len = 3;
        }
        if (text_rec_len + objc_len <= 9) {
            text_rec_len += objc_len;
            strcat(obj_code, temp_objc);
        } else {
            printf("%s^%02X%s\n", text_header, text_rec_len, obj_code);
            fprintf(object_ptr, "%s^%02X%s\n", text_header, text_rec_len, obj_code);
            text_rec_addr += text_rec_len;
            text_rec_len = objc_len;
            snprintf(text_header, sizeof(text_header), "T^%06X", text_rec_addr);
            strcpy(obj_code, temp_objc);
        }
    }
   
    printf("%s^%02X%s\n", text_header, text_rec_len, obj_code);
    fprintf(object_ptr, "%s^%02X%s\n", text_header, text_rec_len, obj_code);
    printf("E^%06X\n", (int)strtol(start_addr, NULL, 16));
    fprintf(object_ptr, "E^%06X\n", (int)strtol(start_addr, NULL, 16));

    fclose(intermediate_ptr);
    fclose(optab_ptr);
    fclose(symtab_ptr);
    fclose(size_ptr);
    fclose(object_ptr);
}
