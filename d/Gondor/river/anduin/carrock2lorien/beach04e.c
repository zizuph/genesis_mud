/*
 * /d/Gondor/river/anduin/lorien2rauros/beach04e.c
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

#define	RIVER	(CARROCK_TO_LORIEN_DIR + "river04")


/* prototypes */
public void	create_shore_room();
public int	move_msg();


/*
 * Function name:	create_shore_room
 * Description	:	set up the riverbank
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
	"Tall grasses, speckled with wildflowers, grow thickly " +
	"alongside the river.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("beach");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_exit("old_road_east", "north", move_msg, 3);
    add_exit("river04", "west", 0, 2, 1);
    add_exit("beach05e", "south", move_msg, 3);
    set_no_exit_msg( ({ "northwest", "southwest", }),
	BSN("You wander along the water's edge for a bit."));
    set_no_exit_msg( ({ "northeast", "east", "southeast", }),
	BSN("You roam among the grasses for a while, then " +
	    "return to the riverbank."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", "dark waters", "dark water", "waters",
	"water", }),
	&exa_water(RIVER,
	    BSN("The dark waters of the Great River flow south " +
		"past the riverbank. They appear deep and " +
		"quite swift.")));

    add_item( ({ "western bank", "west bank", "far shore", "far side",
	"far side of river", "western shore", "west shore" }),
	BSN("The far shore is cloaked with tall grasses apparently " +
	    "identical to those growing here, though at this distance " +
	    "it is hard to be sure."));
    add_item( ({ "this shore", "this side", "this side of river",
	"landscape", "shore", "shores", "eastern bank", "east bank",
	"eastern shore", "east shore" }),
	BSN("Tall grasses stretch east from the river, seemingly " +
	"without end."));
    add_item( ({ "thick grass", "thick grasses", "tall grass",
	"tall grasses", "grasses", "grass", }),
	BSN("The grass is tall and thick, making movement difficult. " +
	    "Bright wildflowers are scattered among the grasses, " +
	    "adding dots of colour to the green landscape."));
    add_item( ({ "bright flower", "bright wildflower", "bright flowers",
	"bright wildflowers", "flower", "wildflower", "flowers",
	"wildflowers", }),
	BSN("The flowers, small but brightly hued, grow scattered " +
	    "among the grasses."));
    add_item( ({ "bright colour", "bright colours", "colour", "colours",
	"dots", "dots of colour" }),
	BSN("The bright colours of the flowers are a vivid constrast " +
	    "to the green grasses."));
    add_item( ({ "earth", "ground" }),
	BSN("No earth is visible beneath the thick grass."));

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
 * Function name:	move_msg
 * Description	:	do some you-move atmospheric msgs
 * Returns	:	int -- 0 (exit always allowed)
 */
public int
move_msg()
{
    switch(QVB)
    {
    case "north":
	WRITE("You follow the riverbank north. Eventually, you " +
	    "emerge onto a grassy track.");
	break;
    case "south":
	WRITE("You trudge south along the riverbank. The grasses " +
	    "spring back up as you pass.");
	break;
    }
    return 0;
} /* move_msg */
