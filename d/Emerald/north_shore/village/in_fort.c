/*
 *  /d/Emerald/north_short/village/in_fort.c
 *
 *  This is a tree fort that many of the local elf children use to
 *  play in. It is quite a fine place to be, unless an Ogre happens to
 *  be kicking the tree that houses it. ;-)
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/* Definitions */
#define            FALLROOM ("/d/Emerald/north_shore/village/fort_room")

/* Prototypes */
public void        create_emerald_room();
public void        get_kicked();
public void        get_kicked2();
public void        get_kicked3();

/* Global Variables */
public int         Being_Kicked = 0; /* Are kick effects in progress? */


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit("fort_room", "down");
} /* create_emerald_room */


/*
 * Function name:        get_kicked
 * Description  :        Apparently, an Ogre is kicking the tree that
 *                       this fort is built in. Bad times for those
 *                       herein shall ensue.
 */
public void
get_kicked()
{
    if (Being_Kicked)
    {
        return; /* no stacking the effects, please */
    }

    tell_room(this_object(), "The tree is suddenly shaken by a"
      + " massive blow! You begin to lose your footing ...\n");

    set_alarm(1.0, 0.0, get_kicked2);
    Being_Kicked = 1;
} /* get_kicked */


/*
 * Function name:        get_kicked2
 * Description  :        everyone screams
 */
public void
get_kicked2()
{
    mixed  *target = FILTER_LIVE(all_inventory(this_object()));
    int     i;

    for (i = 0; i < sizeof(target); i++)
    {
        target[i]->command("$scream");
    }

    set_alarm(1.0, 0.0, get_kicked3);
} /* get_kicked2 */


/*
 * Function name:        get_kicked3
 * Description  :        everyone falls to the ground
 */
public void
get_kicked3()
{
    mixed  *target = FILTER_LIVE(all_inventory(this_object()));
    int     i;

    if (sizeof(target))
    {
        tell_room(find_object(FALLROOM), "From above "
          + COMPOSITE_LIVE(target) + " "
          + ((sizeof(target) > 1) ? "fall" : "falls")
          + " screaming to the ground, landing with a terrific"
          + " crash!\n");
    }

    for (i = 0; i < sizeof(target); i++)
    {
        target[i]->catch_tell("You fall off the platform all the"
          + " way to the ground below ... OOOOOOF!\n");
        target[i]->move_living("M", FALLROOM, 1, 1);
        target[i]->reduce_hit_point(500 + random(100));
        tell_room(this_object(), QCTNAME(target[i]) + " falls off"
          + " the platform!\n");
    }

    Being_Kicked = 0;
} /* get_kicked3 */