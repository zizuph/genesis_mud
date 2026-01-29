/*
 *  /d/Genesis/census/census_master.c
 *
 *  This object logs the average number of players per day. To see the
 *  log itself, check the file:
 *
 *  Copyright (c) October 2007, by Cooper Sherry (Gorboth)
 *
 *  Modification Log:
 *    - Changed to restore data map only when necessary (Petros, 3.2010)
 */
#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

inherit "/d/Emerald/lib/data_manager";

#include <files.h>
#include <language.h>
#include <time.h>



/* Global Variables */
public int               Hour = 0;
public mapping           Data;
public string           *Dates;
public string            Next_Week = "";
public int               Week_Num = 0;

static int               Census_updated = 1; // indicates that census data has been updated since last retrieval

/* Prototypes */
public void     create_data_manager();
public int      query_hour();
public int      filter_valid_player(object player);
public int      tally_players(string guild);
public void     perform_census();
public int     *parse_date(string date);
public string   display_date(int *date_arr);
public int      census_map();
public mixed    census_average(mixed *census_data, int ftrue = 0);
public int      census_max(int *census_data);
public void     census_graph_day(object pl, int *graph_arr1, int *date1, int *date2 = ({}), int week = 0, int *graph_arr2 = ({}));
public mapping  query_census_data();
public string  *query_census_dates();
public int      place_float(float f, int i);
public void     census_graph_year(object pl, mixed *graph_arr, int *date);
public string  *draw_year_lines(mixed graph_arr);
public void     census_chart(object who, string a_start, string a_end, string b_start, string b_end);
public float   *chart_time_period(string start, string end, object who);
public string  *query_open_guilds();
public int      guild_is_open(string name);
public int      check_guild_membership(object who, string gname);


/* Definitions */
#define  TELL_G(x)      find_living("gorboth")->catch_tell(x + "\n")
#define  CENSUS_DIR     "/d/Genesis/census/"
#define  CENSUS_OLD_DIR (CENSUS_DIR + "old/")
#define  CENSUS_FILE    "census"
#define  CENSUS_PATH    (CENSUS_DIR + CENSUS_FILE)
#define  START_DATE     "20071013"


/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    set_save_dir(CENSUS_DIR);
    set_garbage_dir(CENSUS_OLD_DIR);

    /* We'll wait a half-hour after reboot to give players a chance to
     * log in and be counted. Those who just log in to save the droproom
     * will probably be gone in 30 minutes, which is good, because we want
     * to know who the people actually playing are.
     */
    set_alarm(600.0, 0.0, perform_census); /* wait 10 minutes after reset */

    setuid();
    seteuid(getuid());

    census_map();
} /* create_data_manager */

/*
 * Function:    query_census_data
 * Description: Public interface for outside callers to retrieve the census
 *              data stored created and populated using perform_census.
 */
public mapping
query_census_data()
{
    census_map();
    return Data;
}

/*
 * Function:    query_census_dates
 * Description: Public interface for outside callers to retrieve the
 *              dates for each perform_census call.
 */
public string *
query_census_dates()
{
    census_map();
    return Dates;
}

/*
 * Function name:        query_hour
 * Description  :        See what hour of gametime we are in
 * Returns      :        int - numeral representing the hour of the day
 */
public int
query_hour()
{
    int     decimal_1,
            decimal_2;

    decimal_1 = atoi(ctime(time())[11..11]);
    decimal_2 = atoi(ctime(time())[12..12]);

    if (!decimal_1)
    {
        return decimal_2;
    }
    else
    {
        decimal_1 *= 10;
        return decimal_1 + decimal_2;
    }
} /* query_hour */


/*
 * Function name:        filter_valid_player
 * Description  :        only non-linkdead, non-jr, non-wizards are
 *                       considered valid players. We also check to
 *                       make sure that this object is not a null
 *                       login object.
 * Arguments    :        object player - the object to check for
 *                                       valid player status
 * Returns      :        1 - this is a valid player
 *                       0 - not a valid player
 */
public int
filter_valid_player(object player)
{
    if (!objectp(player)
        || player->query_wiz_level()
        || !strlen(player->query_name())
        || player->query_name()[-2..] == "jr")
    {
        return 0;
    }

    return 1;
} /* filter_valid_player */


/*
 * Function name:    tally_players
 * Description  :    Gets a count of the non-linkdead non-wizard players
 *                   who are currently in the game, perhaps in a specific
 *                   guild if specified. We exclude jrs.
 * Arguments    :    string guild - the short name of the guild to
 *                                  check membership in. If null string
 *                                  then we do a census for all players.
 * Returns      :    int - the number of players
 */
public int
tally_players(string guild)
{
    object *online = filter((users()), filter_valid_player);

    if (guild == CENSUS_FILE)
    {
        return sizeof(online);
    }

    return sizeof(filter(online, &check_guild_membership(, guild)));
} /* tally_players */


/*
 * Function name:    perform_census
 * Description  :    take an hourly reading on the number of players
 *                   online and write it to a save file.
 */
public void
perform_census()
{
    string  entry = TIME2FORMAT(time(), "yyyymmdd"),
           *which_census = ({ CENSUS_FILE });
    mixed  *new_tally,
           *old_tally;
    int     i,
            weekday,
            count = 0;

    switch (ctime(time())[0..2])
    {
        case "Sun":
            weekday = 1;
            break;
        case "Mon":
            weekday = 2;
            break;
        case "Tue":
            weekday = 3;
            break;
        case "Wed":
            weekday = 4;
            break;
        case "Thu":
            weekday = 5;
            break;
        case "Fri":
            weekday = 6;
            break;
        case "Sat":
            weekday = 7;
            break;
        default:
            weekday = 0;
            break;
    }

    which_census += query_open_guilds();

    TELL_G("\n\nCensus Time! "+ " Day: " + sprintf("%8s", entry + " ")
              + "Hour: " + sprintf("%2d", query_hour()));
    foreach(string this_census: which_census)
    {
        new_tally = allocate(25),
        old_tally = get_info(this_census, entry);

        if (sizeof(old_tally))
        {
            for (i = 0; i < sizeof(old_tally); i++)
            {
                new_tally[i] = old_tally[i];
            }
        }

        count = tally_players(this_census);
        new_tally[24] = weekday;
        new_tally[query_hour()] = count;

        set_info(this_census, entry, new_tally);
        // Set the Census_updated so that the Data and Dates vars
        // can be refreshed on the next query_census_* call.
        Census_updated = 1;

        if (count)
        {
            TELL_G("   -- " + sprintf("%15s ", this_census)
              + ": " + sprintf("%4d", count));
        }
    }
    TELL_G("\n");

    set_alarm(3600.0, 0.0, perform_census); /* wait an hour */
} /* perform_census */


