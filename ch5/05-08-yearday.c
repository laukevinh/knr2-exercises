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

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year:     set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (year<0 || month<0 || month>12 || day<0)
        return -1;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (day > daytab[leap][month])
        return -1;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day:       set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    int ndays[2] = { 365, 366 };

    if (year<0 || yearday<0)
        return;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (yearday > ndays[leap])
        return;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}