/*
 *  /d/Sparkle/area/tutorial/obj/castle_key.c
 *
 *  This is a key used in Krolocks castle to unlock the desk in
 *  his study. It can be found at:
 *
 *    /d/Sparkle/area/tutorial/castle/bedchamber.c
 *
 *  Created October 2005, by Cooper Sherry (Gorboth)
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
    add_name( ({ "_tutorial_castle_key", "_tutorial_item" }) );

    add_adj( ({ "large", "metal" }) );
    set_short("large key");
    set_long("This large metal key has an odd shape. The key head is"
      + " shaped like a triangle.\n");

    add_prop(OBJ_I_NO_GIVE, "You'd better keep that.\n");
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

