#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IntArray
{
    int* arr;
    int size;
} int_arr_t;

void pushString(int** array_ptr, int* size_ptr, int new_int) {
    int* temp = realloc(*array_ptr, (*size_ptr + 1) * sizeof(int));
    if (temp == NULL) {
        perror("Error reallocating memory");
        return;
    }
    *array_ptr = temp;

    (*array_ptr)[*size_ptr] = new_int;

    (*size_ptr)++;
}

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void sortArray(int** arr, int n) {
    int i, j;

    int* new_arr = *arr;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (new_arr[j] > new_arr[j + 1]) {
                swap(&new_arr[j], &new_arr[j+1]);
            }
        }
    }
}

void printWords(char* str, int** evens, int** odds, int* evens_size, int* odds_size) {
    int j = 0, wordCount = 10, ctr = 0;

    char** newString = malloc(wordCount * sizeof(char*)); // Array of strings (Array of arrays of chars)

    if (!newString) {
        perror("Memory allocation failed");
        return;
    }

    for (int i = 0; i <= strlen(str); i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (j > 0) {
                newString[ctr] = malloc((j + 1) * sizeof(char));
                if (!newString[ctr]) {
                    perror("Memory allocation failed");
                    return;
                }
                strncpy(newString[ctr], &str[i - j], j);
                newString[ctr][j] = '\0'; // Assign null terminator
                ctr++; // Increment word count

                if (ctr >= wordCount) {
                    wordCount *= 2;
                    char** temp = realloc(newString, wordCount * sizeof(char*));

                    if (!temp) {
                        perror("Memory reallocation failed");
                        return;
                    }
                    newString = temp;
                }
            }
            j = 0; // Reset character index
        } else {
            if (j == 0) {
                newString[ctr] = malloc(50 * sizeof(char));
                if (!newString[ctr]) {
                    perror("Memory Allocation failed");
                    return;
                }
            }

            newString[ctr][j] = str[i]; // Assign valid character to word
            j++; // Increment to next character in word
        }
    }

    // Print words
    for (int i = 0; i < ctr; i++) {
        if (i % 2 == 0) {
            pushString(evens, evens_size, atoi(newString[i]));
        } else {
            pushString(odds, odds_size, atoi(newString[i]));
        }
        free(newString[i]);
    }
    free(newString);
}

int getTotalDifference(int_arr_t* arr1, int_arr_t* arr2) {
    int len = 0;
    if (arr1->size < arr2->size) {
        len = arr1->size;
    } else {
        len = arr2->size;
    }

    int total = 0;

    for (int i = 0; i < len; i++) {
        total += abs(arr1->arr[i] - arr2->arr[i]);
    }

    return total;
}

int main() {
    FILE *file_ptr;
    char buffer[250];
    
    file_ptr = fopen("day1_input", "r");
    if (file_ptr == NULL) {
        perror("Error opening file.");
        return 1;
    }

    int* evens = NULL;
    int evens_size = 0;
    int* odds = NULL;
    int odds_size = 0;

    while (fgets(buffer, 250, file_ptr))
    {
        buffer[strcspn(buffer, "\n")] = 0; // Remove the newline character
        printWords(buffer, &evens, &odds, &evens_size, &odds_size);
    }

    sortArray(&evens, evens_size);
    sortArray(&odds, odds_size);

    int_arr_t sEvens;
    int_arr_t sOdds;

    sEvens.arr = evens;
    sEvens.size = evens_size;
    sOdds.arr = odds;
    sOdds.size = odds_size;

    int total_diff = getTotalDifference(&sEvens, &sOdds);

    printf("%d\n", total_diff);

    free(evens);
    free(odds);

    fclose(file_ptr);
    return 0;
}