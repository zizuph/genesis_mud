/*
 * /d/Gondor/lebennin/sirith/farms/farm2/westyard.c
 * west yard of small farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

public void	create_outdoors();
public void	init();


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_areatype("farmyard");
    set_short("a hedged farmyard in southern Lebennin");
    set_extraline("A weathered barn and shed stand to the north "+
	"and west, while a simple wooden door leads into "+
	"the farmhouse to the south. At the eastern end of the "+
	"farmyard are trees and a garden.");

    add_exit("barn", "north", 0, 2);
    add_exit("eastyard", "east", 0, 2);
    add_exit("house", "south", 0, 2, 1);
    add_exit("shed", "west", 0, 2);
    set_door(SIRITH_FARMS_DIR + "obj/f2_house_door1");
    set_no_exit_msg( ({ "northeast", "southeast",
	"southwest", "northwest", "up", "down" }),
	BSN("You walk around the farmyard.") );

    add_item( ({ "farmyard", "farm", "yard" }),
	BSN("The well-tended farmyard is circled by a dense hedge. "+
	    "The buildings, garden and trees all appear to be in good shape."));
    add_item( ({ "dense hedge", "hedge" }),
	BSN("The hedge, which is quite thick, encloses the entire "+
	    "farmyard."));
    add_item( ({ "tree", "trees", "fruit tree", "fruit trees" }),
	BSN("Low trees grow in the northeast corner of the farmyard."));
    add_item( ({ "garden", "vegetable garden" }),
	BSN("The garden occupies the southeast corner of the farmyard."));
    add_item( ({ "building", "buildings" }),
	BSN("The small barn, shed, and farmhouse are all "+
	    "built of weathered grey planking and are apparently "+
	    "in good condition."));
    add_item( ({ "weathered barn", "barn" }),
	BSN("The barn is not large, but appears well-built. Its "+
	    "wooden walls have weathered to a soft silver grey."));
    add_item( ({ "house", "farmhouse" }),
	BSN("The farmhouse, built of weathered planking, "+
	    "is topped by a shaggy thatch roof."));
    add_item( ({ "thatched roof", "thatch", "roof" }),
	BSN("The thatch, although shaggy, appears to be in good condition."));
    add_item( ({ "shed" }),
	BSN("The shed is built of grey weathered planking."));
    add_item( ({ "plank", "planks", "planking" }),
	BSN("Time and weather have turned the planks a soft silver "+
	    "grey."));
    add_item( ({ "ground", "dirt" }),
	BSN("The ground is just bare dirt."));

} /* create_outdoors */


/*
 * Function name:	init
 * Description	:	load the farmhouse
 *
 * for some reason, players who enter a house that has both a door and an
 * npc are moved without doing 'look'. i suspect that this_player() is
 * getting munged somewhere, but i don't have time to try to track it down
 * right now. in the meantime, if i load the house from here, all is well.
 */
public void
init()
{
    ::init();
    (SIRITH_FARMS_DIR+"farm2/house")->short();
} /* init */