/*
 * Function name:        parse_date
 * Description  :        This function takes the string for a given date,
 *                       and returns the different pieces of information
 * Arguments    :        string date - the yyyymmdd format for the date
 * Returns      :        int array - element 0: year,
 *                                   element 1: month,
 *                                   element 2: day,
 *                                   element 3: weekday (1-7 for Sun-Sat)
 */
public int *
parse_date(string date)
{
    int   *date_info = get_info(CENSUS_FILE, date);

    return ({ date[0..3],
              date[4..5],
              date[6..7],
              date_info[24],
           });
} /* parse_date */


/*
 * Function name:        display_date
 * Description  :        print the mm/dd/yyyy format given by
 *                       parse_date()
 * Arguments    :        int *date_arr - the array from parse_date
 * Returns      :        string - the mm/dd/yyyy format
 */
public string
display_date(int *date_arr)
{
    string  month;

    switch(date_arr[1])
    {
        case "01":
            month = "Jan";
            break;
        case "02":
            month = "Feb";
            break;
        case "03":
            month = "Mar";
            break;
        case "04":
            month = "Apr";
            break;
        case "05":
            month = "May";
            break;
        case "06":
            month = "Jun";
            break;
        case "07":
            month = "Jul";
            break;
        case "08":
            month = "Aug";
            break;
        case "09":
            month = "Sep";
            break;
        case "10":
            month = "Oct";
            break;
        case "11":
            month = "Nov";
            break;
        case "12":
            month = "Dec";
            break;
    }

    return month + " " + date_arr[2] + " " + date_arr[0];
} /* display_date */


/*
 * Function name:        census_map
 * Description  :        load the current data from the census file into
 *                       a mapping variable, and put all the dates into
 *                       an array. Only does the actual disk retrieval when
 *                       census data has been updated.
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
census_map()
{
    if (!Census_updated)
    {
        // No need to load the data from disk if nothing has been updated.
        return 1;
    }

    // Restore the data from disk.
    Data = restore_map(CENSUS_PATH);
    Dates = m_indices(Data);
    // Update the Census_updated so that the next retrieval will not pull from
    // disk.
    Census_updated = 0;

    return 1;
} /* census_map */


/*
 * Function name:        census_average
 * Description  :        get the mean of the integer values in
 *                       an array. The default is to get the mean.
 * Arguments    :        mixed census_data - The array of values.
 *                       int ftrue - true if we want a float return
 *                                   default is 0
 * Returns      :        int - the mean value of all index points
 */
public mixed
census_average(mixed *census_data, int ftrue = 0)
{
    int     i;
    int     float_true;
    int     pl_average = 0;
    float   f_pl_average = 0.0;
    float   f;


    if (!sizeof(census_data))
    {
        return 0;
    }

    float_true = floatp(census_data[0]);

    if (float_true)
    {
        for (i = 0; i < sizeof(census_data); i++)
        {
            f_pl_average += census_data[i];
        }

        f_pl_average /= itof(i);

        return f_pl_average;
    }

    for (i = 0; i < sizeof(census_data); i++)
    {
        pl_average += census_data[i];
    }

    f = itof(pl_average);
    pl_average /= i;

    if (ftrue)
    {
        f /= itof(i);
        return f;
    }

    return pl_average;
} /* census_average */


/*
 * Function name:        census_max
 * Description  :        Get the max from a given array of values
 * Arguments    :        int census_data - The array of values.
 * Returns      :        int - the max value from the array
 */
public int
census_max(int *census_data)
{
    return applyv(max, census_data);
} /* census_max */


/*
 * Function name:        census_graph_day
 * Description  :        This function presents data over 24 hours in a
 *                       nice graph form for analysis purposes. If two
 *                       arrays are provided, then it shows a comparison
 *                       of the two on the graph.
 * Arguments    :        object pl      - the player who will receive a
 *                                        printout of the data
 *                       int graph_arr1 - an array of data for the day we
 *                                        want to graph.
 *                       int date1      = array identifying the date for
 *                                        graph_arr1:
 *                                          [0]: year,
 *                                          [1]: month,
 *                                          [2]: day
 *                       int date2      - array identifying the date for
 *                                        graph_arr2, default set to
 *                                        empty array.
 *                       int week       - 1: We want to graph an average
 *                                           week by hour.
 *                                        2: We want to graph an average
 *                                           week by day.
 *                                        0: We are graphing a single day
 *                                           rather than a week (default)
 *                                        average week rather than a
 *                                        particular day (default = 0)
 *                       int graph_arr2 - Optional second array of data
 *                                        that we can use to compare
 *                                        two different days. Default
 *                                        is an empty array.
 */
