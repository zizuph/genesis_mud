/*
 *  /d/Emerald/blackwall/delrimmon/lakeshore/pathway3.c
 *
 *  The pathway leading into the Valley of Del Rimmon travels
 *  down a wooded hillside here, approaching the southermost
 *  shores of the lake.
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_tree_room();


/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
public void
create_tree_room()
{
    set_loc(2);
    set_side("south");
    set_show_area_desc();

    set_extraline("The path travels down through the wooded"
      + " hillside here, twisting this way and that to avoid"
      + " the many trees which are scattered along the slope.");

    add_item( ({ "shore", "shores", "lakeshore", "lake shore",
                 "lakeshores", "lake shores", "shore of the lake",
                 "shores of the lake" }),
        "A ways to the north, what appear to be the shores of"
      + " a lake are visible through the trees.\n");
    add_item( ({ "dropoff", "steep dropoff" }),
        "A steep dropoff prevents movement to the west.\n");
    add_item( ({ "thicket", "thickets", "dense thicket",
                 "dense thickets" }),
        "Dense thickets crowd the path to the east.\n");
    add_item( ({ "ground", "down" }),
        "The ground is grassy and covered with patchy mosses and"
      + " undergrowth amongst the many tree trunks. A path winds its"
      + " way along the ground, heading north and south.\n");
    add_item( ({ "path", "pathway" }),
        "The pathway at your feet is so overgrown and choked by"
      + " mosses and undergrowth that it is hardly recognizable."
      + " It looks as if it has not seen much travel in the past"
      + " few hundred years. It leads up the slope to the south,"
      + " to disappear over a rise where the cliffs block out"
      + " the trees. To the north, it seems to wind down to"
      + " the shores of a lake.\n");

    add_exit(DELRIMMON_DIR + "lakeside/sw_shore1", "north", 
             check_sitting);
    add_exit(DELRIMMON_DIR + "lakeside/pathway2", "south", 
             check_sitting);

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "Dense thickets prevent your movement in that direction.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "The hillside is interrupted by a steep dropoff in that"
      + " direction.\n");

    add_view();
} /* create_tree_room */


/*
 * Function name:        reset_room
 * Description  :        allow herbs to be found again
 *                       at resets
 */
public void
reset_room()
{
    set_searched(- random(3));
} /* reset_room */
