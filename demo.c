#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* passwd() {
    int i = 0;
    char* secret_value = (char*)malloc(20);
    char ch;
    printf("Enter the secret key: ");
    while (1) {
        ch = _getch();
        if (ch == '\r') {
            secret_value[i] = '\0';
            break;
        } else {
            secret_value[i] = ch;
            i++;
            printf("*");
        }
    }
    return secret_value;
}
int main()
{
    char file_name[40],ch,check;
    char* secret_value;
    FILE *ps, *pf;
    int i =0;
    printf("Enter the file name: ");
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strlen(file_name) - 1] = '\0';
    ps = fopen(file_name, "rb");
    if (ps == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    secret_value = passwd();
    pf = fopen("temp.txt", "wb");
    if (pf == NULL) {
        printf("Error creating temp file.\n");
        fclose(ps);
        free(secret_value);
        return 0;
    }
    printf("\nDo you want to encrypt or decrypt the file? [E/D]: ");
    char choice;
    scanf(" %c", &choice);

    if (choice == 'E') {
        while ((ch = fgetc(ps)) != EOF)
        {
            ch = ch + secret_value[i % strlen(secret_value)];
            fputc(ch, pf);
            i++;
        }
        printf("\nThe file %s is successfully encrypted !!!", file_name);
    } else if (choice == 'D') {
        while ((ch = fgetc(ps)) != EOF)
        {
            ch = ch - secret_value[i % strlen(secret_value)];
            fputc(ch, pf);
            i++;
        }
        printf("\nThe file %s is successfully decrypted !!!", file_name);
    } else {
        printf("Invalid choice");
        return 0;
    }

    free(secret_value);
    fclose(ps);
    fclose(pf);
    remove(file_name);
    rename("temp.txt", file_name);

    printf("\nDo you want to see the file [Y/N]? ");
    scanf(" %c", &check);
    if (check == 'Y') {
        ps = fopen(file_name, "rb");
        if (ps == NULL) {
            printf("Error opening file.\n");
            return 0;
        }
        while ((ch = fgetc(ps)) != EOF) {
            printf("%c", ch);
        }
        fclose(ps);
    }
    printf("\n---------------------THANK YOU---------------------\n");
    getch();
    return 0;
}
