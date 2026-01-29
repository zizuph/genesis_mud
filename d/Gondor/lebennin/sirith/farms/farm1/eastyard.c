/*
 * /d/Gondor/lebennin/sirith/farms/farm1/eastyard.c
 * east yard of large farmstead in southern lebennin
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


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_areatype("farmyard");
    set_short("a large farmyard in southern Lebennin");
    set_extraline("A turf bank, pierced by a gate to the east, "+
	"surrounds the entire yard. "+
	"North and west are various sheds, hayricks and a barn; "+
	"a thick hedge "+
	"encloses most of the southern portion of the farmyard. "+
	"A little to the south is a small fenced enclosure, between "+
	"the hedge and the turf bank. ");

    add_exit("northyard", "north", 0, 2);
    add_exit("../fields/track6", "east", 0, 2);
    add_exit("southyard", "south", 0, 2);
    add_exit("westyard", "west", 0, 2);
    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
	"northwest", "up", "down" }),
	BSN("You wander around the farmyard.") );

    set_door(SIRITH_FARMS_DIR + "obj/f1_yard_gate2");
    set_climbdest(SIRITH_FARMS_DIR + "fields/track6");

    add_item( ({ "farm", "farmyard", "yard" }), 
	BSN("The large farmyard is ringed by a turf bank. Buildings, "+
	    "hedge, bank and fencing all seem to be in good repair."));
    add_item( ({ "blocks", "blocks of turf", "bank", "turf", "turf bank" }),
	BSN("The bank, formed of blocks of turf stacked tightly "+
	    "together, is about head-high. A fairly deep ditch, "+
	    "bridged by planks, is visible through a gated "+
	    "opening in the eastern bank."));
    add_item( ({ "ditch", "opening", "bridge", "plank", "planks" }),
	BSN("Just beyond the farm gate, rough planks bridge a three-foot "+
	    "ditch."));
    add_item( ({ "hedge", "thick hedge" }),
	BSN("The hedge, which is quite thick, encloses most "+
	    "of the southern portion of the farmyard."));
    add_item( ({ "building", "buildings" }),
	BSN("A large shed is directly north, and a good-sized barn fills "+
	    "the northwest corner of the yard. A smaller shed "+
	    "stands to the west between the barn and the hedge."));
    add_item("barn",
	BSN("The barn in the northwest corner of the yard is fairly "+
	    "large and appears to be very soundly built."));
    add_item( ({ "shed", "sheds" }),
	BSN("A large shed is directly north, and a smaller shed "+
	    "stands to the west between the barn and the hedge."));
    add_item( ({ "north shed", "large shed", "larger shed", "smokehouse" }), 
	BSN("The north shed is built of stout logs, tightly caulked."));
    add_item( ({ "log", "caulk", "caulking", "logs" }),
	BSN("The logs of the north shed are well caulked."));
    add_item( ({ "hayricks", "hayrick", "hay" }),
	BSN("Hay is stacked between the larger shed and the barn."));
    add_item( ({ "small shed", "smaller shed",  "west shed" }),
	BSN("The shed to the west is quite small."));
    add_item( ({ "fenced enclosure", "fencing", "fence", "enclosure" }),
	BSN("Sturdy fencing forms an enclosure to the south, "+
	    "between the hedge and the turf bank."));
    add_item( ({ "heavy timber", "heavy timbers", "timber", "timbers" }),
	BSN("The heavy timbers of the gate look as if they could withstand "+
	    "a lot of hard use."));
    add_item( ({ "ground", "dirt" }),
	BSN("The ground is just bare dirt."));
} /* create_outdoors */
