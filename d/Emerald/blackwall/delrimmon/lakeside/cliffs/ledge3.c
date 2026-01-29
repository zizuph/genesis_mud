/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge3.c
 *
 *  Here the ledge which runs the length of the western cliffs in
 *  the Blackwall Mountains begins to approach its middle from the south.
 *
 *  Copyright (c) July 1997, Cooper Sherry (Gorboth)
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
    set_cliff_base(DELRIMMON_DIR + "lakeside/w_cliff1");

    set_extraline("The ledge has widened here, as the cliff itself"
      + " has been hewn away to create a large alcove in the"
      + " towering rock. The front of the ledge looks to have been"
      + " washed away recently, as a large portion of it is"
      + " missing, and debris can be seen trailing to the ground"
      + " below.");

    add_item( ({"alcove", "alcoves"}), BSN(
        "The alcove has been cut deep into the cliff face. It rises"
      + " perhaps thirty feet above the ledge, and spans a width of more"
      + " than fifteen feet in diameter."));

    set_catapult_ledge();

    add_item(({"ledge","ground","path","narrow ledge"}), BSN(
        "The ledge here seems to have been reinforced somewhat,"
      + " as it widens dramatically to allow for greater surface"
      + " area. The outside of the ledge seems to have been"
      + " washed away recently by some form of rockslide."));
    add_item(({"debris"}), BSN(
        "Bits of wood and rock lie broken and scattered among the crags"
      + " of the cliff face below. At the base of the cliff, a large pile"
      + " of rubble has formed."));
    add_item(({"bits of wood","wood","bits of rock",
               "bits of wood and rock"}), BSN(
        "The bits of wood and rock form a trail of debris which extends"
      + " to the base of the cliff where a pile of rubble has been"
      + " deposited. The pieces of wood do not look naturally formed,"
      + " but rather the remains of some man-made structure."));
    add_item(({"rubble","pile of rubble","piles of rubble"}), BSN(
        "At the base of the cliff sits a pile of rubble which looks"
      + " to have formed as the result of a major avalanche or"
      + " rockslide recently. The contents are not evident from"
      + " this high vantage point."));
    add_item(({"base","base of the cliff","cliff base",
               "ground below"}), BSN(
        "The base of the cliff is far below where the trees jut up"
      + " against the rock face. There looks to be a pile of rubble"
      + " down there."));
    add_item( ({"rockslide", "avalanche"}), BSN(
        "The damage to the cliff ledge here suggests that there was"
      + " quite recently a major rockslide which deposited much of"
      + " the cliffside below in a great pile of rubble."));

    add_cmd_item( ({"rubble", "pile of rubble", "piles of rubble"}),
        ({"search", "dig", "dig in"}), BSN(
        "The pile of rubble is clear down at the bottom of the cliff"
      + " side, making it quite unaccessable from this ledge."));
    add_item( ({"damage"}), BSN(
        "The damage is extensive. A large section of the ledge has been"
      + " torn away, and a great deal of the cliffside below looks"
      + " to have been gutted out and deposited in a heap of rubble."));

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge4","north");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge2","southeast");

    set_no_exit_msg( ({ "northest", "east" }),
        "You approach the edge of the ledge, and quickly back away again"
      + " to avoid a surely fatal drop.\n");
    set_no_exit_msg( ({ "south", "southwest", "west", "nourthwest" }),
        "The sheer faces of the cliffs prevent any movement in that"
      + " direction.\n");

    reset_room();
} /* create_ledge */
