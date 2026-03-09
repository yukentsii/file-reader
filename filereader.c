#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024 //the max length of a line 
#define MAX_WORD_LENGTH 256 //the max lenght of the searched word

int main() {
    char targetWord[MAX_WORD_LENGTH];
    char fileName[MAX_WORD_LENGTH];
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;

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
        printf("line %d: %s", lineNumber, line); 
    }

    //close the file. good programming practice btw.
    fclose(file);
    
    printf("\n--- file reading done. total of %d line read. ---\n", lineNumber);

    return 0;
}
