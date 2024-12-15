#include <stdio.h>
#include <stdlib.h>
#include "Date.h"

Date* createDate(int day, int month, int year) {
    Date* date = (Date*)malloc(sizeof(Date));
    if (date == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    date->day = day;
    date->month = month;
    date->year = year;
    return date;
}

void destroyDate(Date* date) {
    if (date != NULL) {
        free(date);
    }
}


void saveDateToFile(Date date, FILE* file) {
    fprintf(file, "%d,%d,%d\n", date.day, date.month, date.year);
}

// Load a Date from a text file
Date loadDateFromFile(FILE* file) {
    Date date;
    int ignore =fscanf(file, "%d,%d,%d\n", &date.day, &date.month, &date.year);
    return date;
}