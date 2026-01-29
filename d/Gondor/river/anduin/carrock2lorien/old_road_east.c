/*
 * /d/Gondor/river/anduin/lorien2rauros/old_road_east.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * old forest road on the east shore of the anduin
 *
 * XXX add 'listen', since we talk about grasses rustling
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(CARROCK_TO_LORIEN_DIR + "river03")


/* prototypes */
public void	create_shore_room();
public int	move_msg();


/*
 * Function name:	create_shore_room
 * Description	:	set up the track
 */
public void
create_shore_room()
{
    string	*herbslist;

    set_short("track");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"An overgrown track descends west to a wide river, which seems " +
	"just shallow enough to ford. East, the track disappears " +
	"into a wide plain of grass.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("track");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "ford", "great river", "waters", "water", "wide river", 
	 "river", "anduin", "river anduin", "anduin river" }) );

    add_exit("beach02e", "north", move_msg, 3);
    add_exit("river03", "west", 0, 2, 1);
    add_exit("beach04e", "south", move_msg, 3);
    set_no_exit_msg( ({ "northwest", "southwest" }),
	BSN("You wander along the edge of the track, but find nothing " +
	    "of interest."));
    set_no_exit_msg( ({ "east", }),
	BSN("You follow the track east, but it quickly vanishes in " +
	    "the featureless grassland. Baffled, you retrace your steps."));
    set_no_exit_msg( ({ "northeast", "southeast" }),
	BSN("You leave the track for the open plain, but quickly " +
	    "become disoriented. You return to the river."));

    add_item( ({ "old ford", "ford", "great river", "river anduin",
	"anduin river", "anduin", "wide river", "river", "waters", "water", }),
	&exa_water(RIVER,
	    BSN("The river is wide and swift, but sufficiently " +
		"shallow to ford here.")));

    add_item( ({ "overgrown track", "little-used track", "grassy track",
	"track", }),
	BSN("The track is overgrown with grass and apparently undisturbed " +
	    "by much traffic."));
    add_item( ({ "western bank", "west bank", "far shore", "far side",
	"far side of river", "western shore", "west shore" }),
	BSN("On the far side of the river, the track continues west " +
	    "across a wide grassland."));
    add_item( ({ "wide flat plain", "wide plain", "flat plain", 
	"plain", "wide grassland", "grassland" }),
	BSN("The Anduin flows through the center of a wide flat " +
	    "plain of grass."));
    add_item( ({ "this shore", "this side", "this side of river",
	"inland", "bank", "riverbank", "river bank",
	"shore", "shores", "eastern bank", "east bank", "eastern shore",
	"east shore" }),
	BSN("Flat grassland extends away from the river. Far to " +
	    "the east, a black wall of trees is just visible."));
    add_item( ({ "tall grass", "tall grasses",
	 "green grasses", "green grass", "grasses", "grass", }),
	BSN("Off the track, the grass is easily waist-high. It " +
	    "rustles softly in the lightest breeze."));
    add_item( ({ "forest", "mirkwood", "black wall of trees",
	"black wall", "wall", "trees", }),
	BSN("The forest of Mirkwood appears like a dark wall " +
	   "beyond the grassland to the east."));
    add_item( ({ "earth", "ground" }),
	BSN("The grasses grow thickly to cover the ground."));


    set_drink_from( ({ "ford", "great river", "wide river", "river",
	"anduin", "river anduin", "anduin river" }) );

    herbslist = HERB_MASTER->query_herbs( ({ "moderate", "plains",
					     "middle earth" }) );
    set_up_herbs( ({ ONE_OF_LIST(herbslist), ONE_OF_LIST(herbslist), 
    		     ONE_OF_LIST(herbslist), }),
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
	WRITE("You head north along the riverbank, brushing past " +
	    "waist-high grass.");
	break;
    case "south":
	WRITE("You leave the track to head south along the riverbank.");
	break;
    }
    return 0;
} /* move_msg */
