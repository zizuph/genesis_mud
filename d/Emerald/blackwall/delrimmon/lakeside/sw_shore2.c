/*
 *  /d/Gondor/emyn_muil/lakeside/parth2.c
 *
 *  Some grasses from the Parth Galen extend here along the shore
 *  line of Del Rimmon's western edge as one travels west and
 *  northwest along the water.
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
    set_side("southwest");
    set_show_area_desc();

    set_extraline("Breaking now and again between pebbled beaches"
                + " and muddy embankments, the shore travels to"
                + " the east and northwest here along the edge of"
                + " the lake. To the east, a green lawn is visible.");

    add_item( ({"embankment", "embankments", "muddy embankment",
                "muddy embankments"}), BSN(
        "The embankments along the edge of the lake are cut rather"
      + " low to the surface of the water, allowing, in many places,"
      + " a more gradual shoreline to extend towards the lake, often"
      + " covered with pebbles."));
    add_item( ({"lawn", "lawns", "green lawn", "green lawns"}), BSN(
        "To the east, the shore is blanketed with lush green grasses"
      + " which appear to be growing to the very edge of the lake."));


    add_exit(DELRIMMON_DIR + "lakeside/sw_shore1","east");
    add_exit(DELRIMMON_DIR + "lakeside/sw_shore3","northwest");
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff1","south",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff2","southwest",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "southeast" }),
        "A steep rise bars your movement in that direction.\n");
    set_no_exit_msg( ({ "north", "northeast" }),
        "You wade into the lake for a few feet, and then return to"
      + " the shore.\n");
} /* create lakeshore */
