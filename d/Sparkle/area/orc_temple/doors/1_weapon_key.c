/*
 *  /d/Sparkle/area/orc_temple/doors/1_weapon_key.c
 *
 *  This is the key for the weapon storage room on the first level
 *  of the orc dungeons in Sparkle.
 *
 *  Created August 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/key";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* Prototypes */
public void        leave_env(object from, object to);
public void        do_vanish();

/*
 * Function name:        create_key
 * Description  :        the constructor
 */
public void
create_key()
{
    ::create_key();

    set_name("key");

    set_adj( ({ "thin", "black", "metal" }) );

    set_short("thin black key");
    set_long("This thin key is made of a heavy black metal.\n");

    set_key("_orc_temple_1_weapon_key");
} /* create_key */


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
        return;
    }

    set_alarm(0.0, 0.0, "do_vanish");
} /* leave_env */


/*
 * Function name:        do_vanish
 * Description  :        the object disappears
 */
public void
do_vanish()
{
    object env = environment(this_object());

    tell_room(env, "A rat dashes across the ground, grabs the key, and"
       + " zooms out of sight.\n");

    remove_object();
} /* do_vanish */