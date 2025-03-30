#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populateReports(char* scanned, int*** reports, int reportsIndex) {
    int i = 0;
    int levelsIndex = 0;
    int** reportsArr = *reports;

    while (scanned[i] != '\n') {
        if (scanned[i] != ' ') {
            reportsArr[reportsIndex][levelsIndex] = (int)scanned[i];
        } else {
            levelsIndex++;
        }
        i++;
    }
}

int main() {
    FILE* file_ptr;
    char scanned[50];
    int reports[20][20];

    file_ptr = fopen("input.txt", "r");
    if (NULL == file_ptr) {
        perror("Error opening file.");
        return 1;
    }
    
    int reportsIndex = 0;
    while (fgets(scanned, 50, file_ptr))
    {
        populateReports(scanned, &reports, reportsIndex);
        reportsIndex++;
    }
}