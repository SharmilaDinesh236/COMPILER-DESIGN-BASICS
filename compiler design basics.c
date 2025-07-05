#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of C keywords to check
char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

// Function to check if the given word is a keyword
int isKeyword(char word[]) {
    int i;
    for (i = 0; i < 32; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *file;
    char ch;
    char word[20];  // To hold the word/identifier
    int i;

    // Open the file named "myfile.txt"
    file = fopen("myfile.txt", "r");

    if (file == NULL) {
        printf("Error: Could not open myfile.txt\n");
        return 1;
    }

    printf("Lexical Analysis Result:\n\n");

    while ((ch = fgetc(file)) != EOF) {
        // Skip spaces and new lines
        if (isspace(ch))
            continue;

        // If the character is alphabetic (start of a keyword or identifier)
        if (isalpha(ch)) {
            i = 0;
            word[i++] = ch;

            ch = fgetc(file);
            while (isalnum(ch)) {
                word[i++] = ch;
                ch = fgetc(file);
            }

            word[i] = '\0';   // End the string
            ungetc(ch, file); // Put back the non-alphanumeric character

            if (isKeyword(word))
                printf("Keyword: %s\n", word);
            else
                printf("Identifier: %s\n", word);
        }

        // If it's an operator
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                 ch == '=' || ch == '<' || ch == '>' || ch == '%') {
            printf("Operator: %c\n", ch);
        }

        // You can add more cases for numbers, brackets, etc. if needed
    }

    fclose(file); // Always close the file
    return 0;
}
