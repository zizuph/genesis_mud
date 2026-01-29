/*
 * /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge5.c
 *
 * This high ledge is on the western cliffs of the Blackwall Mountains
 * as they surround the lake of Del Rimmon.
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
    set_cliff_base(DELRIMMON_DIR + "lakeside/w_cliff3");

    set_extraline("The curvature of the cliffs has begun to turn directly"
      + " northward here, straightening the ledge somewhat. To the north,"
      + " a machine is visible, protruding from an alcove in the cliff"
      + " face.");

    add_item(({"machine","machines"}), BSN(
        "The machine to the north appears to be a catapult, but from"
      + " this vantage point, little else is evident."));
    add_item(({"catapult","catapults"}), BSN(
        "The catapult to the north protrudes from some sort of alcove"
      + " which has been hewn from the rocky cliffs."));
    add_item(({"alcove","alcoves"}), BSN(
        "The alcove hewn from the cliffs to the north is tall and"
      + " seemingly deep. A machine of some kind protrudes from its"
      + " base."));

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge6","north");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge4","southeast");

    set_no_exit_msg( ({ "northeast", "east" }),
        "You stop at the edge of the cliff, and decide not to go any"
      + " further.\n");
    set_no_exit_msg( ({ "south", "southwest", "west", "northwest" }),
        "You run up against the sheer faces of the cliff in that"
      + " direction.\n");
} /* create_ledge */
