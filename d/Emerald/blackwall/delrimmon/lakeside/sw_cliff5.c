/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/sw_cliff5.c
 *
 *  Copyright (c) January 1997, by Cooper Sherry (Gorboth)
 *
 *  The cliffs which surround Del Rimmon are approaching their most
 *  westward point from the south here.
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

    set_extraline("The ridge of cliffs which rings the lake approaches"
                + " its westernmost rim as it runs north of here."
                + " Debris are visible beneath the cliffs in that"
                + " direction. To the east the slopes run gradually"
                + " down to meet with the shores of the lake.");

    add_item( ({"ridge", "ridges", "ridge of cliffs"}), BSN(
        "The ridges which form the bowl of Del Rimmon run as sheer"
      + " cliff faces to the northwest and southeast of here."));
    add_item( ({"rim", "westernmost rim", "rims"}), BSN(
        "A ways to the northwest, the rim of cliffs reaches its"
      + " most westward point, and can be seen turning once again"
      + " to angle east. There appear to be some debris below the"
      + " cliffs in that direction."));
    add_item( ({"debris", "pile", "pile of debris"}), BSN(
        "From here, the debris are too distant to see clearly. They"
      + " appear to have fallen from high above."));

    add_exit(DELRIMMON_DIR + "lakeside/w_cliff1","northwest");
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff4","southeast");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1b","north",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3b","east",0,1,1);

    set_no_exit_msg( ({ "south", "southwest", "west" }),
        "The cliffs prevent any movement to the south or west.\n");
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
