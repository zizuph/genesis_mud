/*
 * guard_stun_object.c
 *
 * This is the paralyzer object for the guard stun
 * attacks in the village.
 *
 * Khail - June 19/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "defs.h"

inherit "/std/object";

object guard,
       p_stunned;
int rec_alarm_id,
    time_left,
    ld_detected;

public int cmd_lock(string str);
public void regain_cons(object who);
/*
 * Function name: create_object
 * Description  : Turns this object into a paralyzer.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_object()
{
    set_name("_guard_stun_object");
    add_name("stun_object");
    set_short("_guard_stun_object");
    set_long("_guard_stun_object");
    set_no_show();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1); 
}

/*
 * Function name: set_guard
 * Description  : Sets the 'guard' variable, so we have a pointer
 *                to the guard that stunned us. Called by the
 *                guard when he renders a player unconscious and
 *                preparing this object for movement to the player.
 * Arguments    : ob - Object pointer to the stunning guard.
 * Returns      : n/a
 */ 
public void
set_guard(object ob)
{
    guard = ob;
}

/*
 * Function name: query_guard
 * Description  : Obviously returns the 'guard' variable, which
 *                is an object pointer to the guard that knocked
 *                the player out.
 * Arguments    : n/a
 * Returns      : As described.
 */
public object
query_guard()
{
    return guard;
}

/*
 * Function name: set_recovery_time
 * Description  : Sets how long the player is to be unconscious
 *                and starts an alarm running to regain consciousness.
 *                The time spent unconscious varies depending on the
 *                size of the player and how 'hard' they were hit
 *                when knocked out, determined in the guard's special
 *                attack code and set when the stun object is set
 *                up for the player.
 * Arguments    : time - Integer representing how many seconds the
 *                       player will be unconscious.
 * Returns      : n/a
 */
public void
set_recovery_time(int time)
{
    object who;

    if (!(who = environment()))
        remove_object();
    
    if (get_alarm(rec_alarm_id))
        remove_alarm(rec_alarm_id);
    rec_alarm_id = set_alarm(60.0, 0.0, &regain_cons(who));
    time_left = time - 60;
    time_left = (time_left < 60 ? 0 : time_left);
}

/*
 * Function name: init (MASK)
 * Description  : Called when this object meets another. Here
 *                we mask it to add a few things to the player.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();

  /* Only effect players who are this object's environment. */
    if (TP != environment())
        return;

  /* The following add_action will hook every command the */
  /* player tries to use, and force all to fail. */
    add_action(cmd_lock, "", 1);
  /* Make their short desc reflect their unconscious state. */
    TP->add_prop(LIVE_S_EXTRA_SHORT, " is unconscious");
  /* We'll also stun the player, just in case. */
    TP->add_stun();
    p_stunned = TP;
}

/*
 * Function name: cmd_lock
 * Description  : Called by the add_action, this function
 *                forces every command attempt to fail, except
 *                for wizards, of course.
 * Arguments    : str - String containing arguments to the
 *                      attempted command.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
cmd_lock(string str)
{
  /* Certain commands we'll allow even when paralyzed. */
    switch(query_verb())
    {
        case "commune":
        case "idea":
        case "bug":
        case "praise":
        case "typo":
        case "sysbug":
        case "sysidea":
        case "syspraise":
        case "systypo":
        case "quit":
        case "reply":
            return 0;
    }

    write("Your unconscious state prevents you from doing " +
        "anything!\n");

  /* Wizards aren't effected. */
    if (TP->query_wiz_level())
    {
        write("As you are a wizard, however, this will not " +
            "effect you.\n");
        return 0;
    }
    return 1;
}

/*
 * Function name: regain_cons
 * Description  : Allows the player to 'wake up'. This is called
 *                by a couple possibilities, either the recovery
 *                time alarm running down, or it may be forced
 *                after the player is thrown into jail, then
 *                remove this object.
 * Arguments    : who - Object pointer to the player to wake up.
 * Returns      : n/a
 */
public void
regain_cons(object who)
{
    object dest;
    int ld;

  /* First we'll see if the player has gone linkdead. If */
  /* they have, we'll add the time of linkdeath to the */
  /* time left to recover, so the stun won't wear off */
  /* while they're LD. We only add the time spent LD to */
  /* the time left when we first detect it, however, */
  /* so we don't wind up actually increasing the amount */
  /* of time the player spends stunned. */
    if (ld = who->query_linkdead())
    {
        if (!ld_detected)
        {
            ld_detected = 1;
            time_left += (time() - ld);
        }
        rec_alarm_id = set_alarm(60.0, 0.0, &regain_cons(who));
        return;
    }

  /* If there's still time left to remain unconscious, subtract */
  /* another 60 seconds from it and run a 60 second alarm to */
  /* call this function again. */
    if (time_left > 0)
    {
        time_left -= 60;
        rec_alarm_id = set_alarm(60.0, 0.0, &regain_cons(who));
        return;
    }

  /* If the player is waking up, but in the waiting room, */
  /* we'll trans them to either the environment of their */
  /* guard, or the last room they were in, to wake up. */
    if (file_name(environment(who)) == (ROOM + "jail_waiting"))
    {
        if (!guard)
            dest = who->query_prop(LIVE_O_LAST_ROOM);
        else
            dest = environment(guard);
        who->move_living("M", dest, 1, 1);
    }

    remove_object();
}

/*
 * Function name: remove_object
 * Description  : Called when this object is being destructed.
 *                It should never be necessary, but we'll remove
 *                the extra short and stun props here too, just
 *                in case it gets removed while the player is
 *                still unconscious.
 * Arguments    : n/a
 */
public void
remove_object()
{
    if (environment() && living(environment()))
    {
        tell_object(environment(), "Groggily, you manage to regain " +
            "consciousness.\n");
        environment()->remove_prop(LIVE_S_EXTRA_SHORT);
        environment()->remove_stun();
        tell_room(environment(environment()), QCTNAME(environment()) + 
            " groans and regains consciousness.\n", ({environment()}));
    }

    p_stunned->remove_stun();
    ::remove_object();
}
