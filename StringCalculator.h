#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define CONDITION_NOT_MEET -1

typedef int (*DelimiterHandler)(const char*);

typedef struct {
    char delimiter;
    DelimiterHandler handler;
} DelimiterType;

bool isNullOrEmpty(const char* str) {
    return str == NULL || strlen(str) == 0;
}

bool isZero(const char* str) {
    return strcmp(str, "0") == 0;
}

int CheckEmptyOrNullOrZeroInput(const char* numbers) {
    if (isNullOrEmpty(numbers) || isZero(numbers)) {
        return 0;
    }
    return CONDITION_NOT_MEET;
}

int IgnoreNumbersGreaterThan1000(int num) {
    return num <= 1000 ? num : 0;
}

char* ReplaceNewlineWithDelimiter(const char* numbers, const char* delimiter) {
    char* modifiableNums = strdup(numbers);
    char* p = modifiableNums;
    while ((p = strstr(p, "\n")) != NULL) {
        strncpy(p, delimiter, strlen(delimiter));
        p += strlen(delimiter);
    }
    return modifiableNums;
}

int SumWithDelimiter(const char* numbers, const char* delimiter) {
    int sum = 0;
    char* modifiableNums = ReplaceNewlineWithDelimiter(numbers, delimiter);
    char* token = strtok(modifiableNums, delimiter);
    while (token != NULL) {
        int num = atoi(token);
        sum += IgnoreNumbersGreaterThan1000(num);
        token = strtok(NULL, delimiter);
    }
    free(modifiableNums);
    return sum;
}

int SumWithDefaultDelimiter(const char* numbers) {
    return SumWithDelimiter(numbers, ",");
}

int SumWithNewlineDelimiter(const char* numbers) {
    return SumWithDelimiter(numbers, ",");
}

int SumWithCustomDelimiter(const char* numbers, const char* delimiter) {
    return SumWithDelimiter(numbers, delimiter);
}

int DetectCustomDelimiter(const char* numbers, char* delimiter) {
    if (strncmp(numbers, "//[", 3) == 0) {
        const char* end = strstr(numbers, "]\n");
        if (end != NULL) {
            strncpy(delimiter, numbers + 3, end - (numbers + 3));
            delimiter[end - (numbers + 3)] = '\0';
            return 1;
        }
    }
    return CONDITION_NOT_MEET;
}

int HandleCustomDelimiter(const char* numbers) {
    char delimiter[100] = {0};
    if (DetectCustomDelimiter(numbers, delimiter) != CONDITION_NOT_MEET) {
        return SumWithCustomDelimiter(numbers + strlen(delimiter) + 4, delimiter);
    }
    return CONDITION_NOT_MEET;
}

int HandleNewlineDelimiter(const char* numbers) {
    if (strchr(numbers, '\n') != NULL) {
        return SumWithNewlineDelimiter(numbers);
    }
    return CONDITION_NOT_MEET;
}

int HandleDefaultDelimiter(const char* numbers) {
    return SumWithDefaultDelimiter(numbers);
}

DelimiterType delimiterHandlers[] = {
    {'/', HandleCustomDelimiter},
    {'\n', HandleNewlineDelimiter},
    {',', HandleDefaultDelimiter}
};

int CheckForDelimeterAndComputeSum(const char* numbers) {
    for (int i = 0; i < sizeof(delimiterHandlers) / sizeof(DelimiterType); ++i) {
        int result = delimiterHandlers[i].handler(numbers);
        if (result != CONDITION_NOT_MEET) return result;
    }
    return CONDITION_NOT_MEET;
}

void printExeptionIfNegativeNumber(int foundNegative, const char* message){
    if (foundNegative) {
        fprintf(stderr, "%s\n", message);
        exit(EXIT_FAILURE);
    }
}
void CheckForNegativeNumbers(const char* numbers) {
    char message[256] = "negatives not allowed: ";
    int foundNegative = 0;
    char temp[10];
    const char* ptr = numbers;

    while (*ptr) {
        if (*ptr == '-') {
            foundNegative = 1;
            int num = atoi(ptr);
            sprintf(temp, "%d ", num);
            strcat(message, temp);
        }
        ptr++;
    }
    printExeptionIfNegativeNumber(foundNegative, message);

}

int add(const char* numbers) {
    int result = CheckEmptyOrNullOrZeroInput(numbers);
    if (result != CONDITION_NOT_MEET) return result;

    CheckForNegativeNumbers(numbers);

    result = CheckForDelimeterAndComputeSum(numbers);
    if (result != CONDITION_NOT_MEET ) return result;

    return SumWithDefaultDelimiter(numbers);
}
