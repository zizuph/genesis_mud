/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_shore3.c
 *
 *  This is the westernmost point of the shoreline of Del Rimmon.
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
    set_show_area_desc();

    set_extraline("The water of the lake reaches perhaps its"
                + " westernmost point here, as the shore proceeds"
                + " in a general north-south direction. A bit to"
                + " the north, a stream is visible running down"
                + " from the hills to flow quietly into Del Rimmon.");

    add_item( ({"stream", "streams"}), BSN(
        "The stream is a ways to the north yet. It meanders its"
      + " way from the trees of the forest to mix with the waters"
      + " of the lake."));

    add_cmd_item( ({"stream", "streams"}),
                   ({"search", "dig", "drink"}), BSN(
        "The stream is still a long way off to the north, and"
      + " quite unaccessable from here."));

    add_exit(DELRIMMON_DIR + "lakeside/w_shore4","north");
    add_exit(DELRIMMON_DIR + "lakeside/w_shore2","south");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4","northwest",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "The lake spreads out before you in all easterly directions.\n");
} /* create_lakeshore */
