/*
 *  /d/Emerald/telberin/science/potions/lingering_cooldown.c
 *
 *  Modified from /std/resistance.c to create a cooldown
 *  period of 10 minutes between when a resistance from one of the
 *  potions wears off, and when another potion can be quaffed again.
 *
 *  Created March 2014, by Cooper Sherry (Gorboth)
 */
 
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>


/* Global Variables */
public mixed    Res_Type;   /* The type of resistance */
public int      Alarm_Id;   /* The id of the alarm to end the effect */
public float    Time;	    /* How long time it will be in effect */
public int      Expiration; /* Timestamp of expiration (for recovery) */

/* Prototypes */
public void        create_cooldown();
nomask void        create_object();
public void        enter_env(object to, object from);
public void        end_cooldown();
public string      stat_object();
public void        dissolve_beaker(object loc);

public void        set_lingering_potion_type(string s) { Res_Type = s; }
public string      query_lingering_potion_type()    { return Res_Type; }
public void        set_time(int i)                   { Time = itof(i); }
public int         query_time()                   { return ftoi(Time); }
public void        set_expiration(int i)             { Expiration = i; }
public int         query_expiration()             { return Expiration; }


/*
 * Function name: create_cooldown
 * Description:   Create the cooldown
 */
public void
create_cooldown()
{
    set_name("Potion_Still_In_System");
    add_prop(OBJ_M_NO_DROP, "Drop what?\n");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();
} /* create_cooldown */


/*
 * Function name: create_object
 * Description:   The standard create
 */
nomask void
create_object()
{
    Time = 0.0;
    create_cooldown();
} /* create_object */


/*
 * Function name: enter_env
 * Description:   Called each time this object enters another environment
 * Arguments:     to   - The object this object enters
 *		  from - The object this object leaves
 */
public void
enter_env(object to, object from)
{
    if (objectp(to) && living(to))
    {
        if (Time && (!Alarm_Id || !sizeof(get_alarm(Alarm_Id))))
            Alarm_Id = set_alarm(Time, 0.0, end_cooldown);
    }

    ::enter_env(to, from);
} /* enter_env */


/*
 * Function name: end_cooldown
 * Description:   Called when it is time to end the cooldown.
 */
public void
end_cooldown()
{
    object ob;

    if (objectp(ob = environment(this_object())) && living(ob))
        tell_object(ob,
            "You finally feel that the last potion you quaffed"
          + " has run its course through your system. It would"
          + " probably be safe to quaff another one now.\n");

    remove_alarm(Alarm_Id);
    remove_object();
} /* end_cooldown */


/*
 * Function name: stat_object
 * Description:   Called when wizard stats the object
 * Returns:       A string describing the object.
 */
public string
stat_object()
{
    mixed   a_info;
    string  desc = ::stat_object();

    desc += "================[Specific Cooldown Info]================\n"
         +  "Resistance: " + Res_Type + "\n"
         +  "Duration:   30 minutes\n";

    if (Alarm_Id && sizeof(a_info = get_alarm(Alarm_Id)))
        desc += "Remaining:  " + CONVTIME(ftoi(a_info[2])) + "\n";

    desc += "========================================================\n";

    return desc;
} /* stat_object */


/*
 * Function name:        dissolve_beaker
 * Description  :        let the player know that the beaker is
 *                       destroyed.
 * Arguments    :        object loc = the environment the potion was in
 */
public void
dissolve_beaker(object loc)
{
    string  dtxt;

    dtxt = "Its weakened inner surface suddenly exposed to air, the"
      + " thick crystal beaker bursts into a million pieces and is"
      + " lost.\n";

    if (living(loc))
    {
        set_alarm(2.0, 0.0, &loc->catch_tell(dtxt));
        return;
    }

    set_alarm(5.0, 0.0, &tell_room(loc, dtxt));
    return;
} /* dissolve_beaker */


/*
 * Function name: init_arg
 * Description  : This function is called when the potion recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_arg(string str)
{
    string  r_type;
    string  foobar;
    int     p_expiration;

    if (sscanf(str, "%scooldown_begin#%s#%i#%scooldown_end#", 
               foobar, r_type, p_expiration, foobar) == 4)
    {
        if (p_expiration <= time())
        {
            set_alarm(0.0, 0.0, remove_object);
            return;
        }

        Expiration = p_expiration;
        set_lingering_potion_type(r_type);
        Time = itof(Expiration - time());

        if ((Time > 0.0) && (!Alarm_Id || !sizeof(get_alarm(Alarm_Id))))
            Alarm_Id = set_alarm(Time, 0.0, end_cooldown);
    }
} /* init_arg */


/*
 * Function name: query_auto_load
 * Description  : We let the players hoard these over logins. Upon recovery
 *                we keep track of the type, level, and time remaining
 *                before the potion expires.
 */
public string
query_auto_load()
{
    string file = MASTER;

    return file + ":cooldown_begin#"
                + Res_Type + "#"
                + (Expiration) + "#"
                + "cooldown_end#";
} /* query_auto_load */


/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover.
 */
public string
query_recover()
{
    return 0;
}