public void
census_graph_day(object pl, int *graph_arr1, int *date1, int *date2 = ({}), int week = 0, int *graph_arr2 = ({}))
{
    string  day2 = " ",
            graphtxt,
            graphword = " ",
            graphline = "",
            weektxt = (week ? "week of " : ""),
            frontspaces = " ",
            backspaces = "";
    int     i, n, k,
            compare = (sizeof(graph_arr2)),
           *avg_arr = allocate(sizeof(graph_arr1)),
           *avg_arr2 = allocate(sizeof(graph_arr2));

    if (week == 2)
    {
        frontspaces = "     ";
        backspaces  = "   ";
    }

    if (compare)
    {
        day2 = "O";
    }

    /* First, lets determine the highest point of the graph */
    for (i = 0, n = 0; i < sizeof(graph_arr1); i++)
    {
        if (graph_arr1[i] > n)
        {
            n = graph_arr1[i];
        }

        if (compare)
        {
            if (graph_arr2[i] > n)
            {
                n = graph_arr2[i];
            }
        }
    }

    /* We'll use even numbers for the x axis, so lets make sure we have
     * that in our height.
     */
    if (n - n / 2) /* oops, its an odd number, lets add one */
    {
        n++;
    }

    /* Each point on the graph will represent 2 players, so lets go ahead
     * and divide the number in half, now that we are sure it is even.
     */
    n /= 2;

    if (n < 8)
    {
        n = 8; /* Just so we can draw proper labels on the graph */
    }

    /* Okay! Lets draw the graph! */

    pl->catch_tell(
        "------------------------------------------------------------------"
      + "------------\n");

    if (compare)
    {
        pl->catch_tell(sprintf("%|80s",
            "Comparisons between two time periods:\n"));
        pl->catch_tell(sprintf("%|80s",
            weektxt + display_date(date1) + " = O\n"));
        pl->catch_tell(sprintf("%|80s",
            weektxt + display_date(date2) + " = @\n"));
    }
    else
    {
        pl->catch_tell(sprintf("%|80s",
            "Hourly player activity for " + weektxt + display_date(date1)
          + "\n"));
    }

    pl->catch_tell(
        "------------------------------------------------------------------"
      + "------------\n");

    while (n)
    {
        if (n < 8)
        {
            graphword = "PLAYERS"[7-n..7-n];
        }

        graphline = graphword + (" " * (4 - strlen("" + (n*2)))) + (n*2) + "|";

        for (i = 0; i < sizeof(graph_arr1); i++)
        {
            graphline += frontspaces;
            avg_arr[i] = graph_arr1[i];

            if (graph_arr1[i] < (n*2))
            {
                if (graph_arr1[i] > ( (n - 1) * 2))
                {
                    graphline += ".";
                }
                else
                {
                    graphline += " ";
                }
            }
            else
            {
                graphline += "O";
            }

            if (compare)
            {
                avg_arr2[i] = graph_arr2[i];
                if (graph_arr2[i] < (n*2))
                {
                    if (graph_arr2[i] > ( (n - 1) * 2))
                    {
                        graphline += ".";
                    }
                    else
                    {
                        graphline += " ";
                    }
                }
                else
                {
                    graphline += "@";
                }
            } /* if (compare) */
            else
            {
                graphline += " ";
            }

            graphline += backspaces;
        } /* for (i = 0; i < sizeof(graph_arr1); i++) */

        pl->catch_tell(graphline + "\n");
        n--;
    }

    pl->catch_tell(
        "-----+------------------------------------------------------------"
      + "------------\n");

    if (week == 2)
    {
        pl->catch_tell(
            " Day |    Sun.      Mon.      Tue.      Wed.      Thu."
          + "      Fri.      Sat.    \n");
        pl->catch_tell(
            "-----+--------------------------------------------------------"
          + "----------------\n\n");
        pl->catch_tell("        Mean weekly average players per hour = "
          + ftoa(census_average(avg_arr, 1))[0..4] + "\n");

        pl->catch_tell(
            "--------------------------------------------------------------"
          + "----------------\n");

        return;
    }

    graphline = "Hour |";

    for (i = 0; i < sizeof(graph_arr1); i++)
    {
        graphword = "" + i;

        if (i < 10)
        {
            graphline += " 0" + graphword;
        }
        else
        {
            graphline += " " + graphword;
        }
    }

    pl->catch_tell(graphline + "\n");
    pl->catch_tell(
        "-----+------------------------------------------------------------"
      + "------------\n\n");
    pl->catch_tell("        Mean daily average players per hour = "
      + ftoa(census_average(avg_arr, 1))[0..4] + "\n");

    if (compare)
    {
        pl->catch_tell("        Comparison average players per hour = "
          + ftoa(census_average(avg_arr2, 1))[0..4] + "\n");
    }

    pl->catch_tell(
        "------------------------------------------------------------------"
      + "------------\n");

} /* census_graph_day */


/*
 * Function name:        month_size
 * Description  :        Given a month and a year, determine its number
 *                       of days.
 * Arguments    :        int month - the month from 1-12,
 *                       int year  - the year the month is in, to
 *                                   account for occasional leap years
 * Returns      :        int - the number of days in that month,
 *                           - 0: failure
 */
public int
month_size(int month, int year)
{
    if (!month || !year)
    {
        return 0;
    }

    switch (month)
    {
        case 1:  /* January   */
        case 3:  /* March     */
        case 5:  /* May       */
        case 8:  /* August    */
        case 10: /* October   */
        case 12: /* December  */
            return 31;
            break;
        case 2:  /* February  */
            return ((year % 4 == 0 && year % 100 != 0)
                  || year % 400 == 0) ? 29 : 28;
            break;
        case 4:  /* April     */
        case 6:  /* June      */
        case 7:  /* July      */
        case 9:  /* September */
        case 11: /* November  */
            return 30;
            break;
        default:
            return 0;
    }

    return 0; /* shouldn't ever happen, but just in case */
} /* month_size */


/*
 * Function name:        census_week
 * Description  :        grab the census data for an entire week, average
 *                       it, and return the results by hour.
 * Arguments    :        string date - the date within the week we want
 *                                     to find
 *                       int hourly  - true if we want the average hour
 *                                     for every day in the week.
 *                                     false if we want the average day
 *                                     for each day in the week
 *                                     (default = false)
 * Returns      :        int array   - the array of average active players
 *                                     per hour, or an empty array if the
 *                                     week did not contain adequate data.
 *                       empty array - There was no valid datafield.
 */
