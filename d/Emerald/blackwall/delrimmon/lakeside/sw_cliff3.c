/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/sw_cliff3.c
 *
 *  Here the cliffs along the southwestern rim of Del Rimmon in
 *  the Blackwall Mountains of Emerald jog northwest and east.
 * 
 *  Copyright (c) July 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("southwest");

    set_extraline("The long line of cliffs curves markedly here,"
                + " framing the sloping hillsides of the lakeshore."
                + " Northwest, the ridge travels in a gradual arc"
                + " which traces the boundaries of the lake. Somewhat"
                + " to the east, the peak of a hill is visible.");

    add_item( ({"line", "long line", "line of cliffs",
                "long line of cliffs", "ridge", "ridges",}), BSN(
        "The cliffs run in a gradual curve here, a wide tumbled"
      + " flat of scored and weathered rock."));
    add_item( ({"hillside", "hillsides", "sloping hillside",
                "sloping hillsides",}), BSN(
        "The hills which travel from the lakeshore to the bare"
      + " cliffs are steeper in some places than in others. They"
      + " make their way gradually around the curvature of the"
      + " water which lies shouded by the many treetops below."));
    add_item( ({"peak", "peaks", "peak of a hill", "hill", "hilltop",
                "melan rath",}), BSN(
        "Almost due east and a ways off the peak of Melan Rath is visible"
        + " rising to meet with the cliffs which ring the area."));

    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2b","north",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff2","east");
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff4","northwest");

    set_no_exit_msg( ({ "southeast", "south", "southwest", "west" }),
        "The cliffs prevent movement in that direction.\n");
} /* create_cliff_room */
/*
 * Function name: init
 * Description  : Add actions to the player.
 */
public void
init()
{
    ::init();

    add_action(em_climbing_hook, "climb");
} /* init */
