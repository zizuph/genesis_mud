/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/sw_cliff2.c
 *
 *  Copyright (c) January 1998, by Cooper Sherry (Gorboth)
 *
 *  Here the cliffs which rim Del Rimmon have begun to run due
 *  east where they will eventually run up against Melan Rath.
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
    set_show_area_desc();

    set_extraline("The southernmost edges of the rim of Del Rimmon"
                + " rise to the south where cliffs loom tall and"
                + " impassable over the trees of the lakeshore. The"
                + " ridge to the east and south seems to run up"
                + " against the sides of Melan Rath.");

    add_item( ({"ridge", "ridges", "side", "sides", }), BSN(
        "The ridge formed by the tall cliffs runs east and northwest"
      + " from here, frowning down over the hillsides. They can be"
      + " seen jutting up against the sides of Melan Rath southeast"
      + " and high above."));
    add_item( ({"hill", "melan rath", }), BSN(
        "The hill of Melan Rath rises to the southeast, peering quietly"
      + " over the ridges of the tall cliffs and seemingly melding"
      + " with their easternmost arm."));

    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2","north",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_shore2","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff1","east");
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2b","northwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff3","west");

    set_no_exit_msg( ({ "southeast", "south", "southwest" }),
        "The cliffs prevent any southern movement from here.\n");
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
