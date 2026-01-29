/*
 * /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge10.c
 * 
 * The ledge which runs along the cliffs of the western hills of the
 * Blackwall Mountains is nearly at its northernmost
 * edge here.
 *
 * Copyright (c) July 1998, by Cooper Sherry (Gorboth)
 *
 * Emerald Conversion: November 2000
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
    set_extraline("The ledge has begun to climb slightly here,"
      + " arcing gradually upward as it travels northeast. To"
      + " the north, the ledge seems to end abruptly at a"
      + " sheer precipice where a tree of some kind is growing."
      + " South of here, a machine is visible emerging from an"
      + " alcove in the cliff face.");

    add_item(({"precipice","precipieces","sheer precipiece"}), BSN(
        "The precipice ahead seemingly marks the northernmost"
      + " point of this ledge, offering no further point at"
      + " which feet might safely travel. A tree of some sort"
      + " grows out from the cliff at the edge of the precipice."));
    add_item(({"tree","trees"}), BSN(
        "The tree to the north is yet too distant to get any"
      + " detailed view. It appears to be growing directly from"
      + " the side of the cliff where it meets the precipice."));
    add_item(({"machine","machines"}), BSN(
        "The machine to the south appears to be a catapult of"
      + " some kind."));
    add_item(({"catapult","catapults"}), BSN(
        "The catapult to the south protrudes from what appears"
      + " to be a great alcove hewn from the stone cliff."));
    add_item(({"alcove","alcoves"}), BSN(
        "The alcove to the south rises a great distance from the"
      + " base of the ledge. From its depths, a catapult of some"
      + " sort emerges."));

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge11","northeast");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge9","south");

    set_no_exit_msg( ({ "east", "southeast" }),
        "There is a sheer drop off in that direction.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest", "north" }),
        "The cliff walls bar your progress.\n");

    set_cliff_base(DELRIMMON_DIR + "lakeside/nw_cliff3");

    reset_room();
} /* create_ledge */
