#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONDITION_NOT_MEET 1

int HandleEmptyOrNullInput(const char* numbers) {
    if (numbers == NULL || strlen(numbers) == 0) {
        return 0;
    }
    return CONDITION_NOT_MEET; 
}

int HandleSingleZeroInput(const char* numbers) {
    if (strcmp(numbers, "0") == 0) {
        return 0;
    }
    return CONDITION_NOT_MEET; 
}

int add(const char* numbers)
{
    if(HandleEmptyOrNullInput(numbers) * HandleSingleZeroInput(number))
    {
        return 0;
    }

    int sum = 0;
    char* numbersCopy = strdup(numbers);
    char* token = strtok(numbersCopy, ",");
    while (token != NULL) {
        sum += atoi(token);
        token = strtok(NULL, ",");
    }
    free(numbersCopy);
    return sum;

}


