#ifndef DATE_H
#define DATE_H

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

Date* createDate(int day, int month, int year);
void destroyDate(Date* date);
void saveDateToFile(Date date, FILE* file);
Date loadDateFromFile(FILE* file);

#endif
