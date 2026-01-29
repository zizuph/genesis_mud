/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_shore2.c
 *
 *  A shoreline just south of the westernmost edge of Del Rimmon
 *  in Emerald.
 *
 *  Copyright (c) September 1997 by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 *  Added fishing     : August 2021 (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeshore.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_lakeshore
 * Description  : allows us to create the room with area presets
 */
void
create_lakeshore()
{
    set_loc(1);
    set_side("west");

    set_extraline("The shore winds north and south along the lake"
                + " here. Only the waves, softly lapping against the"
                + " bank, give any indication of movement in this"
                + " quiet basin among the cliffs.");

    add_item( ({"lake", "river", "del rimmon"}), BSN(
        "Del Rimmon spreads out as a wide oval lake fenced by"
      + " steep grey hills on all sides. At the far southern end"
      + " of the lake, three tall peaks rise above the water."
      + " There appears to be some sort of object rising out of"
      + " the water to the east."));
    add_item( ({"object"}), BSN(
        "The object is quite far from shore, and it is impossible"
      + " to get a good look at it here. It looks as if it might"
      + " be nothing more than a tiny island."));
    add_item( ({"tiny island"}), BSN(
        "If it is an island, it cannot be much larger than a"
      + " tree stump."));
    add_item( ({"water", "edge", "surface", "wave", "waves",
                "rippling water"}), BSN(
        "The water of the lake is peaceful and grey. There appears"
      + " to be some sort of object rising out of the water to the"
      + " east. Calm waves lap softly against the bank here."));
    add_item( ({"basin"}), BSN(
        "The basin of Del Rimmon rests quietly among the"
      + " jagged cliffs of the Blackwall Mountains. Ancient tales tell of"
      + " this place. In modern times, few can be said to have"
      + " traveled here."));

    add_cmd_item( ({"object", "tiny island", "island"}),
        ({"search"}), BSN(
        "The object is far out in the water, making it quite"
      + " inaccessable from the lake shore."));

    add_exit(DELRIMMON_DIR + "lakeside/w_shore3","north");
    add_exit(DELRIMMON_DIR + "lakeside/w_shore1","south");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3","northwest",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "You walk a few strides into the lake, and then turn back.\n");
} /* create_lakeshore */
