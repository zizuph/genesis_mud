/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge6.c
 *
 *  Here the ledge along the western cliffs of the Blackwall Mountains has
 *  reached its western apex. There is one of the two remaining
 *  catapults of the ancient defences stationed here.
 *
 *  Copyright (c) August 1997, Cooper Sherry (Gorboth)
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
    set_cliff_base(DELRIMMON_DIR + "lakeside/w_cliff4");
    set_catapult_ledge();
    set_show_area_desc();

    set_extraline("The ledge has widened here, and the cliff"
      + " itself has been hewn away to create a deep"
      + " alcove in the towering rock.");

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge7","north");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge5","south");

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "The ledge falls away in that direction, and you decide to"
      + " avoid falling to your death.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "Sheer walls of rock block your movement in that direction.\n");

    reset_room();
} /* create_ledge */

/*
 * Function name: reset_room
 * Description  : clones a catapult to the room at resets
 */
void
reset_room()
{
    object catapult;

    if (!(catapult = present("catapult", this_object())))
    {
        catapult = clone_object(DELRIMMON_DIR + "obj/catapult");
        catapult->set_functioning(1);
        catapult->move(TO);

        return;
    }

    catapult->set_functioning(1);
    catapult->set_fired(0);
} /* reset_room */
