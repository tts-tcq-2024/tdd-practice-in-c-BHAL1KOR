#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONDITION_NOT_MEET -1

void printExeptionIfNegativeNumber(int foundNegative, const char* message) {
    if (foundNegative) {
        printf("Negatives not allowed: %s\n", message);
        exit(1);
    }
}

int CheckEmptyOrNullOrZeroInput(const char* numbers) {
    if (numbers == NULL || *numbers == '\0') {
        return 0;
    }
    return CONDITION_NOT_MEET;
}

void CheckForNegativeNumbers(const char* numbers) {
    int foundNegative = 0;
    char message[100] = "";
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

int SumWithCustomDelimiter(const char* numbers, const char* delimiter) {
    int sum = 0;
    char* token;
    char* numbersCopy = strdup(numbers);
    token = strtok(numbersCopy, delimiter);
    while (token != NULL) {
        sum += atoi(token);
        token = strtok(NULL, delimiter);
    }
    free(numbersCopy);
    return sum;
}

int DetectCustomDelimiter(const char* numbers, char* delimiter) {
    if (strncmp(numbers, "//", 2) == 0) {
        const char* end = strstr(numbers, "\n");
        if (end != NULL) {
            strncpy(delimiter, numbers + 2, end - (numbers + 2));
            delimiter[end - (numbers + 2)] = '\0';
            return 1;
        }
    }
    return CONDITION_NOT_MEET;
}

int HandleCustomDelimiter(const char* numbers) {
    char delimiter[100] = {0};
    if (DetectCustomDelimiter(numbers, delimiter) != CONDITION_NOT_MEET) {
        return SumWithCustomDelimiter(numbers + strlen(delimiter) + 3, delimiter);
    }
    return CONDITION_NOT_MEET;
}

int HandleNewlineDelimiter(const char* numbers) {
    return CONDITION_NOT_MEET; // Placeholder for handling newline delimiter
}

int HandleDefaultDelimiter(const char* numbers) {
    return CONDITION_NOT_MEET; // Placeholder for handling default delimiter
}

int CheckForDelimeterAndComputeSum(const char* numbers) {
    int result = HandleCustomDelimiter(numbers);
    if (result != CONDITION_NOT_MEET) {
        return result;
    }
    result = HandleNewlineDelimiter(numbers);
    if (result != CONDITION_NOT_MEET) {
        return result;
    }
    return HandleDefaultDelimiter(numbers);
}

int SumWithDefaultDelimiter(const char* numbers) {
    int sum = 0;
    char* token;
    char* numbersCopy = strdup(numbers);
    token = strtok(numbersCopy, ",");
    while (token != NULL) {
        sum += atoi(token);
        token = strtok(NULL, ",");
    }
    free(numbersCopy);
    return sum;
}

int add(const char* numbers) {
    int result = CheckEmptyOrNullOrZeroInput(numbers);
    if (result != CONDITION_NOT_MEET) return result;

    CheckForNegativeNumbers(numbers);

    result = CheckForDelimeterAndComputeSum(numbers);
    if (result != CONDITION_NOT_MEET) return result;

    return SumWithDefaultDelimiter(numbers);
}
