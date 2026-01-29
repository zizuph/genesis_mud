/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood1.c
 *
 *  A wooded area along the western slopes surrounding Del Rimmon
 *  in the Blackwall Mountains of Emerald.
 *
 *  Copyrignt (c) March 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("west");

    set_extraline("The slope of the hillsides runs a ways to the"
                + " north, where the undergrowth appears to run"
                + " somewhat thinner. To the south, dense thickets"
                + " of brambles are visible.");

    add_item( ({"thicket", "thickets",
                "dense thicket", "dense thickets"}), BSN(
        "South of here, the ground becomes crowded with brambles"
      + " which run in dense thickets along the hillside."));
    add_item( ({"bramble", "brambles"}), BSN(
        "The brambles are to the south, and appear to be growing"
      + " quite thickly."));

    add_exit(DELRIMMON_DIR + "lakeside/w_wood2","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore2", "northeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore1","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3b","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff5", "southwest",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1b","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2b", "northwest",
             check_sitting,1,1);
} /* create_tree_room */
