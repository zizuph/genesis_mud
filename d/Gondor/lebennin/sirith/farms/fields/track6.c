/*
 * /d/Gondor/lebennin/sirith/farms/track6.c	
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
    set_extraline("Open fields lie beside the track to the east. "+
	"On the west side of the track, a heavy gate leads into "+
	"a large farmstead that is enclosed "+
	"by a ditch and further fortified by a turf bank.");


    add_exit("track7", "north", 0, 2);
    add_exit("field7", "northeast", ditch_msg, 3, 1);
    add_exit("field5", "east", ditch_msg, 3, 1);
    add_exit("field4", "southeast", ditch_msg, 3, 1);
    add_exit("track5", "south", 0, 2);
    add_exit("field3", "southwest", ditch_msg, 3, 1);
    add_exit("../farm1/eastyard", "west", 0, 2, 1);
    add_exit("field6", "northwest", ditch_msg, 3, 1);

    /* directions of exits to fields */
    set_trackdir( ({ "east", "northeast", "southeast",
	"northwest", "northwest" }) );

    set_door(SIRITH_FARMS_DIR + "obj/f1_yard_gate1");
    set_climbdest(SIRITH_FARMS_DIR + "farm1/eastyard");

    add_item( ({ "building", "buildings", "farm", "farmstead" }),
	BSN("The farmstead is large and appears quite prosperous, "+
	    "but the bank surrounding it blocks most of your view."));
    add_item( ({ "ditch", "ditches" }),
	BSN("The western ditch is about three feet deep, and completely "+
	    "surrounds the farmstead. Planks have been laid "+
	    "across the ditch to form a rough bridge. The ditch to "+
	    "the east is equally deep, and probably serves to keep "+
	    "livestock out of the crops"));
    add_item( ({ "bridge", "plank", "planks" }),
	"Several planks form a bridge across the ditch.\n");
    add_item( ({ "bank", "turf" }),
	BSN("Inside the ditch runs a solid turf bank, which blocks "+
	    "much of your view. A gate in the center of the "+
	    "bank, facing the path, allows access to the farmstead."));
    add_item( ({ "heavy timber", "heavy timbers", "timber", "timbers" }),
	BSN("The heavy timbers of the gate look as if they could withstand "+
	    "a lot of hard use."));
} /* create_outdoors */
