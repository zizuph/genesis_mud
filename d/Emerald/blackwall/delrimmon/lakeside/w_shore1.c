/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_shore1.c
 *
 *  The shore along the western edge of Del Rimmon begins to
 *  curve south southeast here.
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

    set_extraline("The curvature of the shore begins to take a"
                 + " northerly stride here, ringing the lake with"
                 + " its rocky surface.");

    add_item( ({"rocky surface", "rock", "rocks", "pebbled beach"}), BSN(
        "The pebbles of the beach are stewn in their miniature"
      + " assortment around the entire rim of the lake, only"
      + " breaking occasionally where a low bank will interrupt"
      + " its expanse."));
    add_item( ({"low bank"}), BSN(
        "Occasionally a low bank interrupts the pebbled beach"
      + " which rims the lake, scooping down to meet the water"
      + " with its grassy lawn or muddy sides."));
    add_item( ({"grassy lawn", "muddy sides"}), BSN(
        "There are none here, but along the lake, a few can"
      + " be seen in the distance."));
    add_item( ({"curvature"}), BSN(
        "The curvature of the lake is gradual here, heading in a"
      + " rather north-south direction."));

    add_exit(DELRIMMON_DIR + "lakeside/sw_shore3","southeast");
    add_exit(DELRIMMON_DIR + "lakeside/w_shore2","north");
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3","south",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3b","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2","northwest",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "northeast", "east" }),
        "You glance briefly at the lake, and decide it best not to"
      + " try to cross.\n");
} /* create_lakeshore */


