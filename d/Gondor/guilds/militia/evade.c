/*
 * /d/Gondor/guilds/militia/evade.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of his code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Evade special for the Thornlin Militia
 *
 * Gwyneth and Auberon, March 4, 2001
 *
 * Modification log:
 */

#include <stdproperties.h>
#include "militia.h"

public void stop_evade(object who);

int
evade(string str)
{
    object who = this_player(), tank;
    int num, duration, skill;

    skill = who->query_skill(SS_MILITIA);

    if (who->query_evade())
    {
        notify_fail("You are already evading attacks!\n");
        return 0;
    }
    else if (who->query_prop(PLAYER_I_EVADE_RESET))
    {
        notify_fail("You aren't ready to evade attacks again.\n");
        return 0;
    }
    else if (!who->query_attack())
    {
        notify_fail("You aren't in combat!\n");
        return 0;
    }
    else if (skill < 1)
    {
        notify_fail("You really have no clue how to begin. Perhaps you " +
            "should seek training.\n");
        return 0;
    }
    else if (who->query_prop(PLAYER_I_JAB_PREPARE))
    {
        notify_fail("You are too busy looking for a hole in your " +
            "enemy's defences to evade attacks well.\n");
        return 0;
    }
    else if (who->query_prop(PLAYER_I_JAB_RESET))
    {
        notify_fail("You are a bit winded from jabbing still.\n");
        return 0;
    }
    else if (who->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You are too stunned to do much of anything!\n");
        return 0;
    }

    who->set_evade(1);

    set_alarm(13.94, 0.0, &stop_evade(who));
    write("You watch your enemy closely, ready to evade his attacks.\n");
    return 1;
}

/* Function name : reset_evade
 * Description   : removes the props
 * Arguments     : object who - this_player()
 */
void
reset_evade(object who)
{
    who->remove_prop(PLAYER_I_EVADE_RESET);
    who->catch_tell("\nYou feel ready to attempt evasive maneuvers " +
        "again.\n\n");
}

/*
 * Function name: stop_evade
 * Description  : sets the evade variable off, and sets an alarm for
 *                the special to reset. Adds the reset prop.
 * Arguments    : object who - the evader
 */
void
stop_evade(object who)
{
    who->set_evade(0);

    who->add_prop(PLAYER_I_EVADE_RESET, 1);
    set_alarm(3.94, 0.0, &reset_evade(who));
    return;
}
