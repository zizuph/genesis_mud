/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_cliff3.c
 *
 *  A large hole undercuts the cliff face here along the western
 *  slopes of the hills which border Del Rimmon in the Blackwall Mountains
 *  of Emerald.
 *
 *  Copyright (c) April 1998, by Cooper Sherry (Gorboth)
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
 * Description  : Allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("west");

    set_extraline("The cliff directly to the west is undercut by a"
                + " great depression in the rock wall. Growing"
                + " almost to the very spot where the rock faces"
                + " climb upwards, a few trees have managed to"
                + " exist apart from the forest to the east.");

    add_item( ({"depression", "great depression"}), BSN(
        "Whether by wind or some unknown force of nature, the"
      + " cliff face directly to the west has been worn back so"
      + " that it is undercut by a great depression in the rock."
      + " The gaping hole rises many dozens of feet above the"
      + " ground, and is as wide as a large house."));
    add_item( ({"hole", "gaping hole"}), BSN(
        "It seems unlikely that wind could have made such"
      + " a large depression in the cliff face, yet there"
      + " are no signs that it was made by anything unnatural."));
    add_item( ({"faces", "rock faces", "wall", "rock wall"}), BSN(
        "The cliff face directly to the west has been undercut"
      + " by a great depression in the rock which rises to a"
      + " vast height above the ground."));
    add_item( ({"few trees", "nearby trees"}), BSN(
        "These trees seem to have somehow grown apart from the"
      + " greater part of the forest which covers the hillsides"
      + " which climb down toward the lake."));

    add_exit(DELRIMMON_DIR + "lakeside/w_cliff4","north");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4b","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b","east",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2b","southeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff2","south");

    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "The towering cliffs prevent any movement in that direction.\n");
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
