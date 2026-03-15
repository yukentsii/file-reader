#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024 //the max length of a line 
#define MAX_WORD_LENGTH 256 //the max lenght of the searched word

//Compare two strings in a case-insensitive manner
int caseInsensitiveCompare(const char *str1, const char *str2, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (tolower((unsigned char)str1[i]) != tolower((unsigned char)str2[i])) {
            return 0;
        }
    }
    return 1;
}
//checking if the character has a word limit.
int isWordBoundary(char c) {
    return c == '\0' || c == ' ' || c == '\t' || c == '\n' || 
           c == '.' || c == ',' || c == '!' || c == '?' || 
           c == ';' || c == ':' || c == '-' || c == '_' ||
           c == '(' || c == ')' || c == '[' || c == ']' ||
           c == '"' || c == '\'' || c == '/';
}
//Find how many times the exact word appears in the line
int countWordInLine(const char *line, const char *word) {
    int count = 0;
    size_t wordLen = strlen(word);
    if (wordLen == 0) return 0;
    
    const char *ptr = line;
    while (*ptr) {
        if (caseInsensitiveCompare(ptr, word, wordLen)) {
            int startIsBoundary = (ptr == line) || isWordBoundary(*(ptr - 1));
            int endIsBoundary = isWordBoundary(*(ptr + wordLen));
            if (startIsBoundary && endIsBoundary) {
                count++;
            }
        }
        ptr++;
    }
    return count;
}

int main() {
    char targetWord[MAX_WORD_LENGTH];
    char fileName[MAX_WORD_LENGTH];
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;
    int totalCount = 0;

    //getting the word to search
    printf("please enter the word: ");
    scanf("%255s", targetWord); 

    //ask user for the file
    printf("please enter the name of the file program gonna search for (for ex: text.txt): ");
    scanf("%255s", fileName);

    file = fopen(fileName, "r");
    
    //check the file
    if (file == NULL) {
        printf("error: cannot find the '%s' file \n", fileName);
        return 1;
    }

    printf("\n--- '%s' file opened correctly and started reading line by line---\n\n", fileName);

    //read the file linebyline
    while (fgets(line, sizeof(line), file) != NULL) {
        lineNumber++;
        
        //we will write the counting program here eventually
        int count = countWordInLine(line, targetWord);
        if (count > 0) {
            printf("line %d (%d times): %s", lineNumber, count, line);
            totalCount += count;
        }
    }
    

    //close the file. good programming practice btw.
    fclose(file);
    
    printf("\n--- file reading done. total of %d line read. ---\n", lineNumber);
    printf("--- '%s' word found %d times in total ---\n", targetWord, totalCount);  

    return 0;
}
