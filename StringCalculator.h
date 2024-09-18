#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int CheckEmptyInput(const char* input) {
    return (input == NULL || strcmp(input, "") == 0) ? 1 : 0;
}

int CheckForNegativeInput(const char* input) {
    return (strstr(input, "-") != NULL);
}

int printExeptionIfNegativeNumber(char* numbers) {
    char buffer[256] = "Negative number found:";
    char* token = strtok(numbers, ",");

    while (token != NULL) {
        int num = atoi(token);
        if (num < 0) {
            char numStr[12];
            sprintf(numStr, " %d", num);
            strcat(buffer, numStr);
        }
        token = strtok(NULL, ",");
    }
    strcat(buffer, "\n");
    printf("%s", buffer);
    return 1;
}


// Function to get the actual delimiter specified within []
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
    if (!foundNewline) {
        strcpy(modifiedInput, input);
    }
    return foundNewline;
}

int CheckForCustomDelimiterAndReplaceWithComma(const char* input, char* modifiedInput) {
    if (input[0] == '/' && input[1] == '/') {
        const char* delimiterEnd = strstr(input, "\n");
        if (delimiterEnd != NULL) {
            size_t delimiterLength = delimiterEnd - input - 2;
            char* delimiter = (char*)malloc(delimiterLength + 1);
            strncpy(delimiter, input + 2, delimiterLength);
            delimiter[delimiterLength] = '\0';
            strcpy(modifiedInput, delimiterEnd + 1);
            ReplaceDelimiterWithComma(modifiedInput, modifiedInput, delimiter);
            free(delimiter);
            return 1;
        }
    }
    strcpy(modifiedInput, input);
    
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

int ReturnZeroForEmptyInput(const char* numbers) {
    return 0;
}

typedef int (*CheckFunction)(const char*, char*);
typedef int (*ResultFunction)(char*);

typedef struct {
    CheckFunction checkFunction;
    ResultFunction resultFunction;
    int enabled;
} Check;

int add(const char* numbers) {
    int ReturnValue = 0;
    char* modifiedNumbers = (char*)malloc(strlen(numbers) + 1);

    Check checks[] = {
    { (CheckFunction)CheckEmptyInput, (ResultFunction)ReturnZeroForEmptyInput, 0 },
    { (CheckFunction)CheckForCustomDelimiterAndReplaceWithComma, (ResultFunction)SumNumbers, 0 },
    { (CheckFunction)CheckNewlineDelimiterAndReplaceWithComma, (ResultFunction)SumNumbers, 0 },
    { (CheckFunction)CheckForNegativeInput, (ResultFunction)printExeptionIfNegativeNumber, 0 }
    };

    for (int i = 0; i < 4; i++) {
        checks[i].enabled = checks[i].checkFunction(numbers, modifiedNumbers);
        if (checks[i].enabled) {
            ReturnValue = checks[i].resultFunction(modifiedNumbers);
            break;
        }
    }

    if (ReturnValue == 0 ) {
        ReturnValue = SumNumbers(numbers);
    }

    free(modifiedNumbers);
    return ReturnValue;
}
