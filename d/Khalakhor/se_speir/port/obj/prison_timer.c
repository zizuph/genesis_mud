/*
 * prison_timer.c
 *
 * This object is a 'tracker' for players who have been
 * arrested by guards in Port Macdunn and thrown into
 * jail.
 *
 * First, the player is arrested and thrown into jail.
 * This action clones this object into the prisoner's inventory,
 * and arrest_me(prisoner) is called. This sets their temp
 * start location to their cell, and figures out how long
 * to keep them in there.
 *
 * Every minute, a function is checked which handles a few
 * things. First, if the prisoner is still in his cell, it
 * reduces the time left by 60 seconds, and then sets an alarm
 * to call itself again in another 60 seconds. If the player
 * is LD, it calls itself again in another 60 seconds, but
 * without reducing the time left. If the player is not LD
 * but not in his cell, it assumes he escaped somehow, clears
 * the temp startloc, and removes itself. Once the entire
 * sentence has been served, it calls release_me.
 *
 * Release_me basically just releases the prisoner, and moves
 * him outside the cell, where he'll find the equipment stripped
 * from him upon arrest.
 *
 * Khail - June 20/97
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "defs.h"

#define PRISON_TIMER_NAME  "_prison_timer"
#define KPM_LIVE_I_ARRESTS "_kpm_live_i_arrests"
/* BAIL_FACTOR is number of plats per 5 minutes in sentence. */
#define BAIL_FACTOR        2

inherit "/std/object";

int time_left,
    sentence,
    counter;

public void
create_object()
{
    set_name(PRISON_TIMER_NAME);
    add_name("timer");
    set_short("_macdunn_prison_timer");
    set_long("_macdunn_prison_timer");
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, 1);
}

/*
 * Functio name: release_me
 * Description : Called when a player has 'served his sentence'
 *               and is released from jail.
 * Arguments   : who - Object pointer to the released player.
 * Returns     : n/a
 */
public void
release_me(object who)
{
    string dest;
    object *equip;
    
    reset_euid();
    tell_object(who, "A guard arrives and unceremoniously " +
        "escorts you out of your cell.\n");
    tell_room(environment(who), "A guard arrives and " +
        "unceremoniously escorts " + QTNAME(who) + " out " +
        "of the cell.\n", ({who}));
    switch(file_name(environment(who)))
    {
        case ROOM + "jail_cell_1":
            dest = ROOM + "jail_corridor_2";
            break;
        case ROOM + "jail_cell_2":
        case ROOM + "jail_cell_3":
            dest = ROOM + "jail_corridor_3";
    }

    equip = (ROOM + "jail_storage")->get_equipment(who);
    if (sizeof(equip))
    {
        tell_room(find_object(dest), "A guard arrives, and " +
            "drops some equipment on the floor.\n");
        equip->move(find_object(dest));
        who->move_living("M", dest);
        tell_room(find_object(dest), "The guard escorts " +
            QTNAME(who) + " out of " + who->query_possessive() +
            " cell and leaves.\n", ({who}));
    }
    else
    {
        who->move_living("M", dest);
        tell_room(find_object(dest), "A guard arrives and " +
            "escorts " + QTNAME(who) + " out of " +
            who->query_possessive() + " cell and leaves.\n",
            ({who}));
    }
    who->set_temp_start_location(0);
    remove_object();
}

/*
 * Function name: check_time_left
 * Description  : This function is called every minute to count
 *                down the prison sentence. If it finds out the
 *                player is LD, it stops reducing the time_left
 *                but keeps running until the player returns from
 *                link death. If the prisoner is no longer in a
 *                cell, nor linkdead, we'll assume he/she escaped
 *                somehow and remove this object.
 *                If we discover armageddon has hit, give the
 *                prisoner a premature release. End of the world
 *                and all that ;)
 * Arguments    : who - Object pointer to the prisoner.
 * Returns      : n/a
 */
