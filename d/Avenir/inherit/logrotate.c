#pragma no_clone
#pragma strict_types

/*
 * Function name: logrotate
 * Description	: Logs text into a file
 * Arguments	: string  log - The filepath to log to.
 *		  string text - The text to log to 'log'.
 *		   int   size - The log filesize limit.
 *		   int rotate - How many backup logs to keep.
 * Notes	: Backup logs have the numerical rotation number
 *		  appended to them. I.e. log, log.1, log.2, log.3, etc.
 */
public varargs int
logrotate(string log, string text, int size = 100000, int rotate = 1)
{
    if (!strlen(log) || !strlen(text))
	return 0;

    if (file_size(log) == -2)
	return 0;

    setuid(); seteuid(geteuid());

    if (file_size(log) > size)
    {
	if (rotate)
	{
	    int sz;

	    while(++sz)
	    {
		if (file_size(log + "." + sz) < 1)
		    break;
	    }

	    while(--sz >= 1)
	    {
		if ((rotate != -1) && (sz >= rotate))
		    continue;
		rename(log + "." + sz, log + "." + (sz + 1));
	    }
	    rename(log, log + ".1");
	}
	else
	{
	    rm(log);
	}
    }
    return write_file(log, text);
}

/*
 * This is here until they 'fix' /sys/global/time.c to include
 * the time in addition to the date in TIME2FORMAT
 */
private mapping MonthToNumMap = ([
    "Jan" : 1, "Feb" : 2, "Mar" : 3, "Apr" : 4, "May" : 5,
    "Jun" : 6, "Jul" : 7, "Aug" : 8, "Sep" : 9, "Oct" : 10,
    "Nov" : 11, "Dec" : 12 ]);

public nomask string
time2format(int timestamp, string format)
{
    string result = "";
    string timestring = ctime(timestamp);
    
    while(strlen(format))
    {
        if (format[0..3] == "yyyy")
        {
            result += timestring[20..23];
            format = format[4..];
            continue;
        }
	else if (format[0..3] == "tttt")
	{
            result += timestring[11..18];
            format = format[4..];
            continue;
	}

        if (format[0..2] == "mmm")
        {
            result += timestring[4..6];
            format = format[3..];
            continue;
        }
	else if (format[0..2] == "ddd")
        {
            result += timestring[0..2];
            format = format[3..];
            continue;
        }

        if (format[0..1] == "mm")
        {
            result += sprintf("%02d", MonthToNumMap[timestring[4..6]]);
            format = format[2..];
            continue;
        }
	else if (format[0..1] == "dd")
        {
            result += sprintf("%02d", atoi(timestring[8..9]));
            format = format[2..];
            continue;
        }
	else if (format[0..1] == "tt")
	{
            result += timestring[11..15];
            format = format[2..];
            continue;
	}

        if (format[0..0] == "m")
        {
            result += MonthToNumMap[timestring[4..6]];
            format = format[1..];
            continue;
        }
	else if (format[0..0] == "d")
        {
            result += atoi(timestring[8..9]);
            format = format[1..];
            continue;
        }

        result += format[0..0];
        format = format[1..];
    }
   
    return result;
}
