/*
 * /d/Gondor/lebennin/sirith/farms/farm1/hedgeyard.c
 * hedged yard in large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * Finwe,May 2019: Removed hidden exits
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
    set_short("a farmyard in southern Lebennin");
    set_extraline("The farmyard is edged by squat trees to the south "+
	"and a garden to the east. To the west is a stone farmhouse, "+
	"with a low thatch roof and a wooden door.");

    add_exit("westyard", "north", 0, 2);
    add_exit("trees", "south", 0, 2);
    add_exit("garden", "east", 0, 2);
    add_exit("house", "west", 0, 2);
    set_no_exit_msg( ({ "northeast", "southeast",
	"southwest", "northwest", "up", "down" }),
	BSN("You stroll around the farmyward.") );

    set_door(SIRITH_FARMS_DIR + "obj/f1_house_door1");

    add_item( ({ "farm", "farmyard", "yard" }), 
	BSN("A tidy farmyard, ringed by a sturdy hedge."));
    add_item( ({ "buildings", "building" }),
	BSN("The farmhouse is directly west, and you can just "+
	    "glimpse a barn through an opening in the hedge "+
	    "to the north."));
    add_item( ({ "barn", "opening" }),
	BSN("A barn is just visible through the opening in the hedge."));
    add_item( ({ "ground", "dirt" }),
	BSN("Bare, packed dirt is underfoot."));
    add_item( ({ "hedge" }),
	BSN("The hedge is thick and fairly tall."));
    add_item( ({ "stone house", "stone farmhouse", "house", "farmhouse" }),
	BSN("The farmhouse is built of brown river stones and has a "+
	    "thatch roof. It looks snug and prosperous."));
    add_item( ({ "speckled brown stone", "speckled brown stones", 
		 "speckled stone", "speckled stones", "brown stone",
		 "brown stones", "stone", "stones", "river stone",
		 "river stones" }),
	BSN("The speckled brown stones are very smooth."));
    add_item( ({ "low roof", "thatch roof", "thatch", "roof" }),
	BSN("The thatch is in excellent repair."));
    add_item( ({ "thriving garden", "garden" }),
	BSN("A thriving garden runs along the hedge to the east."));
    add_item( ({ "tree", "trees", "fruit tree", "fruit trees",
		 "squat tree", "squat trees" }),
	BSN("The trees, which are not very tall, appear to be fruit "+
	    "trees, but you cannot be sure from here."));
}

/*
 * Function name:	init
 * Description	:	force load of house
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
    (SIRITH_FARMS_DIR+"farm1/house")->short();
} /* init */
