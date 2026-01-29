/*
 * /d/Gondor/river/anduin/lorien2rauros/beach05e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * east shore of the anduin, 50 miles south of old forest road.
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(CARROCK_TO_LORIEN_DIR + "river05")


/* prototypes */
public void	create_shore_room();
public int	check_exit();


/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    string	*herbslist;

    set_short("riverbank");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The riverbank is thick with tall grasses. To the west, " +
	"the Great River flows past.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("riverbank");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_exit("beach04e", "north", check_exit, 3);
    add_exit("river05", "west", check_exit, 2, 1);
    set_no_exit_msg( ({ "southwest",  "northwest", }),
	BSN("You poke around at the edge of the river, but find " +
	"nothing unusual."));
    set_no_exit_msg( ({ "northeast",  "east", "south", "southeast", }),
	BSN("You explore the grasses, but soon lose your way. " +
	    "With some relief, you return to the river."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", "waters", "water", }),
	&exa_water(RIVER,
	    BSN("The waters are wide and dark, and very swift. " +
		"They are not inviting.")));

    add_item( ({ "western bank", "west bank", "far shore", "far side",
	"far side of river", "western shore", "west shore" }),
	BSN("The west shore is quite distant. Tall grass is all that " +
	    "is visible from here."));
    add_item( ({ "this shore", "this side", "this side of river",
	"shore", "shores", "eastern bank", "east bank", "eastern shore",
	"east shore" }),
	BSN("Tall grasses grow thickly along the river, making " +
	    "passage difficult. It is impossible to see very far."));
    add_item( ({ "thick grass", "thick grasses", "tangled grass",
	"tangled grasses", "tall grass", "tall grasses",
	"grasses", "grass", }),
	BSN("The grasses grow thick and tangled, making it difficult " +
	    "to move about."));
    add_item( ({ "earth", "ground" }),
	BSN("The tangled grass completely covers the ground."));

    set_drink_from( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }) );

    herbslist = HERB_MASTER->query_herbs( ({ "moderate", "plains",
					     "middle earth" }) );
    set_up_herbs( ({ ONE_OF_LIST(herbslist), ONE_OF_LIST(herbslist), 
       		     ONE_OF_LIST(herbslist) }),
	    	  ({ "riverbank", "bank", "shore", "ground",
		     "grass", "grasses", }),
		  5);
} /* create_shore_room */


/*
 * Function name:	check_exit
 * Description	:	do nice you-move msgs, and don't let them enter river
 * Returns	:	int --	0 if moving north,
 *				1 if trying to enter river
 */
public int
check_exit()
{
    if (QVB == "north")
    {
	WRITE("You make your way north through the lush grass.");
	return 0;
    }
    WRITE("The river is wide, deep and very swift. You suffer " +
	"a sudden nervous qualm, and decide to remain ashore.");
    return 1;
} /* check_exit */
