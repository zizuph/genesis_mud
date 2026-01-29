/*
 *  /d/Sparkle/area/orc_temple/doors/2_cell_key.c
 *
 *  This is the key for the prison cells on the 2nd level of tne Dungeon
 *  beneath the Orc Temple in Sparkle.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/key";

#include <stdproperties.h>
#include "../defs.h"

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
    add_name( ({ "ring", JAILERS_KEYS }) );
    add_adj( ({ "noisy", "ring", "of", "key" }) );

    set_short("noisy ring of keys");
    set_long("A thin black iron ring has been strung with many wirey"
      + " keys which are covered in filth.\n");

    set_key("_orc_temple_2_cell_key");
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