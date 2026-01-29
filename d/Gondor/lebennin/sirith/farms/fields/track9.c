/*
 * /d/Gondor/lebennin/sirith/farms/track9.c	
 * track in farm community in southern Lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

public void	create_outdoors();

/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_areatype("track");
    set_extraline("A small farmstead is visible through a gate in the hedge "+
	"on the west side of the track, and open pastures stretch east "+
	"and north.");

    add_exit("pasture5", "north", 0, 2, 1);
    add_exit("pasture6", "northeast", 0, 2, 1);
    add_exit("pasture4", "east", 0, 2, 1);
    add_exit("track8", "south", 0, 2);
    add_exit("field9", "southeast", ditch_msg, 3, 1);
    add_exit("../farm2/eastyard", "west", 0, 2, 1);
    add_exit("field8", "southwest", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "northwest" }),
	"You wander along the edge of the track.\n");

    /* directions of exits to fields */
    set_trackdir( ({ "southeast", "southwest" }) );

    set_door(SIRITH_FARMS_DIR + "obj/f2_yard_gate1");
    set_climbdest(SIRITH_FARMS_DIR + "farm2/eastyard");

    /* the only track with no adjacent fields, so do this by hand.
     * if it becomes a general problem, solve it in outdoors.c
     */
    remove_item("crop");
    remove_item("crops");
    remove_item("plant");
    remove_item("plants");

    /* directions in items are hint re non-obvious exits */
    add_item( ({ "field", "fields" }),
	    "Cultivated fields, separated from the track by ditches, "+
	    "lie to the southeast and southwest.");
    add_item( ({ "ditch", "ditches" }),
	    "The ditches are fairly deep, but probably could be crossed "+
	    "with moderate effort.");
    add_item( ({ "pasture", "pastures", "open pasture", "open pastures" }),
	    "Open, grassy pastures stretch away east and north.\n");

    add_item( ({ "building", "buildings", "farm", "farmstead",
		 "farmyard", "yard" }),
	"The farmstead is not large, but from the little you can "+
	    "see through the hedge gate, it appears well-kept.");
    add_item( ({ "hedge" }),
	    "The hedge is thick and fairly tall. A gate in the center "+
	    "leads west into the farmyard.");
    add_item( ({ "heavy timber", "heavy timbers", "timber", "timbers" }),
	    "The heavy timbers of the gate look as if they could withstand "+
	    "a lot of hard use.");
  
} /* create_outdoors */
