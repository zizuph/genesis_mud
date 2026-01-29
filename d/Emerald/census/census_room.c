/*
 *  /d/Emerald/census/census_room.c
 *
 *  This room is the control station and user-interface for the census
 *  code I am creating to track trends in the playerbase population. I
 *  am putting it in Emerald at present to utilize the domain's ability
 *  to load this file and get it going at reboot. I'm sure there is a
 *  better way to do this, but we'll go with this for now.
 *
 *  Created October 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";

#include <time.h>

/* Definitions */
#define            CENSUS      "/d/Emerald/census/census_master"
#define            CENSUS_FILE "census"
#define  TELL_G(x)     find_living("gorboth")->catch_tell(x + "\n")

/* Global Variables */
public string      Date1 = "";
public string      Date2 = "";
public int         Week = 0; /* Toggle value. Are we graphing weeks? */
public int         Hour = 1; /* Toggle value. Are we graphing by hour? */
public mixed       Which_Hour = "all";
public mixed       Weekday = "all";


/* Prototypes */
public void        create_room();
public string      long_desc();
public void        init();
public int         do_tally(string arg);
public int         do_display(string arg);
public int         dateset(string arg);

public string      query_date1() { return Date1; }
public string      query_date2() { return Date2; }

/*
 * Function name:        create_room
 * Description  :        constructor - set up the room
 */
public void
create_room()
{
    set_short("the control room for the Genesis Census");
    set_long(long_desc);
} /* create_room */


/*
 * Function name:        long_desc
 * Description  :        provide a variable long-description
 * Returns      :        string - the description text
 */
public string
long_desc()
{
    string  long_txt,
            date1 = "(unassigned)",
            date2 = "(unassigned)";

    if (strlen(Date1))
    {
        date1 = Date1;
    }

    if (strlen(Date2))
    {
        date2 = Date2;
    }

    long_txt = "This is the control room for the Genesis Census.\n\n"
      + "   Settings:\tPrimary Date: " + date1 + "\n"
      + "\t\tComparison Date: " + date2 + "\n\n"
      + "\t\tCurrently displaying hourly averages by: "
      + (Week ? "Week" : "Single Day") + "\n"
      + "\t\tCurrently displaying Averages by: "
      + (Hour ? "Hour" : "Day of the Week") + "\n\n"
      + "\t\tWhich_Hour = " + Which_Hour + "\n"
      + "\t\tWeekday = " + Weekday + "\n\n"
      + "   Commands:\t<dateset yyyymmdd> - set dates to analyze\n"
      + "\t\t<dateset week>  - toggle to display week or single day\n"
      + "\t\t<dateset type>  - toggle to display weeks by hour or day\n\n"
      + "\t\t<display graph> - display graph for the primary date\n"
      + "\t\t<display graphs>- display primary and comparison graphs\n\n";



    return long_txt;
} /* long_desc */


/*
 * Function name:        init
 * Description  :        add some actions for players in the room
 */
public void
init()
{
    ::init();

    add_action(do_tally, "tally");
    add_action(do_display, "display");
    add_action(dateset, "dateset");
} /* init */


/*
 * Function name:        do_tally
 * Description  :        Perform all sorts of analyses on the data of
 *                       playerbase frequency.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_tally(string arg)
{
    string  *dates,
             date;
    int      i;

    if (!strlen(arg))
    {
        notify_fail("Perform what sort of tally? Look at the room for"
          + " instructions.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "'date' %w", date))
    {
        dates = CENSUS->parse_date(date);

        write("Trying to parse that date:\n\n"
          + "\tYear = " + dates[0] + "\n"
          + "\tMonth = " + dates[1] + "\n"
          + "\tDat = " + dates[2] + "\n"
          + "\tDay of the week = " + dates[3] + "\n\n");
        return 1;
    }

    if (parse_command(arg, ({}),
        "'average' %w", date))
    {
        dates = CENSUS->get_info(CENSUS_FILE, date);

        if (!sizeof(dates))
        {
            notify_fail("Either that is not a valid date, or there has"
              + " been no census data collected for that date.\n");
            return 0;
        }

        write("Averages for " + date + "\n\n"
          + "\tMean:\t" + CENSUS->census_average(dates) + "\n"
          + "\t Max:\t" + CENSUS->census_max(dates[..-2]) + "\n\n");
        return 1;
    }
        
    switch (arg)
    {
        case "average":
            write("Usage: <tally average yyyymmdd>\n");
            break;
        case "hour":
            write("The hour is: " + CENSUS->query_hour() + "\n");
            break;
        case "players":
            write("The currently number of players is: "
              + CENSUS->tally_players() + "\n");
            break;
        case "day":
            write("The current day of the month is: "
              + TIME2FORMAT(time(), "d") + "\n"
              + "The current day of the week is: "
              + ctime(time())[0..2] + "\n");
            break;
        case "test":
            CENSUS->perform_census();
            write("Done!\n");
            break;
        case "dates":
            dates = CENSUS->query_census_dates();

            for (i = 0; i < sizeof(dates); i++)
            {
                write(dates[i] + "\n");
            }
            break;
        default:
            notify_fail("That is not a valid command. Check the room"
              + " description for usage.\n");
            return 0;
            break;
    }

    return 1;
} /* do_tally */


