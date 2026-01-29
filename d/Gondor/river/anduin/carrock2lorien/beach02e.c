/*
 * /d/Gondor/river/anduin/lorien2rauros/beach02e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * east shore of the anduin, 30 miles north of old forest rd
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(CARROCK_TO_LORIEN_DIR + "river02")


/* prototypes */
public void	create_shore_room();
public int	move_msg();


/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    string	*herbslist;

    set_short("grassy riverbank");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"Green grasses, tipped with golden seedheads, stretch east from " +
	"the Anduin as far as the eye can see.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("riverbank");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    set_drink_from( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }) );

    add_exit("fishcamp_s", "north", move_msg, 3);
    add_exit("river02", "west", 0, 2, 1);
    add_exit("old_road_east", "south", move_msg, 3);
    set_no_exit_msg( ({ "northwest", "southwest" }),
	BSN("You wander among the tall grasses of the riverbank."));
    set_no_exit_msg( ({ "northeast", "east", "southeast", }),
	BSN("You head inland, but the grasses all look alike and " +
	    "you soon become disoriented. You return to the riverbank."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", "waters", "water", }),
	&exa_water(RIVER,
	    BSN("At the edge of the grasses, the Anduin flows south. " +
		"Its waters are wide and swift and quite silent.")));

    add_item( ({ "edge", }),
	BSN("The grasses grow up to the very edge of the river."));
    add_item( ({ "western bank", "west bank", "far shore", "far side",
	"far side of river", "western shore", "west shore" }),
	BSN("From this distance, all that can be seen across the Anduin " +
	    "is wide green grassland."));
    add_item( ({ "this shore", "this side", "this side of river",
	"inland", "bank", "riverbank", "river bank",
	"shore", "shores", "eastern bank", "east bank", "eastern shore",
	"east shore" }),
	BSN("The east shore is blanketed with tall gold-flecked grass."));
    add_item( ({ "tall grass", "tall grasses", "green grasses",
	"green grass", "tall gold-flecked grasses",
	"tall gold-flecked grass", "gold-flecked grasses",
	"gold-flecked grass", "grasses", "grass", }),
	BSN("The grasses are green save for their very tips, where " +
	    "golden seedheads dance in the breeze."));
    add_item( ({ "tip", "tips", "golden seedhead", "golden seedheads",
	"cluster", "clusters", "fleck", "flecks", "seedhead", "seedheads", }),
	BSN("Clusters of seeds tip the grasses with flecks of gold."));
    add_item( ({ "earth", "ground" }),
	BSN("The grasses grow thickly to cover the earth."));

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
	WRITE("You follow the riverbank to the north, where " +
	    "the grasses give way to a sandy beach.");
	break;
    case "south":
	WRITE("You trudge south along the river. After some " +
	    "distance, you emerge onto a little-used track.");
	break;
    }
    return 0;
} /* move_msg */
