/*
 *  /d/Sparkle/area/tutorial/obj/key.c
 *
 *  This is a simple key used in the pre-creation tutorial
 *  in room:
 *
 *    /d/Sparkle/area/tutorial/pre_tutorial/5.c
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

/* prototypes */
public void        create_object();
public void        leave_env(object from, object to);


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("key");
    add_name( ({ "_tutorial_key" }) );

    add_adj( ({ "small", "metal" }) );
    set_short("small metal key");
    set_long("This is a small metal key. Keys such as this are often used"
      + " in Genesis to unlock doors. Most doors in the game respond to"
      + " the commands <open>, <lock>, and <unlock>.\n");

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

    if (!objectp(from) || !objectp(to) || !living(from))
        return;

    if (!to->query_prop(ROOM_I_IS))
    {
        return;
    }

    tell_room(to, "The " + this_object()->short() + " falls to the"
      + " ground and vanishes in a flash of light.\n");
    set_alarm(0.0, 0.0, "remove_object");
} /* leave_env */
