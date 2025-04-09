bool isLeap(int year) 
{ 
    return (((year % 4 == 0) &&  (year % 100 != 0)) || (year % 400 == 0)); 
} 

bool isDateValid(const char *dt1)
{
    int day, month, year;
    sscanf(dt1, "%d%*c%d%*c%d", &day, &month, &year);

    long ttime = time(NULL);
    tm *time = localtime(&ttime);

    if(day<1 || day>31) return false;
    if(month<1 || month>12) return false;
    if(year<0 || year>time->tm_year+1900) return false;

    if(year==time->tm_year+1900)
    {
        //if((day>time->tm_mday) || (month>time->tm_mon+1)) return false;
        if(month == time->tm_mon+1)
        {
            if(day > time->tm_mday) return false;
        }
    }

    if (month == 2) 
    { 
        if (isLeap(year)) 
        return (day <= 29); 
        else
        return (day <= 28); 
    } 

    //31 days:
    else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if(day>31) return false;
    }
    else //30 days:
    {
        if(day>30) return false;
    }

    return true;

}

bool isDateValid(const char dt1[], const char dt2[])
{
    long ttime = time(NULL);
    tm *time = localtime(&ttime);

    int accday, accmon, accyr;
    sscanf(dt2, "%d%*c%d%*c%d", &accday, &accmon, &accyr);

    int thisday, thismon, thisyr;
    thisday = time->tm_mday;
    thismon = time->tm_mon+1;
    thisyr = time->tm_year+1900;

    int day, mon, yr;
    sscanf(dt1, "%d%*c%d%*c%d", &day, &mon, &yr);

    if(yr<accyr || yr>thisyr) return false;
    if(yr == accyr)
    {
        if(mon < accmon) return false;
    }
    if(yr == thisyr)
    {
        if(mon > thismon) return false;
    }
    if(yr == accyr && mon == accmon)
    {
        if(day<accday) return false;
    }
    if(yr == thisyr && mon == thismon)
    {
        if(day>thisday) return false;
    }
    return true;
}