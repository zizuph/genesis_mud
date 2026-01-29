/*
 * death_mark.c
 *
 * The object that sends a player off to meet his maker.
 * In this particular case, that'd be Lars.
 *
 * Khail, Nov. 15/96
 *
 * Based off original death_mark.c by:
 * Mrpr 901122
 * Tintin 911031
 * Nick 920211
 */
#pragma strict_types

#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include "death.h"

inherit "/std/object";

/* Global vars */
int start_death_id,
    reincar_id;

/* Prototypes */
public void create_object();
public string query_auto_load();
public void init_arg(string str);
public void start_death();
public void do_reincarnate(object who);
public void enter_env(object to, object from);

/*
 * Function name: create_object
 * Description  : Sets variables to create death mark.
 *                Since the object is fully invis, no long
 *                or short desc are needed.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_object()
{
  /* Make the object completely invis, even to wizards. */
    set_no_show();
    set_name("death_mark");
    add_prop(OBJ_I_WEIGHT, 0);     /* 0 grams    */
    add_prop(OBJ_I_VOLUME, 0);     /* 0 ml       */
    add_prop(OBJ_I_VALUE, 0);      /* Worthless  */
    add_prop(OBJ_M_NO_DROP, 1);    /* Can't drop */
}

/*
 * Function name: query_auto_load
 * Description  : Returns the path of this object, so that it
 *                can be added to the player's autoload list.
 *                This ensures players can't 'quit' out of the
 *                death sequence, as they'll be pulled back in
 *                the next time they log in and this object
 *                autoloads.
 * Arguments    : n/a
 * Returns      : A string, the filename of this object.
 */
public string
query_auto_load()
{
    return MASTER + ":";
}

/*
 * Function name: init_arg
 * Description  : Initializes the object on loading. Used normally
 *                for restoring variables saved in the query_auto_load
 *                string, here we are just using it to start an alarm.
 * Arguments    : string str - n/a in this case.
 * Returns      : n/a
 */
public void
init_arg(string str)
{
  /* Make sure there's not already an alarm running to start_death() */
  /* before starting one. If there isn't, call start_death() in 1 */
  /* second. */
    if (get_alarm(start_death_id))
        return;
    start_death_id = set_alarm(1.0, 0.0, start_death);
}

public void
tell_the_others()
{
    object dead,
           next;

    dead = environment();

    tell_room(environment(dead), "A sudden chill permeates the " +
        "air, and a dark shadow seems to sweep over " +
        dead->query_possessive() + " lifeless eyes.\n", dead);
}         
        
/*
 * Function name: start_death
 * Description  : Starts up the death routine. Delivers appropriate
 *                messages to player who died and those in the room,
 *                and either moves the player to death's room, or 
 *                calls reincarnate in him/her.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
start_death()
{
    int dnr;
    object ned, my_host, badge;

  /* Figure out who's carrying the mark. */
    my_host = environment();

  /* Set the start_death alarm id to ensure it won't run again */
  /* for whatever reason. */
    start_death_id = 1;

  /* Make sure this mark is actually on a player who's died. Remove */
  /* it if that's not the case. */
    if (!my_host || !living(my_host) || !my_host->query_ghost())
    {
        remove_object();
        return;
    }

  /* Make sure the player isn't already a ghost. */
    if (MASTER_OB(my_host) == LOGIN_NEW_PLAYER)
    {
        remove_object();
        return;
    }
        
  /* See how many times the player has died DURING THIS BOOT. */
    setuid(); seteuid(getuid());
    dnr = DEATH_ROOM->query_deaths(my_host->query_real_name());

    tell_object(my_host, "You see a dark hooded man standing " +
        "beside your corpse.\n" +
        "He is wiping the bloody blade of a wicked-looking scythe " +
        "with slow, measured motions. Suddenly he stops and seems to " +
        "look straight at you with his empty... no, not empty but... " +
        "orbs....\n\n");

  /* If this is the player's first death this boot, deliver appropriate */
  /* messages, then trans the player to DEATH_ROOM to wait to be */
  /* reincarnated. Also in the even that my_host is link dead, we'll */
  /* send him/her through the long sequence even though dnr might */
  /* be greater than or equal to one. This is to reduce the chances */
  /* of a player walking around as a ghost. */
    if (!dnr || !interactive(my_host))
    {
        tell_the_others();
        tell_object(my_host, "Death says: COME WITH ME, MORTAL ONE!\n\n" +
            "He reaches for you, and suddenly you find yourself in " +
            "another place.\n\n");
    setuid(); seteuid(getuid());
        my_host->move(DEATH_ROOM, 1);
    }

  /* Looks like the player's already died at least once, so have */
  /* Death taunt him/her for a minute, increment the number of */
  /* times they've died, and start them reincarnating. */
    else
    {
        tell_the_others();
        tell_object(my_host, "Death says: COME WITH M...\n\n " +
            "He suddenly looks closer at you, focusing his empty " +
            "orbs on your very essence. After a long scrutinization " +
            "he gives you a disgusted look.\n\n" +
            "Death says: DON'T YOU THINK ONCE IS ENOUGH? I KNEW THIS " +
            "REINCARNATION BUSINESS WAS A BAD IDEA THE FIRST TIME I " +
            "EVER HEARD OF IT!\n\n" +
            "Death mumbles angrily as he lifts you up and throws you " +
            "on another short flight, to what is by now a rather " +
            "familiar place.\n\n");

      /* Make sure we don't call do_reincarnate twice somehow. */
        if (get_alarm(reincar_id))
            return;

      /* Start them on the road to recovery in 1 second. */
        reincar_id = set_alarm(1.0, 0.0, &do_reincarnate(my_host));
    }
}

/*
 * Function name: do_reincarnate
 * Description  : Calls reincarnate() in the player that died.
 * Arguments    : object who - object pointer to the player to
 *                be reincarnated.
 * Returns      : n/a
 */
public void
do_reincarnate(object who)
{
  /* Make sure the object is pointing at the person holding this */
  /* marker (just a failsafe). */
    if (!who || environment() != who)
        return;

  /* Secondary failsafe to prevent attempts to reincarnate players */
  /* that are non-interactive. If who is non-interactive, move */
  /* them through the normal death sequence rather than dumping */
  /* them straight to reincarnate. */
    if (!interactive(who))
    {
            setuid(); seteuid(getuid());
        who->move(DEATH_ROOM, 1);
        return;
    }
    
  /* Ok, time to reincarnate the player, which will prep them for */
  /* a new body and trans 'em to /d/Genesis/login/bodies.c */
    who->reincarnate();
    if (this_object())
        remove_object();

}

/*
 * Function name: enter_env (MASK)
 * Description  : Evaluates certain things when this object enters
 *                another object's inventory. Here, we use it to start
 *                up the start_death alarm.
 * Arguments    : object to - Object pointer to the environment this
 *                            object is moving into.
 *                object from - Object pointer to the environment this
 *                              object is moving out of.
 * Returns      : n/a
 */
public void
enter_env(object to, object from)
{
  /* Always call back to masked functions. */
    ::enter_env(to, from);

  /* Don't bother with the alarm if the new environment isn't */
  /* alive. */
    if (!to || !living(to))
        return;

  /* Don't run the alarm if it's already running. */
    if (get_alarm(start_death_id))
        return;

  /* Don't try to 'kill' a ghost. */
    if (MASTER_OB(to) == LOGIN_NEW_PLAYER)
        return;
  
  /* Ok, start the death sequence by calling start_death in 1 sec. */
    start_death_id = set_alarm(1.0, 0.0, start_death);
}
