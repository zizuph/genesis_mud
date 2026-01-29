/*
 * /d/Gondor/lebennin/sirith/farms/farm1/westyard.c
 * west yard of large farmstead in southern lebennin
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
    set_areatype("farmyard");
    set_short("a farmyard in southern Lebennin");
    set_extraline("A large barn lies north, and a house "+
	"and garden are visible through an opening in the hedge to "+
	"the south. Between the hedge and the barn stands a "+
	"weather-beaten shed.");

    add_exit("barn1", "north", 0, 2);
    add_exit("eastyard", "east", 0, 2);
    add_exit("hedgeyard", "south", 0, 2);
    add_exit("shed", "west", 0, 2);
    set_no_exit_msg( ({ "northeast", "southeast",
	"southwest", "northwest", "up", "down" }),
	BSN("You stroll around the farmyard.") );

    add_item( ({ "farm", "farmyard", "yard" }), 
	BSN("A large farmyard, ringed by a turf bank. Barn, "+
	    "hedge, and bank all seem to be in good repair."));
    add_item( ({ "bank", "turf", "turf bank" }),
	BSN("Blocks of turf are stacked tightly "+
	    "together to form a bank around the farmyard."));
    add_item( ({ "buildings", "building" }),
	BSN("The barn and shed are quite close, and "+
	    "a house lies beyond the hedge."));
    add_item( ({ "large barn", "barn", "plank", "planks" }),
	BSN("The barn is built of silver grey planks, and "+
	    "appears to be well-maintained."));
    add_item( ({ "weather-beaten", "shed" }),
	BSN("The weather-beaten shed is fairly small."));
    add_item( ({ "ground", "dirt" }),
	BSN("Bare, packed dirt is underfoot."));
    add_item( ({ "thick hedge", "hedge", "opening" }),
	BSN("A thick hedge encloses "+
	    "the southern portion of the farmyard. An opening in "+
	    "the hedge gives a glimpse of a house and garden."));
    add_item( ({ "house", "garden" }),
	BSN("The house and garden are just visible through the hedge; "+
	    "you cannot see details."));
} /* create_outdoors */
