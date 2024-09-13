#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONDITION_NOT_MEET -1

bool isNullOrEmpty(const char* str) {
    return str == NULL || strlen(str) == 0;
}

bool isZero(const char* str) {
    return strcmp(str, "0") == 0;
}

int ReturnZeroForEmptyOrNullOrZeroInput(const char* numbers) {
    if (isNullOrEmpty(numbers) || isZero(numbers)) {
        return 0;
    }
    return CONDITION_NOT_MEET;
}

int IgnoreNumbersGreaterThan1000(int num) {
    return num <= 1000 ? num : 0;
}

char* ReplaceNewlineWithDelimiter(const char* numbers, char delimiter) {
    char* modifiableNums = strdup(numbers);
    for (char* p = modifiableNums; *p; ++p) {
        if (*p == '\n') *p = delimiter;
    }
    return modifiableNums;
}

int SumWithDelimiter(const char* numbers, char delimiter) {
    int sum = 0;
    char* modifiableNums = ReplaceNewlineWithDelimiter(numbers, delimiter);
    char* token = strtok(modifiableNums, &delimiter);
    while (token != NULL) {
        int num = atoi(token);
        sum += IgnoreNumbersGreaterThan1000(num);
        token = strtok(NULL, &delimiter);
    }
    free(modifiableNums);
    return sum;
}

int SumWithDefaultDelimiter(const char* numbers) {
    return SumWithDelimiter(numbers, ',');
}

int HandleSpecialCases(const char* numbers) {
    return ReturnZeroForEmptyOrNullOrZeroInput(numbers);
}

int add(const char* numbers) {
    int result = HandleSpecialCases(numbers);
    if (result != CONDITION_NOT_MEET) return result;

    if (strncmp(numbers, "//", 2) == 0) {
        return SumWithDelimiter(numbers + 4, numbers[2]);
    }

    return SumWithDefaultDelimiter(numbers);
}
