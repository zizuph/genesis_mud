/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/sw_cliff1.c
 *
 *  The southeastern-most cliff faces run up against the sides
 *  of Melan Rath here. The lakeshore is to the northeast, and the
 *  slopes of Melan Rath are to the southeast.
 *
 *  Copyright (c) December 1997 by Cooper Sherry (Gorboth)
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

    set_extraline("The sheer rock walls of the cliffs which fence"
                + " the basin of Del Rimmon rise to meld with"
                + " the western flanks of Melan Rath here, which tower"
                + " high above to shoulder against its slopes to the"
                + " southeast.");

    add_item( ({"flanks", "western flanks"}), BSN(
        "To the southeast, the western flanks of Melan Rath are visible"
      + " as they ride up against and merge with the cliffs which"
      + " ring the entire region."));
    add_item( ({"slope", "slopes"}), BSN(
        "The slopes which rim the lake have run up against sheer"
      + " which form the southwestern edge of the basin in which"
      + " Del Rimmon rests here in the Blackwall Mountains."));
    add_item( ({"melan rath", "hill", "hills"}), BSN(
        "Melan Rath is visible rising beside the cliff faces to the"
      + " southeast. Trees are visible mounting one head above the"
      + " next toward the summit, where the green swath of pines"
      + " suddenly fails."));
    add_item( ({"summit", "top", "hilltop", "top of the hill"}), BSN(
        "The summit of Melan Rath to the southeast appears to be"
      + " devoid of trees."));
    add_item( ({"swath", "swath of pine trees", "pine", "pines",
                "pine tree", "pine trees"}), BSN(
        "Pine trees are visible growing upon Melan Rath. Climbing"
      + " towards the summit, they fail suddenly, leaving the"
      + " hilltop cold-gleaming against the sky."));

    add_exit(DELRIMMON_DIR + "lakeside/sw_shore2","north",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_shore1","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff2","west");
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2","northwest",0,1,1);

    set_no_exit_msg( ({ "southwest", "south" }),
        "The cliff walls block your progress.\n");
    set_no_exit_msg( ({ "southeast", "east" }),
        "The slopes of Melan Rath rise steeply in that direction,"
      + " blocking your progress.\n");
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
