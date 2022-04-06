#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_SIZE ((size_t) 7)

bool onlyLetters(char* str, int str_len) {
    // loop through each character in the string
    for (int i = 0; i < str_len; i++) {
        // compare each char to ascii values
        if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') {
            return false;
        }
    }
    return true;
}

bool onlyLower(char* str, int str_len) {
    // loop through each character in the string
    for (int i = 0; i < str_len; i++) {
        // compare each char to ascii values
        if (str[i] < 'a' || str[i] > 'z') {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    
    FILE* allWords = fopen("bin/allWords.txt", "r");
    FILE* someWords = fopen("bin/someWords.txt", "w"); // only the words we want

    if (allWords == NULL) {
        printf("Couldn't open words.txt\n");
        exit(-1);
    } else if (someWords == NULL) {
        printf("Couldn't open someWords\n");
        exit(-1);
    }

    // line buffer
    // we only need 6 chars: 5 for the words we want, one extra to check for end of line char vs another char
    char* buf = (char*) malloc(BUF_SIZE * sizeof(char));
    size_t *bytesWritten = (size_t*) malloc(1 * sizeof(unsigned long)); // we only need this for getline

    // loop til end of file
    while (getline(&buf, bytesWritten, allWords) >= 0) {
        // check if the line is a 5 letter word
        // i.e. the last char is an eof
        if (buf[BUF_SIZE - 1] == '\n' && onlyLower(buf, BUF_SIZE - 1)) {
            // write the whole buffer which includes the newline
            fprintf(someWords, "%s", buf); 
        }
    }

    // free memory
    free(buf);
    free(bytesWritten);
    fclose(allWords);
    fclose(someWords);
}