/*
 * /w/gwyneth/drug/overdose.c
 *
 * Invisible overdose object cloned onto the player if
 * overdosing is an option. Overdosing effects should be
 * implemented in the responsible drug, as this object
 * only keeps track of various values and calculates them
 * upon demand.
 *
 * Coded by Gwyneth, 20 August 2000
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public int calculate_overdose();

int gDose,
    gLimit,
    gRate,
    gTime,
    gInterval;

/*
 * Function name: set_overdose
 * Description:   Sets up the necessary variables.
 * Arguments:     int dose - the strength of the drug being consumed,
 *                int limit - the level at which overdose occurs,
 *                int rate - how much the strength will be decreased by,
 *                int interval - how often the strength will be decreased,
 *                string name - the name to give this overdose object
 *                       and associated with the drug name
 */
public void
set_overdose(int dose, int limit, int rate, int interval, string name)
{
    calculate_overdose();
    gDose = dose;
    gLimit = limit;
    gRate = rate;
    gInterval = interval;
    gTime = time();
    set_name(name);
}

/*
 * Function name: set_overdose_dose
 * Description:   adds to the total strength.
 * Arguments:     int dose - the dose to add
 */
public void
set_overdose_dose(int dose)
{
    calculate_overdose();
    gDose += dose;
}

/*
 * Function name: reset_overdose
 * Description:   Reset the variables when values fall below 0.
 */
public void
reset_overdose()
{
    gDose = 0;
    gTime = time();
}

/*
 * Function name: calculate_overdose
 * Description:   Calculates the strength of the drug in the
 *                player's body given the original time, the
 *                current time, the original strength, the
 *                rate of decay, and the interval. Adjusts
 *                the time and strength accordingly. Should
 *                be called before any variables are changed
 *                in order to update everything.
 * Returns:       The new strength
 */
public int
calculate_overdose()
{
    int t = time(), result, diff = 0;

    result = t - gTime;

    /* Prevent division by zero. Sets the interval to 1 minute */
    if (!gInterval)
    {
        gInterval = 60;
    }

    if (result > gInterval)
    {
        diff = result % gInterval;
    }
    else
    {
        return gDose;
    }

    result = result / gInterval;
    result = gRate * result;
    result = gDose - result;
    gDose  = result;
    gTime = t - diff;
    return gDose;
}

/*
 * Function name: query_time_left
 * Description:   Gives the amount of time left that the drug
 *                will be in the body if no more taken. Included
 *                for purposes of diagnosing by mortals.
 * Returns:       int - the time left in seconds
 */
public int
query_time_left()
{
    int result, extra;

    calculate_overdose();
    result = gDose / gRate;
    result *= gInterval;
    extra = gDose % gRate;
    if (!extra)
    {
        return result;
    }
    else
    {
        return (result + gInterval);
    }
}

/*
 * Function name: query_limit
 * Description:   Gives the overdose level. Included for purposes
 *                of diagnosing by mortals.
 * Returns:       the limit
 */
public int
query_limit()
{
    calculate_overdose();
    return gLimit;
}

public void
create_object()
{
    add_name("overdose");
    set_long("This is an object to keep track of the drug levels " +
        "and start overdosing effects.\n");

    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
}

/*
 * Function name: stat_object
 * Description:   Called when a wizard stats the object
 * Returns:       A string describing the object.
 */
public string
stat_object()
{
    calculate_overdose();
    return ::stat_object() +
    "Time   : " + gTime + "\n" +
    "Dose   : " + gDose + "\n" + 
    "Rate   : " + gRate + " per " + gInterval + " seconds\n";
}

/*
 * Function name: query_auto_load
 * Description:   Used to reload the overdose into the player if
 *                it hasn't become obsolete when he quits.
 */
public nomask string
query_auto_load()
{
    if (calculate_overdose() <= 0)
    {
        return "";
    }

    return MASTER + ":" +
        gDose + "," +
        gRate + "," +
        gInterval + "," + 
        query_name() + 
        "#USER#";
}

/*
 * Function name: init_arg
 * Description:   Parses the data from the saved object
 * Arguments:     arg - the arguments to init
 */
public nomask void
init_arg(string arg)
{
    string str, *arglist;

    sscanf(arg, "%s#USER#", str);
    arglist = explode(str, ",");
    sscanf(arglist[0], "%d", gDose);
    sscanf(arglist[1], "%d", gRate);;
    sscanf(arglist[2], "%d", gInterval);
    set_name(arglist[3]);
    gTime = time();
}
