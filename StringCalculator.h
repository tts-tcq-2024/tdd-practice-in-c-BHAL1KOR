#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define CONDITION_NOT_MEET -1

int CheckEmptyOrNullInput(const char* numbers) {
    if (numbers == NULL || strlen(numbers) == 0) {
        return 0;
    }
    return CONDITION_NOT_MEET; 
}

int CheckSingleZeroInput(const char* numbers) {
    if (strcmp(numbers, "0") == 0) {
        return 0;
    }
    return CONDITION_NOT_MEET; 
}

int IgnoreNumbersGreaterThan1000(int num) {
    return num <= 1000 ? num : 0;
}

int SumWithDefaultDelimiter(const char* numbers) {
    int sum = 0;
    char* modifiableNums = strdup(numbers);
    char* token = strtok(modifiableNums, ",");
    while (token != NULL) {
        int num = atoi(token);
        sum += IgnoreNumbersGreaterThan1000(num);
        token = strtok(NULL, ",");
    }
    free(modifiableNums);
    return sum;
}

int SumWithNewlineDelimiter(const char* numbers) {
    int sum = 0;
    char* modifiableNums = strdup(numbers);
    for (char* p = modifiableNums; *p; ++p) {
        if (*p == '\n') *p = ',';
    }
    char* token = strtok(modifiableNums, ",");
    while (token != NULL) {
        int num = atoi(token);
        sum += IgnoreNumbersGreaterThan1000(num);
        token = strtok(NULL, ",");
    }
    free(modifiableNums);
    return sum;
}

int SumWithCustomDelimiter(const char* numbers, char delimiter) {
    int sum = 0;
    char* modifiableNums = strdup(numbers);
    for (char* p = modifiableNums; *p; ++p) {
        if (*p == '\n') *p = delimiter;
    }
    char* token = strtok(modifiableNums, &delimiter);
    while (token != NULL) {
        int num = atoi(token);
        sum += IgnoreNumbersGreaterThan1000(num);
        token = strtok(NULL, &delimiter);
    }
    free(modifiableNums);
    return sum;
}

int DetectCustomDelimiter(const char* numbers) {
    if (strncmp(numbers, "//", 2) == 0) {
        return numbers[2];
    }
    return CONDITION_NOT_MEET;
}

int DetectNewlineDelimiter(const char* numbers) {
    if (strchr(numbers, '\n') != NULL) {
        return 1;
    }
    return CONDITION_NOT_MEET;
}

int add(const char* numbers) {
    int result;

    result = CheckEmptyOrNullInput(numbers);
    if (result != CONDITION_NOT_MEET) {
        return result;
    }
    result = CheckSingleZeroInput(numbers);
    if (result != CONDITION_NOT_MEET) {
        return result;
    }
    result = DetectCustomDelimiter(numbers);
    if (result != CONDITION_NOT_MEET) {
        return SumWithCustomDelimiter(numbers + 4, result);
    }
    result = DetectNewlineDelimiter(numbers);
    if (result != CONDITION_NOT_MEET) {
        return SumWithNewlineDelimiter(numbers);
    }

    return SumWithDefaultDelimiter(numbers);
}
