/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_shore2.c
 *
 *  The lakeshore of Del Rimmon is nearing its northernmost
 *  point here, curving to the east to meet with the sides
 *  of the sheer cliffs of the Blackwall Mountains in that direction.
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
    set_side("northwest");

    set_extraline("The lakeshore of Del Rimmon is near its"
                + " northernmost point here, leading towards the"
                + " towering cliffs of the Blackwall Mountains to the east,"
                + " and curving towards the western region of the"
                + " lake to the southwest.");

    add_item( ({"towering cliffs"}), BSN(
        "The cliffs of the Blackwall Mountains surround this entire region."
      + " Directly to the north, above the tops of the trees, the"
      + " cliffs curve slowly around to border the shoreline to the"
      + " direct east, where the sheer walls of stone seem to halt"
      + " movement in that direction."));
    add_item( ({"walls", "walls of stone", "sheer walls", "stone walls",
                "sheer walls of stone"}), BSN(
        "The cliffs do indeed seem sheer to the east. They are undercut"
      + " in places, making climbing difficult for even the most"
      + " cunning expert."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3","north",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff7","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore3","east");
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore1","southwest");
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3b","northwest",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "southeast", "south" }),
        "You ponder briefly the merits of plunging into the lake water,"
      + " and decide against it.\n");
} /* create_lakeshore */