public varargs void
check_time_left(object who = 0)
{
    int delay;

  /* If 'who' is not set, default to environment. */
    if (!who)
        who = environment();

  /* If we get a 'who' pointer that isn't to the environment, */
  /* abort. */
    else if (who != environment())
    {
        who->set_temp_start_location(0);
        remove_object();
        return;
    }

  /* If 'who' has managed to escape the jail cell somehow, */
  /* abort, unless the player is linkdead. */
    if (!environment(who) ||
        (!environment(who)->is_jail_cell() &&
        !who->query_linkdead()))
    {
        who->set_temp_start_location(0);
        remove_object();
        return;
    }

  /* If who is in a jail cell, but their startloc isn't */
  /* set to that cell, set it. */
    if (environment(who)->is_jail_cell() &&
        who->query_temp_start_location() != file_name(environment(who)))
        who->set_temp_start_location(file_name(environment(who)));

  /* Release prisoner now if armageddon is active. */
    if ("/secure/armageddon"->shutdown_active())
    {
        release_me(who);
        return;
    }

  /* If who is linkdead, keep ticking, but don't remove any */
  /* time from the amount left to spend in jail. Otherwise,  */
  /* take 60 seconds away from the time to serve and set up */
  /* a 60 second alarm for the next check. */
    if (!who->query_linkdead())
    {
        if (time_left <= 0)
        {
            release_me(who);
            return;
        }
        if (time_left < 60)
            delay = time_left;
        else
            delay = 60;
        time_left -= delay;
    }
    else
    {
        delay = 60;
    }

    counter = set_alarm(itof(delay), 0.0, &check_time_left(who));
}

/*
 * Function name: query_auto_load
 * Description  : Makes imprisonment pass beyond armageddon.
 * Arguments    : n/a
 * Returns      : A string containing the filename of this object,
 *                plus how much time is left on the prison sentence.
 */
public string
query_auto_load()
{
    return MASTER + ":" + time_left;
}

/*
 * Function name: init_arg
 * Description  : Called when this object is autoloaded to 'remember'
 *                how much time was left in the prison sentence.
 * Arguments    : arg - String argument as set in query_auto_load.
 * Returns      : n/a
 */
public void
init_arg(string str)
{
    time_left = atoi(str);
    set_alarm(1.0, 0.0, check_time_left);
}

/*
 * Function name: arrest_me
 * Description  : Handles the startloc reset and sentence
 *                time initialization, called when a player
 *                is thrown into a jail cell.
 * Arguments    : who - Object pointer to the prisoner.
 * Returns      : n/a
 */
public void
arrest_me(object who)
{
    int priors;

    if (who != environment())
        return;

    who->set_temp_start_location(file_name(environment(who)));
  /* Here we calculate the time spent in jail. It is */
  /* determined as 10 minutes, plus 5 minutes for each */
  /* prior arrest, to a max of 30 minutes. */
    priors = who->query_prop(KPM_LIVE_I_ARRESTS);
    time_left = 600 + priors * 300;
    time_left = (time_left > 1800 ? 1800 : time_left);
    sentence = time_left;
    check_time_left(who);
    seteuid(getuid());
    log_file("macdunn_jail",who->query_name() + " thrown " +
        "into jail for " + sentence + " seconds on " +
        ctime(time()) + ".\n");
}

/*
 * Function name: query_time_left
 * Description  : Returns how much longer the prisoner will be
 *                in jail.
 * Arguments    : n/a
 * Returns      : Time left in seconds.
 */
public int
query_time_left()
{
    return time_left;
}

/*
 * Function name: query_bail
 * Description  : Returns the bail cost (in plats) to bail this
 *                prisoner out of jail. Cost determined by the
 *                initial length of jail time.
 * Arguments    : n/a
 * Returns      : Cost of bail in plats as an int.
 */
public int
query_bail()
{
    return BAIL_FACTOR * (sentence / 60) / 5;
}
