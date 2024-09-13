#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int is_empty_or_null(const char* numbers) {
    return numbers == NULL || strlen(numbers) == 0;
}

int is_single_zero(const char* numbers) {
    return strcmp(numbers, "0") == 0;
}

int ignore_numbers_greater_than_1000(int num) {
    return num <= 1000 ? num : 0;
}

int sum_with_delimiter(const char* numbers, char delimiter) {
    int sum = 0;
    char* modifiable_nums = strdup(numbers);
    char* token = strtok(modifiableNums, &delimiter);
    while (token != NULL) {
        int num = atoi(token);
        sum += ignore_numbers_greater_than_1000(num);
        token = strtok(NULL, &delimiter);
    }
    free(modifiableNums);
    return sum;
}

int detect_custom_delimiter(const char* numbers) {
    return strncmp(numbers, "//", 2) == 0 ? numbers[2] : CONDITION_NOT_MEET;
}

int detect_newline_delimiter(const char* numbers) {
    return strchr(numbers, '\n') != NULL;
}

int add(const char* numbers) {
    int result;

    if (is_empty_or_null(numbers)) {
        return 0;
    }

    if (is_single_zero(numbers)) {
        return 0;
    }

    if (detect_custom_delimiter(numbers)) {
        return sum_with_delimiter(numbers + 4, detect_custom_delimiter(numbers));
    }

    if (detect_newline_delimiter(numbers)) {
        return sum_with_delimiter(numbers, '\n');
    }

    return sum_with_delimiter(numbers, ',');
}
