/*
 *  /d/Sparkle/area/tutorial/herbs/silverdell_herb.c
 *
 *  We don't want herbs piling up ... and since there is no place to
 *  sell them here, we blow them away if they are dropped.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 *  Updated by Gronkas August 3, 2016 to fix a typo in blow_away()
 */
#pragma strict_types

inherit "/std/herb";

#include <stdproperties.h>
#include <language.h>

/* Prototypes */
public void        blow_away();
public void        leave_env(object from, object to);


/*
 * Function name:        blow_away
 * Description  :        give a delay before we blow the item away. Also
 *                       check to see if anyone has picked it up first.
 */
public void
blow_away()
{
    if (interactive(environment(this_object())))
    {
        return;
    }

    tell_room(environment(this_object()), "A strong gust of wind suddenly"
      + " blows " + LANG_THESHORT(this_object()) + " away.\n");
    remove_object();
} /* blow_away */


/*
 * Function name:        leave_env
 * Description  :        we don't want these piling up anywhere, so we
 *                       have them vanish if the player drops them
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
        return;

    if (!to->query_prop(ROOM_I_IS))
    {
        return;
    }

    set_alarm(10.0, 0.0, blow_away); /* give it a bit of time */
} /* leave_env */
