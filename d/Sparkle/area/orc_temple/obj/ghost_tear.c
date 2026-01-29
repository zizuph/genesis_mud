/*
 *  /d/Sparkle/area/orc_temple/obj/ghost_tear.c
 *
 *  These tears are dropped by ghosts in the orc dungeons near Sparkle.
 *  They are part of a quest there.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"


/* Definitions */
#define            ALARM_INTERVAL    60.0

/* Global Variables */
public mixed       Vanish_Alarm = 0;


/* prototypes */
public void        create_object();
public void        leave_env(object from, object to);
public void        do_vanish();


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("tear");
    add_adj( ({ "crystalline", "ghost" }) );
    add_name( ({ QUEST_TEAR }) );

    set_short("crystalline tear");
    set_long("Shaped like a tiny tear, this jewel-like crystalline"
      + " object feels very warm to the touch.\n");

    add_prop(OBJ_I_NO_GIVE, "You'd better keep that.\n");
    add_prop(OBJ_M_NO_SELL, "The crystalline tear has no monetary"
      + " value.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 7);
} /* create_object */


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

    if (!objectp(from) || !objectp(to))
        return;

    if (!to->query_prop(ROOM_I_IS))
    {
        if (interactive(to) &&
            to->query_prop(ORC_TEMPLE_QUEST_PROP) != "ghost")
        {
            set_alarm(0.0, 0.0, &do_vanish());
            return;
        }

        if (Vanish_Alarm)
        {
            remove_alarm(Vanish_Alarm);
            Vanish_Alarm = 0;
        }

        return;
    }

    if (Vanish_Alarm)
    {
        remove_alarm(Vanish_Alarm);
    }

    Vanish_Alarm = set_alarm(ALARM_INTERVAL, 0.0, "do_vanish");
} /* leave_env */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 * We redefine this to make sure the tears don't pile up.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (dest->query_prop(ROOM_I_IS))
    {
        Vanish_Alarm = set_alarm(ALARM_INTERVAL, 0.0, "do_vanish");
    }
} /* enter_env */


/*
 * Function name:        do_vanish
 * Description  :        the object disappears
 */
public void
do_vanish()
{
    object env = environment(this_object());

    if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "The crystaline tear dissolves into mist and"
          + " is gone.\n");
    }
    else if (living(env))
    {
        env->catch_tell("The crystaline tear dissolves into mist and is"
          + " gone.\n");
    }

    if (Vanish_Alarm)
    {
        remove_alarm(Vanish_Alarm);
    }

    Vanish_Alarm = 0;

    remove_object();
} /* do_vanish */