/*
 * Function name:        do_display
 * Description  :        print out graphical displays of the data, usually
 *                       via graphs
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
do_display(string arg)
{
    string  date,
            date2;
    int    *census_arr,
           *census_arr2,
            display_week = Week;

    if (!strlen(arg))
    {
        notify_fail("Display what?\n");
        return 0;
    }

    if (arg == "graph")
    {
        if (!strlen(Date1))
        {
            notify_fail("The primary date has not yet been set. Use"
              + " <dateset 1 yyyymmdd> to set it.\n");
            return 0;
        }

        if (Week)
        {
            census_arr = CENSUS->census_week(Date1, (Hour ? 1 : 0) );

            if (!sizeof(census_arr))
            {
                notify_fail("There was insufficient data to display.\n");
                return 0;
            }

            if (!Hour)
            {
                display_week++;
            }
        }
        else
        {
            census_arr = CENSUS->get_info(CENSUS_FILE, Date1);
        }

        if (!sizeof(census_arr))
        {
            notify_fail("Either that is not a valid date, or there has"
              + " been no census data collected for that date.\n");
            return 0;
        }

        CENSUS->census_graph_day(this_player(),
            ((display_week == 2) ? census_arr : census_arr[..-2]),
            CENSUS->parse_date(Date1), ({}), display_week);

        return 1;
    }

    if (arg == "graphs")
    {
        if (!strlen(Date2))
        {
            notify_fail("The comparison date has not yet been set. Use"
              + " <dateset 2 yyyymmdd> to set it.\n");
            return 0;
        }

        census_arr = CENSUS->get_info(CENSUS_FILE, Date1);

        if (!sizeof(census_arr))
        {
            notify_fail("Either the primary date is not a valid date,"
              + " or there has been no census data collected for that"
              + " date.\n");
            return 0;
        }

        census_arr2 = CENSUS->get_info(CENSUS_FILE, Date2);

        if (!sizeof(census_arr2))
        {
            notify_fail("Either the comparison date is not a valid date,"
              + " or there has been no census data collected for that"
              + " date.\n");
            return 0;
        }

        CENSUS->census_graph_day(this_player(), census_arr[..-2],
            CENSUS->parse_date(Date1), CENSUS->parse_date(Date2), 0,
            census_arr2[..-2]);
        return 1;
    }

    if (arg == "timegraph")
    {
        CENSUS->average_over_time(Date1, Date2, this_player(),
                                  Weekday, Which_Hour);
        return 1;
    }

    notify_fail("You may either <display graph> or <display graphs>\n");
    return 0;
} /* do_display */


/*
 * Function name:        dateset
 * Description  :        Allow a user to set the dates they wish to
 *                       display information to.
 * Arguments    :        What was typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
dateset(string arg)
{
    int    *dates;
    string  num,
            date;

    notify_fail("Usage: <dateset 1 yyyymmdd> for a primary date.\n"
              + "       <dateset 2 yyyymmdd> for a comparison date.\n"
              + "       <dateset clear> to clear the dates.\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "%w %w", num, date))
    {
        if (arg == "clear")
        {
            Date1 = "";
            Date2 = "";
            Week = 0;

            write("Dates cleared.\n");
            return 1;
        }

        if (arg == "week")
        {
            Week = !Week;
            write("The display will now graph an average "
              + (Week ? "week" : "day") + ".\n");
            return 1;
        }

        if (arg == "type")
        {
            Hour = !Hour;
            write("The average will now be displayed by "
              + (Hour ? "hour" : "day") + ".\n");
            return 1;
        }

        write("Failed at parse check.\n");
        return 0;
    }

    switch (lower_case(num))
    {
        case "weekday":
            write("The weekday has been set to: " + date + "\n");
            Weekday = date;
            return 1;
            break;
        case "hour":
            write("The hour to check has been set to: " + date + "\n");
            Which_Hour = date;
            return 1;
            break;
        default:
            break;
    }

    dates = CENSUS->get_info(CENSUS_FILE, date);

    if (!sizeof(dates))
    {
        notify_fail("Either that is not a valid date, or there has"
          + " been no census data collected for that date.\n");
        return 0;
    }

    switch (lower_case(num))
    {
        case "1":
            Date1 = date;
            write("Primary date set to: " + date + "\n");
            break;
        case "2":
            Date2 = date;
            write("Comparison date set to: " + date + "\n");
            break;
        default:
            write("Failed at switch.\n");
            return 0;
    }

    return 1;
} /* dateset */