public int *
census_week(string date, int hourly = 0)
{
    int    *date_data      = get_info(CENSUS_FILE, date),
            year           = atoi(parse_date(date)[0]),
            month          = atoi(parse_date(date)[1]),
            day            = atoi(parse_date(date)[2]),
            weekday        = date_data[24],
            i,
            j,
            pre_month      = month - 1,
            post_month     = month + 1,
            monthsize      = month_size(month, year),
            pre_year       = year - 1,
            post_year      = year + 1,
            dig            = day - weekday,
            dec_tag        = 0; /* set if we hit end of year */
    string *week_dates     = allocate(7);
    mixed  *week_data      = allocate(7),
           *hourly_data    = allocate(7),
           *hourly_average = allocate(24),
           which_day,
           which_month    = month,
           which_year     = year;

// TELL_G("census_week: entered function.");
// TELL_G("\tyear = " + year);
// TELL_G("\tmonth = " + month);
// TELL_G("\tday = " + day);
// TELL_G("\tweekday = " + weekday);
// TELL_G("\tmonthsize = " + monthsize);

    if (!sizeof(date_data))
    {
        return ({});
    }

    if (pre_month < 1)
    {
        pre_month = 12;
    }

    if (post_month > 12)
    {
        post_month = 1;
    }

    /* So, lets determine the dates for this week in yyyymmdd format */

    /* First off, we need to check to see if this week spans beyond the
     * beginning of the current month and year.
     */
    if (dig < 0)
    {
// TELL_G("census_week: trying to dig into the former month.");
        /* It does, so we are going to have to dig into the former month
         * to make this work.
         */
        for (i = 0; i < 8; dig++, i++)
        {
            if (dig < 0)
            {
                which_month = pre_month;

                if (month == 1) /* Oops! Gotta dig into last year too! */
                {
                    which_year = pre_year;
                }

                monthsize = month_size(which_month, which_year);
                which_day = monthsize + dig;
            }
            else
            {
                which_day = dig + 1;
                which_month = month;
                which_year = year;
            }

            if (which_day > monthsize)
            {
                which_day = 1;

                if (which_month == 12)
                {
                    which_month = 1;
                }
                else
                {
                    which_month++;
                }
            }

            if (strlen("" + which_day) == 1)
            {
                which_day = "0" + which_day;
            }
            if (strlen("" + which_month) == 1)
            {
                which_month = "0" + which_month;
            }

            if (i < 7)
            {
                week_dates[i] = "" + which_year
                              + "" + which_month
                              + "" + which_day;
            }
            else
            {
                Next_Week = "" + which_year
                          + "" + which_month
                          + "" + which_day;
            }
        }
    }
    /* We also need to check to see if this week spans beyond the end of
     * the current month and year.
     */
    else if ( ((7 - weekday) + day) > monthsize)
//  else if ( (monthsize - (weekday + 1)) < day)
    {
 // TELL_G("census_week: trying to dig into the next month.");
        /* It does, so we are going to have to dig into the next month
         * to make this work.
         */
        for (i = 0; i < 8; i++)
        {
            if (day + i > monthsize)
            {
                which_month = post_month;

 // TELL_G("Checking month: month = " + month);
                if (month == 12)
                {
                    which_year = post_year;
                }

                which_day = (day + i) - monthsize;
            }
            else
            {
                which_day = day + i;
            }

            if (which_day > monthsize)
            {
                which_day = 1;

                if (which_month == 12)
                {
                    which_month = 1;
                }
                else
                {
                    which_month++;
                }
            }

            if (strlen("" + which_day) == 1)
            {
                which_day = "0" + which_day;
            }
            if (strlen("" + which_month) == 1)
            {
                which_month = "0" + which_month;
            }

            if (i < 7)
            {
                week_dates[i] = "" + which_year
                              + "" + which_month
                              + "" + which_day;
            }
            else
            {
                Next_Week = "" + which_year
                          + "" + which_month
                          + "" + which_day;
            }
        }
    }
    /* And if the week all falls within the same month, we do it this
     * much simpler way.
     */
    else
    {
// TELL_G("census_week: It all falls within the same month.");
        for (i = 0; i < 8; i++)
        {
            which_day = ((i + 1) - weekday) + day;

            if (which_day > monthsize)
            {
                which_day = 1;

                if (which_month == 12)
                {
                    which_month = 1;
                    which_year = post_year;
                }
                else
                {
                    which_month = post_month;
                }
            }

// TELL_G("census_week: (" + i + ") which_day = " + which_day + " (before)");
// TELL_G("census_week: strlen() = " + strlen(which_day));
            if (strlen("" + which_day) == 1)
            {
                which_day = "0" + which_day;
            }
            if (strlen("" + which_month) == 1)
            {
                which_month = "0" + which_month;
            }
// TELL_G("census_week: (" + i + ") which_day = " + which_day + " (after)");

            if (i < 7)
            {
                week_dates[i] = "" + which_year
                              + "" + which_month
                              + "" + which_day;
            }
            else
            {
                Next_Week = "" + which_year
                          + "" + which_month
                          + "" + which_day;
            }
        }
    }

// TELL_G("census_week: dumping data: " + Week_Num);
// dump_array(week_dates);

    /* Now, lets see if there is a full data set for this week */
    for (i = 0; i < 7; i++)
    {
// TELL_G("census_week: is there a full data set? i = " + i);
        week_data[i] = get_info(CENSUS_FILE, week_dates[i]);

        if (!sizeof(week_data[i]))
        {
            return ({});
        }
    }

    if (hourly)
    {
// TELL_G("census_week: hourly is true");
        for (i = 0; i < 24; i++) /* gather the 24 hourly index points */
        {
            for (j = 0; j < 7; j++) /* over the 7 days of the week */
            {
                hourly_data[j] = week_data[j][i];
            }

            hourly_average[i] = census_average(hourly_data);
        }

        return hourly_average;
    }

    return ({ census_average(week_data[0][..-2]),
              census_average(week_data[1][..-2]),
              census_average(week_data[2][..-2]),
              census_average(week_data[3][..-2]),
              census_average(week_data[4][..-2]),
              census_average(week_data[5][..-2]),
              census_average(week_data[6][..-2]),
           });
} /* census_week */


/*
 * Function name:        average_over_time
 * Description  :        take the average number of players for a given
 *                       day, hour, or time, and print the results in
 *                       a horizontal graph.
 * Arguments    :        string start - the date to start with
 *                       string end   - the date to end with
 *                       object who   - the player to print stuff to.
 *                       string census - the census file we want to look
 *                                       at (i.e. overall, or some guild?)
 *                       mixed which_weekday - the weekday we want to look
 *                                       at. Default = "all", in which case
 *                                       we simply show every day.
 *                       mixed hour   - the hour we want to see. Default
 *                                      is "all" in which case we do not
 *                                      show a specific hour, but rather
 *                                      the average for a given day.
 */
public void
average_over_time(string start, string end, object who, string census, mixed which_weekday = "all", mixed hour = "all")
{
    int    *date_data      = get_info(census, start),
            year           = atoi(parse_date(start)[0]),
            month          = atoi(parse_date(start)[1]),
            day            = atoi(parse_date(start)[2]),
            weekday        = date_data[24],
            count          = 0,
            i,
            j,
            pre_month      = month - 1,
            post_month     = month + 1,
            monthsize      = month_size(month, year),
            pre_year       = year - 1,
            post_year      = year + 1,
            dig            = day - weekday,
            which_month    = month,
            which_year     = year,
            which_day,
           *count_average  = ({});
    string *week_dates     = allocate(7),
            current_date   = start,
            weekday_txt    = "all days",
            hour_txt       = "daily average";
    mixed  *week_data      = allocate(7),
           *hourly_data    = allocate(7),
           *hourly_average = allocate(24);

    if (!sizeof(date_data))
    {
        who->catch_tell("The start date is invalid.\n");
        return;
    }

    if (pre_month < 1)
    {
        pre_month = 12;
    }

    if (post_month > 12)
    {
        post_month = 1;
    }

    who->catch_tell("----------------------------------------------"
      + "---------------------------------\n");

    while (sizeof(date_data))
    {
        date_data      = get_info(census, current_date);

        if (sizeof(date_data))
        {
            year           = atoi(parse_date(current_date)[0]);
            month          = atoi(parse_date(current_date)[1]);
            day            = atoi(parse_date(current_date)[2]);
            weekday        = date_data[24];
        }
        else
        {
            break;
        }

        if (which_weekday == "all" || atoi(which_weekday) == weekday)
        {
            if (hour == "all")
            {
                count = census_average(exclude_array(date_data, 24, 24));
            }
            else
            {
                count = date_data[atoi(hour)];
            }

            who->catch_tell(current_date + "  " + ("X" * count)
              + "\t\t(" + count + ")\n");
            count_average += ({ count });
        }

        if (current_date == end)
        {
            break;
        }

        if (day == month_size(month, year))
        {
            if (month == 12)
            {
                month = 1;
                year++;
            }
            else
            {
                month++;
            }

            day = 1;
        }
        else
        {
            day++;
        }

        current_date = sprintf("%d%02d%02d", year, month, day);
    }

    switch(which_weekday)
    {
        case "1":
            weekday_txt = "all Sundays";
            break;
        case "2":
            weekday_txt = "all Mondays";
            break;
        case "3":
            weekday_txt = "all Tuesdays";
            break;
        case "4":
            weekday_txt = "all Wednesdays";
            break;
        case "5":
            weekday_txt = "all Thursdays";
            break;
        case "6":
            weekday_txt = "all Fridays";
            break;
        case "7":
            weekday_txt = "all Saturdays";
            break;
        default:
    }

    if (hour != "all")
    {
        hour_txt = "player activity during the "
                 + LANG_ORD2EXT(atoi(hour)) + " hour";
    }
    else
    {
        hour_txt = "daily average of player activity";
    }

    who->catch_tell("----------------------------------------------"
      + "---------------------------------\n");
    who->catch_tell("Displayed was the " + hour_txt + " on "
      + weekday_txt + " beginning on " + start + " and ending on "
      + end + ".\n\n");
    who->catch_tell(sprintf("%| 80s",
        "Average players per hour in given parameters = "
      + ftoa(census_average(count_average, 1))[0..4]) + "\n");
    who->catch_tell("----------------------------------------------"
      + "---------------------------------\n");
} /* average_over_time */


