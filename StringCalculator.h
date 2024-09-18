#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pch.h"
#include <setjmp.h>
jmp_buf buf;



int CheckEmptyInput(const char* input) {
    return (input == NULL || strcmp(input, "") == 0) ? 1 : 0;
}

int CheckForNegativeInput(const char* input) {
    return (strstr(input, "-") != NULL);
}

// Function to get the actual delimiter speicfied within []
void ExtractActualDelimiter(const char* delimiter, char* actualDelimiter) {
    size_t delimiterLength = strlen(delimiter);

    if (delimiter[0] == '[' && delimiter[delimiterLength - 1] == ']') {
        strncpy(actualDelimiter, delimiter + 1, delimiterLength - 2);
        actualDelimiter[delimiterLength - 2] = '\0';
    }
    else {
        strcpy(actualDelimiter, delimiter);
    }
}

void ReplaceDelimiterWithComma(char* input, char* output, const char* delimiter) {
    size_t delimiterLength = strlen(delimiter);
    char* actualDelimiter = (char*)malloc(delimiterLength + 1);

    ExtractActualDelimiter(delimiter, actualDelimiter);
    size_t actualDelimiterLength = strlen(actualDelimiter);

    while (*input) {
        if (strncmp(input, actualDelimiter, actualDelimiterLength) == 0) {
            *output = ',';
            input += actualDelimiterLength;
        }
        else {
            *output = *input;
            input++;
        }
        output++;
    }
    *output = '\0';

    free(actualDelimiter);
}

int CheckNewlineDelimiterAndReplaceWithComma(const char* input, char* modifiedInput) {
    int foundNewline = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '\n') {
            foundNewline = 1;
            ReplaceDelimiterWithComma((char*)input, modifiedInput, "\n");
            break;
        }
    }
    return foundNewline;
}

int CheckForCustomDelimiterAndReplaceWithComma(const char* input, char* modifiedInput) {
    if (input[0] == '/' && input[1] == '/') {
        const char* delimiterEnd = strstr(input, "\n");
        size_t delimiterLength = delimiterEnd - input - 2;
        char* delimiter = (char*)malloc(delimiterLength + 1);
        strncpy(delimiter, input + 2, delimiterLength);
        delimiter[delimiterLength] = '\0';
        strcpy(modifiedInput, delimiterEnd + 1);
        printf("identified delimeter = %s\r\n", delimiter);
        ReplaceDelimiterWithComma(modifiedInput, modifiedInput, delimiter);
        free(delimiter);
        return 1;
    }
    return 0;
}

int IgnoreNumbersGreaterThan1000(int num) {
    return num <= 1000 ? num : 0;
}

int SumNumbers(const char* numbers) {
    int sum = 0;
    char* numbersCopy = strdup(numbers);
    char* token = strtok(numbersCopy, ",");

    while (token != NULL) {
        int num = atoi(token);
        sum += IgnoreNumbersGreaterThan1000(num);
        token = strtok(NULL, ",");
    }

    free(numbersCopy);
    return sum;
}

void throw_exception(const char* message) {
    printf("%s\n", message);
    longjmp(buf, 1);
}
void printExeptionIfNegativeNumber(const char* input) {
    char negatives[256] = "";
    char* inputCopy = strdup(input);
    char* token = strtok(inputCopy, ",");

    while (token != NULL) {
        int num = atoi(token);
        if (num < 0) {
            if (strlen(negatives) > 0) {
                strcat(negatives, ", ");
            }
            char numStr[12];
            sprintf(numStr, "%d", num);
            strcat(negatives, numStr);
        }
        
        token = strtok(NULL, ",");
    }

    free(inputCopy);

    if (strlen(negatives) > 0) {
        char message[512];
        sprintf(message, "negatives not allowed: %s", negatives);
        throw_exception(message);
    }
}

int ReturnZeroForEmptyInput() {
    return 0;
}

typedef int (*CheckFunction)(const char*, char*);

int add(const char* numbers) {
    int ReturnValue = 0;
    char* modifiedNumbers = (char*)malloc(strlen(numbers) + 1);

    CheckFunction checks[] = {
        (CheckFunction)CheckEmptyInput,
        (CheckFunction)CheckForCustomDelimiterAndReplaceWithComma,
        (CheckFunction)CheckNewlineDelimiterAndReplaceWithComma,
        (CheckFunction)CheckForNegativeInput
    };

    for (int i = 0; i < 4; i++) {
        if (checks[i](numbers, modifiedNumbers)) {
            switch (i) {
                case 0:
                    ReturnValue = ReturnZeroForEmptyInput();
                    break;
                case 1:
                    ReturnValue = SumNumbers(modifiedNumbers);
                    break;
                case 2:
                    ReturnValue = SumNumbers(modifiedNumbers);
                    break;
                case 3:
                   printExeptionIfNegativeNumber(numbers);
                    break;
            }
            break;
        }
    }

    if (ReturnValue == 0 && !CheckForNegativeInput(numbers)) {
       ReturnValue = SumNumbers(numbers);
    }

    free(modifiedNumbers);
    return ReturnValue;
}
