/*
 * /d/Gondor/lebennin/sirith/farms/farm2/eastyard.c
 * east yard of small farmstead in southern lebennin
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
    set_short("a hedged farmyard in southern Lebennin");
    set_extraline("Small trees grow to the north, "+
	"a vegetable garden stretches south, "+
	"and various weathered buildings are to the west. "+
	"A gate in the hedge leads east out of the farmyard.");

    add_exit("trees", "north", 0, 2);
    add_exit("../fields/track9", "east", 0, 2, 1);
    add_exit("garden", "south", 0, 2);
    add_exit("westyard", "west", 0, 2);
    set_no_exit_msg( ({ "northeast", "southeast",
	"southwest", "northwest", "up", "down" }),
	BSN("You stroll around the farmyard.") );

    set_door(SIRITH_FARMS_DIR + "obj/f2_yard_gate2");
    set_climbdest(SIRITH_FARMS_DIR + "fields/track9");

    add_item( ({ "farmyard", "farm", "yard" }),
	BSN("The well-tended farmyard is circled by a dense hedge. "+
	    "Buildings, garden and trees all "+
	    "appear to be in good shape."));
    add_item( ({ "hedge" }),
	BSN("The hedge, which is quite thick, encloses the entire "+
	    "farmyard."));
    add_item( ({ "fruit tree", "fruit trees", "small tree", "squat tree",
    	"twiggy tree", "small trees", "squat trees", "twiggy trees",
    	"tree", "trees", }),
	BSN("The squat, twiggy trees appear to be fruit trees of some "+
	    "kind. There are round lumps in the grass beneath the trees."));
    add_item( ({ "grass", "grasses" }),
	BSN("Short, broad-bladed grasses grow thickly beneath the trees. "+
	    "Round lumps are scattered about the grass."));
    add_item( ({ "shape", "shapes", "lump", "lumps" }),
	BSN("From here, all you can see are low, round shapes "+
	    "in the grass."));
    add_item( ({ "garden", "vegetable garden", "vegetables" }),
	BSN("The vegetable garden occupies a good part of the farmyard "+
	    "to the south."));
    add_item( ({ "weathered building", "weathered buildings",
    		 "building", "buildings" }),
	BSN("The buildings include a small house, a barn and a couple of "+
	    "sheds."));
    add_item( ({ "house", "farmhouse" }),
	BSN("A simple, sturdy farmhouse built of river stones, with a "+
	    "shaggy thatch roof, occupies the southwest corner of "+
	    "the farmstead."));
    add_item( ({ "thatch", "roof" }),
	BSN("The thatch, although shaggy, appears to be in good condition."));
    add_item( ({ "barn" }),
	BSN("A small barn, built of vertical planks weathered "+
	    "to a silvery grey, lies to the northwest."));
    add_item( ({ "shed", "small shed", "larger shed", "sheds" }),
	BSN("There is a small shed to the west of the garden "+
	    "and a larger shed directly west, between the farmhouse "+
	    "and the barn."));
    add_item( ({ "timber", "timbers" }),
	BSN("The heavy timbers of the gate look as if they could withstand "+
	    "a lot of hard use."));
    add_item( ({ "ground", "dirt" }),
	BSN("The ground is just bare dirt."));

    add_cmd_item( ({ "shape", "shapes", "lump", "lumps" }),
	({ "search", "get", "take" }),
	BSN("You'll need to be closer to do that."));
} /* create_outdoors */