/*
 * Function name:        census_year
 * Description  :        create an array of the average number of players
 *                       per hour, each week, for an entire year.
 * Arguments    :        string date - the date within the week we want
 *                                     to find
 *                       int hourly  - true if we want the average hour
 *                                     for every day in the week.
 *                                     false if we want the average day
 *                                     for each day in the week
 *                                     (default = false)
 * Returns      :        int array   - the array of average active players
 *                                     per hour, or an empty array if the
 *                                     week did not contain adequate data.
 *                       empty array - There was no valid datafield.
 */
public mixed *
census_year(string date)
{
    int    *date_data      = get_info(CENSUS_FILE, date),
            month,
            i;
    mixed  *year_data = allocate(52);

    Next_Week = date;

    for (i = 0; i < 52; i++)
    {
        //TELL_G("Next_Week = " + Next_Week);
        Week_Num = i + 1;
        month = atoi(parse_date(Next_Week)[1]);
        year_data[i] = ({ census_average(census_week(Next_Week), 1),
                          month });
    }

    return year_data;
} /* census_year */


/*
 * Function name:        place_float
 * Description  :        Take a float, determine if it fits within the
 *                       range of a given integer, and return a value
 *                       to indicate where above, below, or within the
 *                       range it fits.
 * Arguments    :        float f - the float to check
 *                       int i - the integer representing the range
 * Returns      :        int:    0 - the float is below the int range
 *                               1 - the float is within the int, but
 *                                   below the x.5 range.
 *                               2 - the float is within the int, but
 *                                   above the x.5 range.
 *                               3 - the float is above the int range
 */
public int
place_float(float f, int i)
{
    if (ftoi(f) > i)
    {
        return 3;
    }

    if (f < itof(i))
    {
        return 0;
    }

    if (f >= (itof(i) + 0.5))
    {
        return 2;
    }

    return 1;
} /* place_float */


/*
 * Function name:        census_graph_year
 * Description  :        This function presents the mean scores for
 *                       the number of active players per hour over a
 *                       full 52 week period. Each data line on the
 *                       graph represents the mean score for a week.
 * Arguments    :        object pl       - the player who will receive a
 *                                         printout of the data
 *                       mixed graph_arr - the array of data containing
 *                                         the graph for the year:
 *                                          [0]: mean score (float)
 *                                          [1]: month of origin (int)
 *                       int date       = array identifying the date for
 *                                        graph_arr:
 *                                          [0]: year,
 *                                          [1]: month,
 *                                          [2]: day
 */
public void
census_graph_year(object pl, mixed *graph_arr, int *date)
{
    string  day2 = " ",
            graphtxt,
            graphword = " ",
            graphline = "",
            frontspaces = "",
            backspaces = "",
            graphnum,
            graphplot,
           *months,
            margin_text = "AVG PER HOUR EACH WEEK",
           *graph_lines = draw_year_lines(graph_arr);
    int     i,
            high_n = 23,
            low_n = 8,
            n,
            k = 1,
            last_month = graph_arr[0][1],
            margin_n = strlen(margin_text),
           *avg_arr = allocate(sizeof(graph_arr)),
            graph_width = strlen(graph_lines[0]) - 2;

    months = ({ "Jan.",
                "Feb.",
                "Mar.",
                "Apr.",
                "May ",
                "Jun.",
                "Jul.",
                "Aug.",
                "Sep.",
                "Oct.",
                "Nov.",
                "Dec." });

    /* First, lets determine the highest point of the graph */
    for (i = 0; i < sizeof(graph_arr); i++)
    {
        if (ftoi(graph_arr[i][0]) > high_n)
        {
            high_n = ftoi(graph_arr[i][0]);
        }
    }

    /* Now, lets determine the lowest point of the graph */
    for (i = 0; i < sizeof(graph_arr); i++)
    {
        if (ftoi(graph_arr[i][0]) < low_n)
        {
            low_n = ftoi(graph_arr[i][0]);
        }
    }

    /* The range will be equal to the distance between the high and
     * low ranges * 2, so that we can plot by each .5 score.
     */
    n = (high_n - low_n) * 2;

    if (n < margin_n)
    {
        n = margin_n; /* Just so we can draw proper labels on the graph */
    }

    /* Okay! Lets draw the graph! */
    pl->catch_tell(graph_lines[2] + "\n");
    pl->catch_tell("|"  + (" " * graph_width) + "|\n");
    pl->catch_tell("|" + sprintf("%| " + graph_width + "s",
        "Average player activity by week for entire year, beginning "
      + display_date(date)) + "|\n");
    pl->catch_tell("|"  + (" " * graph_width) + "|\n");

    pl->catch_tell(graph_lines[0] + "\n");

    while (n)
    {
        graphplot = " ";

        if (n <= margin_n)
        {
            graphword = margin_text[(margin_n)-n..(margin_n)-n];
        }

        if (k)
        {
            graphnum = (high_n - 1) + ".5";
            high_n--;
        }
        else
        {
            graphnum = high_n + ".0";
        }

        k = !k;

        graphline = "| " + graphword + " "
                  + (" " * (5 - strlen("" + graphnum)))
                  + graphnum + " |";

        for (i = 0; i < sizeof(graph_arr); i++)
        {
            if (graph_arr[i][1] != last_month && (i > 0))
            {
                frontspaces = "|";
            }

            graphline += frontspaces;
            avg_arr[i] = ftoi(graph_arr[i][0]);

            if (ftoi(graph_arr[i][0]) < (low_n + (n / 2)))
            {
                if (!k)
                {
                    if (place_float(graph_arr[i][0], high_n) == 2)
                    {
                        graphline += "X";
                    }
                    else
                    {
                        graphline += " ";
                    }
                }
                else
                {
                    graphline += " ";
                }
            }
            else
            {
                graphline += "X";
            }

            last_month = graph_arr[i][1];
            frontspaces = "";
        } /* for (i = 0; i < sizeof(graph_arr); i++) */

        pl->catch_tell(graphline + "|\n");
        n--;
    }

    pl->catch_tell(graph_lines[0] + "\n");
    pl->catch_tell(graph_lines[1] + "\n");
    pl->catch_tell(graph_lines[0] + "\n");
    pl->catch_tell("|"  + (" " * graph_width) + "|\n");
    pl->catch_tell("|" + sprintf("%| " + graph_width + "s",
        "Mean yearly average players per hour = "
      + ftoa(census_average(avg_arr, 1))[0..4]) + "|\n");
    pl->catch_tell("|"  + (" " * graph_width) + "|\n");
    pl->catch_tell(graph_lines[2] + "\n");

} /* census_graph_year */


