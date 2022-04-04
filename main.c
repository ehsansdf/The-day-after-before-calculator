#include <stdio.h>
struct date {
    int month;
    int day;
    int year;
};

int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int leapyear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

int validdate(struct date now) {
    int daysmon;
    if (now.year <= 1582)                   // pre-Gregorian
        return 0;
    if (now.month < 1 || now.month > 12)
        return 0;
    daysmon = daysPerMonth[now.month-1];
    if (leapyear(now.year) && now.month == 2)
        daysmon++;
    if (now.day < 1 || now.day > daysmon)
        return 0;
    return 1;
}

void bumpdate(struct date* now,struct date* Tom,struct date* Yes ) {
    int daysmon = daysPerMonth[now->month-1];
    int T,Y,To,Ye;
    *Tom=*now;
    *Yes=*now;
    To=daysmon;
    Ye=daysmon;
    if (leapyear(now->year) && now->month == 2)To++;

    //================================
    if (++Tom->day > To)
    {
     Tom->day = 1;
      if (++Tom->month > 12)
      {
        Tom->month = 1;
        Tom->year++;
      }
    }
    //================================
    if (--Yes->day<1) //04/01/2022,01/01/2022,02/25/2022,03/01/2024,02/28/2024,01/01/2000
    {

      if(now->month>=2)Yes->day =daysPerMonth[now->month-2];
      else {Yes->day =daysPerMonth[now->month+10];Yes->year--;}

      if (leapyear(now->year) && now->month == 3)Yes->day++;

      if (--Yes->month<1)
      {
        Yes->month = 12;
      }
    }

}

int main (void) {
    struct date today, tomorrow ,yesterday,tom,yes;
    while(1){
    printf("Enter today's date (dd/mm/yyyy): ");
    if (3 != scanf("%d %*[/-] %d %*[/-] %d", &today.day, &today.month, &today.year)) {
        printf ("Need the proper date format\n");
        return 1;
    }
    if (!validdate(today)) {
        printf ("Invalid date\n");
        return 1;
    }

    bumpdate(&today,&tom,&yes);

    printf("Tomorrow's date is %02d/%02d/%04d\n",  tom.day,tom.month, tom.year);
    printf("Yesterday's date is %02d/%02d/%04d\n",  yes.day,yes.month, yes.year);
    //return 0;
}
}
