/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_cliff2.c
 *
 *  A massive rockslide has occured just south of here, sending debris
 *  trailing into the forest. The cliffs here are nearly due west from
 *  the center of Del Rimmon in the Blackwall Mountains of Emerald.
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public int     climb_rocks();
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("west");

    set_extraline("The cliffs rise high above to the west, towering"
                + " down over the tops of the trees which dominate the"
                + " eastern view. The natural order of things seems"
                + " disturbed to the south, where a great pile of"
                + " debris cuts a path through the area.");

    add_item( ({"high above", "above"}), BSN(
        "Peering up the sides of the cliffs, you think you notice"
      + " a break in the slope, as if a ledge has been carved there."));
    add_item( ({"ledge", "break", "break in the slope"}), BSN(
        "It is high high above, and certainly not within eyeshot of"
      + " any real detail."));
    add_item( ({"eastern view"}), BSN(
        "Trees flow down the slope to the east, blocking visibility"
      + " of most things in that direction."));
    add_item( ({"pile", "great pile", "great pile of debris",
                "debris", "pile of debris"}), BSN(
        "The pile of debris to the south appears to be the aftermath"
      + " of a rockslide, which sent many tons of rock spilling"
      + " forth into the forest."));
    add_item( ({"rockslide", "tons of rock",
                "many tons of rock"}), BSN(
        "The rockslide is still a ways to the south. Travelling"
      + " in that direction would certainly require a bit of a"
      + " climb to traverse the piled debris."));
    add_item( ({"wall", "rocky wall", "piled debris"}), BSN(
        "The debris to the south have formed a rocky wall which"
      + " extends into the forest."));

    add_cmd_item( ({"wall", "rocky wall", "debris", "pile",
                    "great pile", "great pile of debris",
                    "pile of debris", "rockslide", "tons of rock",
                    "many tons of rock",}), 
                  ({"get", "search", "climb"}), BSN(
        "The rockslide is too far away to do that."));

    add_exit(DELRIMMON_DIR + "lakeside/w_cliff3","north");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2b","east",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1b","southeast",0,1,1);
    /* Extra fatigue here for climbing over the rockslide */
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff1","south",climb_rocks,4);

    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "The cliffs block your progress in that direction.\n");
} /* create_cliff_room */

/*
 * Function name : climb_rocks
 * Description   : print a message telling the player that they had
 *                 to do some climbing to go in this direction.
 * Arguments     : none
 * Returns       : 0
 */
public int
climb_rocks()
{
    write(BSN("Traveling a bit to the south, you are forced to climb over"
        + " a massive mound of rocks and boulders."));

    return 0;
} /* climb_rocks */
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