/*
 * Function name:        draw_year_lines
 * Description  :        Draw out various year lines based on the
 *                       info for the year. The idea is to align the
 *                       separation marks for the months ( "|" ) with
 *                       Various things so the graph looks correct.
 * Arguments    :        mixed graph_arr - the array of data containing
 *                                         the graph for the year:
 *                                          [0]: mean score (float)
 *                                          [1]: month of origin (int)
 * Returns      :        string array: [0]: line at top of graph
 *                                     [1]: line at bottom of graph
 *                                     [2]: month line
 *                                     [3]: line below monthline
 */
public string *
draw_year_lines(mixed graph_arr)
{
    string    *year_line_arr = allocate(3),
              *months,
               month_line = "|";
    int        current_month = graph_arr[0][1],
               i,
               k,
               tag,
               month_space = 0,
              *month_spaces = ({}),
              *month_order = ({}),
               month_len = 0,
               wait = 1;

    months = ({ "Jan",
                "Feb",
                "Mar",
                "Apr",
                "May",
                "Jun",
                "Jul",
                "Aug",
                "Sep",
                "Oct",
                "Nov",
                "Dec" });

    /* First, we will draw the divider line that will appear in multiple
     * places on the year graph. The goal is to have "+" characters line
     * up with the "|" divider lines that separate one month from the next
     * on the main graph. Before doing anything else, we build the margin.
     */
    year_line_arr[0] = "+---------+";

    /* Now, we run a foreach taking each week of the year, determining the
     * month (numerically) that the week fell in during the year. We keep
     * track of what the most recently seen month was, and if the month
     * changes, we know we need to do two things: 1. we draw a "+" instead
     * of simply a "-" in the divider line. 2. we count how many characters
     * width will be available for the month line later on.
     */
    foreach (mixed week: graph_arr)
    {
        if (week[1] == current_month)
        {
            year_line_arr[i] += "-";

            if (!month_space && wait)
            {
                wait = 0;
            }
            else
            {
                month_space++;
            }
        }
        else
        {
            year_line_arr[i] += "+-";
            month_spaces += ({ month_space + 1 });
            month_order += ({ current_month });
            month_space = 0;
        }

        current_month = week[1];
    }

    /* Lastly, we tag a little "+" on the end to finish the line. */
    year_line_arr[0] += "+";

    /* Now, it is time to use the array of character width indicators to
     * know how to properly draw the month names below each column, which
     * is the next task. Again, we start by building the margin.
     */
    year_line_arr[1] = "|  Month  |";

    for (i = 0; i < sizeof(month_spaces); i++)
    {
        if (month_spaces[i] < 4)
        {
            year_line_arr[1] += (" " * month_spaces[i]);
        }
        else
        {
            if (!i)
            {
                if (month_spaces[i] > 3)
                {
                    month_line = "";
                }
            }

            year_line_arr[1] += month_line + months[month_order[i] - 1]
              + (" " * (month_spaces[i] - strlen(months[month_order[i] - 1])));

            month_line = "|";
        }
    }

    tag = (strlen(year_line_arr[0]) - 2) - strlen(year_line_arr[1]);

    year_line_arr[1] += "|";

    if (tag)
    {
        year_line_arr[1] += (" " * tag) + "|";
    }

    year_line_arr[2] = "+" + ("-" * (strlen(year_line_arr[0]) - 2)) + "+";

    return year_line_arr;
} /* draw_year_lines */


/*
 * Function name:        census_chart
 * Description  :        Print out a chart with tables displaying the
 *                       comparison of data on player activity between
 *                       two time periods.
 * Arguments    :        object who     - the player to see the chart
 *                       string a_start - start date for period A
 *                       string a_end   - end date for period A
 *                       string b_start - start date for period B
 *                       string b_end   - end date for period B
 */
