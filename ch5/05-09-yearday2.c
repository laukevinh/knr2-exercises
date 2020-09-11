/* KnR Exercise 05-09   Rewrite the routines day_of_year
    and month_day with pointers instead of indexing. 
    
    Daytab is now an array of 2 pointers pointing to
    int arrays. I also changed subscript notation
    to pointer arithmetic notation. In my first draft,
    I changed as little of the original code as
    possible, which made it very difficult to read.
    e.g. (*(daytab + leap))[month] vs daytab[leap][month]
    
    After looking at clc-wiki, I found it cleaner to
    create a local var to represent the array of days in
    a month. This breaks up the nested parentheses. */

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *p, int *q);

int main()
{
    int year, month, day, yearday;

    year = 2020;
    month = 10;
    day = 20;
    yearday = day_of_year(year, month, day);
    printf("%d-%d-%d day %d\n", year, month, day, yearday);
    month_day(year, yearday, &month, &day);
    printf("%d-%d date %d-%d-%d\n", year, yearday, year, month, day);
    
    year = 2020;
    month = 0;
    day = 20;
    yearday = day_of_year(year, month, day);
    printf("%d-%d-%d day %d\n", year, month, day, yearday);
    month_day(year, yearday, &month, &day);
    printf("%d-%d date %d-%d-%d\n", year, yearday, year, month, day);

    return 0;
}

static char notleapyear[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
static char leapyear[] = {
    0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
static char *daytab[2] = { notleapyear, leapyear};

/* day_of_year:     set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    char *pdaysmonth;

    if (year<0 || month<0 || month>12 || day<0)
        return -1;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    pdaysmonth = *(daytab + leap);
    if (day > *(pdaysmonth + month))
        return -1;
    for (i = 1; i < month; i++)
        day += *pdaysmonth++;
    return day;
}

/* month_day:       set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    int daysyear[2] = { 365, 366 };
    char *pdaysmonth;

    if (year<0 || yearday<0)
        return;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (yearday > daysyear[leap])
        return;
    pdaysmonth = *(daytab + leap);
    for (i = 1; yearday > *pdaysmonth; i++)
        yearday -= *pdaysmonth++;
    *pmonth = i;
    *pday = yearday;
}