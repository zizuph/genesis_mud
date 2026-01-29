/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge9.c
 *
 *  The ledge along the western cliffs of the Blackwall Mountains
 *  widens here where an alcove has been hewn from the rock to
 *  provide shelter for the catapults of old.
 *
 *  Copyright (c) August 1997, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master.c";

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_ledge
 * Description  : allows us to create the room with area presets
 */
void
create_ledge()
{
    set_catapult_ledge();
    set_cliff_base(DELRIMMON_DIR + "lakeside/nw_cliff2");

    set_extraline("The ledge broadens here, extending both further"
      + " from the face of the cliff as well as deep within it. This"
      + " is due to a large alcove which has been hollowed out of"
      + " the stone, offering shelter to this area.");

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge10","north");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge8","south");
    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "The sheer drop in that direction gives you pause.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "Sheer walls of rock block your movement in that direction.\n");

    reset_room();
} /* create_ledge */

/*
 * Function name: reset_room
 * Description  : clones a catapult to the room, and sets it up
 */
void
reset_room()
{
    object catapult;

    if (!present("catapult", TO))
    {
        catapult = clone_object(DELRIMMON_DIR + "obj/catapult");
        catapult->move(TO);
    }
} /* reset_room */