public void
census_chart(object who, string a_start, string a_end, string b_start, string b_end)
{
    float  *a  = chart_time_period(a_start, a_end, who);
    float  *b  = chart_time_period(b_start, b_end, who);
    string *c  = allocate(33);
    string *atxt = allocate(33);
    string *btxt = allocate(33);
    string  ctxt;
    string  ax = ftoa(a[31])[0..4];
    string  bx = ftoa(b[31])[0..4];
    string  cx = ftoa(((b[31] - a[31]) / a[31]) * 100.0)[0..4];
    string  cpre;
    string  cpost;
    int     i;
    int     spaces;

    if (((b[31] - a[31]) / b[31]) > 0.0)
    {
        cx = "+" + cx;
    }

    for (i = 0; i < (sizeof(a) - 1); i++)
    {
        ctxt = ftoa((b[i] - a[i]) / a[i] * 100.0);

        if (ctxt[0..0] != "-")
        {
            spaces = 2 - strlen(explode(ctxt, ".")[0]);
            ctxt = (" " * spaces) + "+" + ctxt;
        }
        else
        {
            spaces = 3 - strlen(explode(ctxt, ".")[0]);
            ctxt = (" " * spaces) + ctxt;
        }

        cpre = explode(ctxt, ".")[0];
        cpost = explode(ctxt, ".")[1][0..1];
        ctxt = implode( ({ cpre, cpost }), ".");
        c[i] = sprintf("% 10s", ctxt[0..7] + " %");

        ctxt = ftoa(a[i]);
        spaces = 2 - strlen(explode(ctxt, ".")[0]);
        atxt[i] = sprintf(" %- 6s", ((spaces * " ") + ctxt)[0..4]);

        ctxt = ftoa(b[i]);
        spaces = 2 - strlen(explode(ctxt, ".")[0]);
        btxt[i] = sprintf(" %- 6s", ((spaces * " ") + ctxt)[0..4]);
    }

    /* All data secured! Let's draw the chart.
     *
     * Note: Normally, I feel it is important to keep all code readable
     * without wrapping at screen-width 80. However, for the purposes of
     * laying out this graph, which takes all 80 characters of that
     * default screen width, I do not. The following code is best viewed
     * with screen width set to 90. (Yuck! Apologies!)
     */
    who->catch_tell(
        "+----------------------------------------------------------------------------+\n"
      + "|             Comparing player activity over two time periods:               |\n"
      + "|                      A: " + display_date(parse_date(a_start))
      + " - " + display_date(parse_date(a_end)) + "                          |\n"
      + "|                      B: " + display_date(parse_date(b_start))
      + " - " + display_date(parse_date(b_end)) + "                          |\n"
      + "+-------+-------+-------+----------+--+-----------+-------+-------+----------+\n"
      + "| Hour  |   A   |   B   | % change |  | Weekday   |   A   |   B   | % change |\n"
      + "+-------+-------+-------+----------+  +-----------+-------+-------+----------+\n");

    who->catch_tell(
        "| 00.00 |" + atxt[0] + "|" + btxt[0] + "|" + c[0]
      + "|  | Sunday    |" + atxt[24] + "|" + btxt[24] + "|" + c[24] + "|\n");
    who->catch_tell(
        "| 01.00 |" + atxt[1] + "|" + btxt[1] + "|" + c[1]
      + "|  | Monday    |" + atxt[25] + "|" + btxt[25] + "|" + c[25] + "|\n");
    who->catch_tell(
        "| 02.00 |" + atxt[2] + "|" + btxt[2] + "|" + c[2]
      + "|  | Tuesday   |" + atxt[26] + "|" + btxt[26] + "|" + c[26] + "|\n");
    who->catch_tell(
        "| 03.00 |" + atxt[3] + "|" + btxt[3] + "|" + c[3]
      + "|  | Wednesday |" + atxt[27] + "|" + btxt[27] + "|" + c[27] + "|\n");
    who->catch_tell(
        "| 04.00 |" + atxt[4] + "|" + btxt[4] + "|" + c[4]
      + "|  | Thursday  |" + atxt[28] + "|" + btxt[28] + "|" + c[28] + "|\n");
    who->catch_tell(
        "| 05.00 |" + atxt[5] + "|" + btxt[5] + "|" + c[5]
      + "|  | Friday    |" + atxt[29] + "|" + btxt[29] + "|" + c[29] + "|\n");
    who->catch_tell(
        "| 06.00 |" + atxt[6] + "|" + btxt[6] + "|" + c[6]
      + "|  | Saturday  |" + atxt[30] + "|" + btxt[30] + "|" + c[30] + "|\n");
    who->catch_tell(
        "| 07.00 |" + atxt[7] + "|" + btxt[7] + "|" + c[7]
      + "|  +-----------+-------+-------+----------+\n");
    who->catch_tell(
        "| 08.00 |" + atxt[8] + "|" + btxt[8] + "|" + c[8]
      + "|                                         |\n");
    who->catch_tell(
        "| 09.00 |" + atxt[9] + "|" + btxt[9] + "|" + c[9]
      + "|                                         |\n");
    who->catch_tell(
        "| 10.00 |" + atxt[10] + "|" + btxt[10] + "|" + c[10]
      + "|  +--------------------------------------+\n");
    who->catch_tell(
        "| 11.00 |" + atxt[11] + "|" + btxt[11] + "|" + c[11]
      + "|  |       - - - Field  Sizes - - -       |\n");
    who->catch_tell(
        "| 12.00 |" + atxt[12] + "|" + btxt[12] + "|" + c[12]
      + "|  | Number of days in Period A: " + sprintf("%7s", ftoa(a[32])) + "  |\n");
    who->catch_tell(
        "| 13.00 |" + atxt[13] + "|" + btxt[13] + "|" + c[13]
      + "|  | Number of days in Period B: " + sprintf("%7s", ftoa(b[32])) + "  |\n");
    who->catch_tell(
        "| 14.00 |" + atxt[14] + "|" + btxt[14] + "|" + c[14]
      + "|  +--------------------------------------+\n");
    who->catch_tell(
        "| 15.00 |" + atxt[15] + "|" + btxt[15] + "|" + c[15]
      + "|                                         |\n");
    who->catch_tell(
        "| 16.00 |" + atxt[16] + "|" + btxt[16] + "|" + c[16]
      + "|                                         |\n");
    who->catch_tell(
        "| 17.00 |" + atxt[17] + "|" + btxt[17] + "|" + c[17]
      + "|  +--------------------------------------+\n");
    who->catch_tell(
        "| 18.00 |" + atxt[18] + "|" + btxt[18] + "|" + c[18]
      + "|  |           Overall Summary            |\n");
    who->catch_tell(
        "| 19.00 |" + atxt[19] + "|" + btxt[19] + "|" + c[19]
      + "|  +--------------------------------------+\n");
    who->catch_tell(
        "| 20.00 |" + atxt[20] + "|" + btxt[20] + "|" + c[20]
      + "|  | Overall average for Period A: " + sprintf("%6s", ax) + " |\n");
    who->catch_tell(
        "| 21.00 |" + atxt[21] + "|" + btxt[21] + "|" + c[21]
      + "|  | Overall average for Period B: " + sprintf("%6s", bx) + " |\n");
    who->catch_tell(
        "| 22.00 |" + atxt[22] + "|" + btxt[22] + "|" + c[22]
      + "|  |                                      |\n");
    who->catch_tell(
        "| 23.00 |" + atxt[23] + "|" + btxt[23] + "|" + c[23]
      + "|  | Overall increase/decrease:" + sprintf("%|11s", cx + " %") + "|\n");
    who->catch_tell(
        "+-------+-------+-------+----------+--+--------------------------------------+\n\n");
}


/*
 * Function name:        chart_time_period
 * Description  :        create an array of values representing the daily
 *                       tally of players per hour for each day falling
 *                       between the specified start and end date. The tally
 *                       can be limited to only certain hours and/or certain
 *                       days of the week.
 * Arguments    :        string start - the date to start with
 *                       string end   - the date to end with
 *                       object who   - the player to print stuff to.
 * Returns     :         int array    - the array contains arrays that
 *                                      will be used to create the chart
 *                                      for this time period. The first
 *                                      24 arrays are the player tally
 *                                      for the given hour of the day on
 *                                      each day of the time period. The
 *                                      next seven elements are the
 *                                      daily averages for each individual
 *                                      weekday (all Mondays, etc) in the
 *                                      time period. The final index point
 *                                      is not an array, but rather a
 *                                      float value representing the mean
 *                                      score for the average hour over
 *                                      the entire time period.
 */
public float *
chart_time_period(string start, string end, object who)
{
    int    *date_data      = get_info(CENSUS_FILE, start),
            year           = atoi(parse_date(start)[0]),
            month          = atoi(parse_date(start)[1]),
            day            = atoi(parse_date(start)[2]),
            weekday        = date_data[24],
            count          = 0,
            i,
            pre_month      = month - 1,
            post_month     = month + 1,
            monthsize      = month_size(month, year),
            pre_year       = year - 1,
            post_year      = year + 1,
            dig            = day - weekday,
            which_month    = month,
            which_year     = year,
            which_day;
    string *week_dates     = allocate(7),
            current_date   = start,
            weekday_txt    = "all days",
            hour_txt       = "daily average";
    mixed  *week_data      = allocate(7),
           *hourly_data    = allocate(7),
           *hourly_average = allocate(24),
           *day_arr        = ({}),
           *hour_0         = ({}),
           *hour_1         = ({}),
           *hour_2         = ({}),
           *hour_3         = ({}),
           *hour_4         = ({}),
           *hour_5         = ({}),
           *hour_6         = ({}),
           *hour_7         = ({}),
           *hour_8         = ({}),
           *hour_9         = ({}),
           *hour_10         = ({}),
           *hour_11         = ({}),
           *hour_12         = ({}),
           *hour_13         = ({}),
           *hour_14         = ({}),
           *hour_15         = ({}),
           *hour_16         = ({}),
           *hour_17         = ({}),
           *hour_18         = ({}),
           *hour_19         = ({}),
           *hour_20         = ({}),
           *hour_21         = ({}),
           *hour_22         = ({}),
           *hour_23         = ({}),
           *day_1           = ({}),
           *day_2           = ({}),
           *day_3           = ({}),
           *day_4           = ({}),
           *day_5           = ({}),
           *day_6           = ({}),
           *day_7           = ({});

    if (!sizeof(date_data))
    {
        who->catch_tell("The start date is invalid.\n");
        return 0;
    }

    if (pre_month < 1)
    {
        pre_month = 12;
    }

    if (post_month > 12)
    {
        post_month = 1;
    }

    while (sizeof(date_data))
    {
        date_data      = get_info(CENSUS_FILE, current_date);

        if (sizeof(date_data))
        {
            year           = atoi(parse_date(current_date)[0]);
            month          = atoi(parse_date(current_date)[1]);
            day            = atoi(parse_date(current_date)[2]);
            weekday        = date_data[24];
        }
        else
        {
            break;
        }

        hour_0 += ({ date_data[0] });
        hour_1 += ({ date_data[1] });
        hour_2 += ({ date_data[2] });
        hour_3 += ({ date_data[3] });
        hour_4 += ({ date_data[4] });
        hour_5 += ({ date_data[5] });
        hour_6 += ({ date_data[6] });
        hour_7 += ({ date_data[7] });
        hour_8 += ({ date_data[8] });
        hour_9 += ({ date_data[9] });
        hour_10 += ({ date_data[10] });
        hour_11 += ({ date_data[11] });
        hour_12 += ({ date_data[12] });
        hour_13 += ({ date_data[13] });
        hour_14 += ({ date_data[14] });
        hour_15 += ({ date_data[15] });
        hour_16 += ({ date_data[16] });
        hour_17 += ({ date_data[17] });
        hour_18 += ({ date_data[18] });
        hour_19 += ({ date_data[19] });
        hour_20 += ({ date_data[20] });
        hour_21 += ({ date_data[21] });
        hour_22 += ({ date_data[22] });
        hour_23 += ({ date_data[23] });

        switch (date_data[24])
        {
            case 1:
                day_1 += ({ census_average(date_data, 1) });
                break;
            case 2:
                day_2 += ({ census_average(date_data, 1) });
                break;
            case 3:
                day_3 += ({ census_average(date_data, 1) });
                break;
            case 4:
                day_4 += ({ census_average(date_data, 1) });
                break;
            case 5:
                day_5 += ({ census_average(date_data, 1) });
                break;
            case 6:
                day_6 += ({ census_average(date_data, 1) });
                break;
            case 7:
                day_7 += ({ census_average(date_data, 1) });
                break;
        }

        day_arr += ({ census_average(date_data, 1) });

        if (current_date == end)
        {
            break;
        }

        if (day == month_size(month, year))
        {
            if (month == 12)
            {
                month = 1;
                year++;
            }
            else
            {
                month++;
            }

            day = 1;
        }
        else
        {
            day++;
        }

        current_date = sprintf("%d%02d%02d", year, month, day);
    }

    return ({ census_average(hour_0, 1),
              census_average(hour_1, 1),
              census_average(hour_2, 1),
              census_average(hour_3, 1),
              census_average(hour_4, 1),
              census_average(hour_5, 1),
              census_average(hour_6, 1),
              census_average(hour_7, 1),
              census_average(hour_8, 1),
              census_average(hour_9, 1),
              census_average(hour_10, 1),
              census_average(hour_11, 1),
              census_average(hour_12, 1),
              census_average(hour_13, 1),
              census_average(hour_14, 1),
              census_average(hour_15, 1),
              census_average(hour_16, 1),
              census_average(hour_17, 1),
              census_average(hour_18, 1),
              census_average(hour_19, 1),
              census_average(hour_20, 1),
              census_average(hour_21, 1),
              census_average(hour_22, 1),
              census_average(hour_23, 1),
              census_average(day_1, 1),
              census_average(day_2, 1),
              census_average(day_3, 1),
              census_average(day_4, 1),
              census_average(day_5, 1),
              census_average(day_6, 1),
              census_average(day_7, 1),
              census_average(day_arr, 1),
              itof(sizeof(day_arr)) });
} /* chart_time_period */


/* Function name:        query_open_guilds
 * Description  :        Generates an array containing the short name
 *                       of all open guilds in the game.
 * Returns      :        string array - the names of open guilds
 */
public string *
query_open_guilds()
{
    return filter(SECURITY->query_guilds(), guild_is_open);
} /* query_open_guilds */



/*
 * Function name:        guild_is_open
 * Description  :        filter check to see if the guild is currently
 *                       open.
 * Arguments    :        string name - the name of the guild
 * Returns      :        1 - its open, 0 - its closed
 */
public int
guild_is_open(string name)
{
    return ((SECURITY->query_guild_phase(name) == "open") ? 1 : 0);
} /* guild_is_open */


/*
 * Function name:        check_guild_membership
 * Description  :        See if a player is in a given guild.
 * Arguments    :        object who - the player object
 *                       string gname - the short name of the guild
 * Returns      :        int 1 - if they are a member,
 *                           0 - if they are not a member
 */
public int
check_guild_membership(object who, string gname)
{
    string  this_guild = SECURITY->query_guild_long_name(gname),
            player_guild;

    if (who->query_guild_name_occ()   != this_guild &&
        who->query_guild_name_lay()   != this_guild &&
        who->query_guild_name_race()  != this_guild &&
        who->query_guild_name_craft() != this_guild)
    {
        return 0;
    }

    if (!this_guild) /* It isn't a guild */
    {
        return 0;
    }

    return 1;
} /* check_guild_membership */
