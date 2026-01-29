/*
 * /d/Gondor/river/anduin/lorien2rauros/old_road_west.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * old forest road on the west shore of the anduin
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
	"A little-used path leads east to a deep ford and west into " +
	"tall grasses. Great mountains, blue with distance, " +
	"are just visible beyond the grasslands.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("track");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("east",
	({ "deep ford", "ford", "great river", "waters", "water",
	"river", "anduin", "river anduin", "anduin river" }) );

    add_exit("river03", "east", 0, 2, 1);
    set_no_exit_msg( ({ "north", "northeast", "south", "southeast" }),
	BSN("You wander along the edge of the river, but find nothing " +
	    "of interest."));
    set_no_exit_msg( ({ "west", }),
	BSN("You follow the path into the grasses, but soon lose your " +
	    "way. With some difficulty, you return to the ford."));
    set_no_exit_msg( ({ "northwest", "southwest" }),
	BSN("You strike out into the grasses, but quickly become " +
	    "disoriented. After wandering aimlessly for a while, you " +
	    "find yourself back at the river."));

    add_item( ({ "old ford", "ford", "waters", "water", }),
	&exa_water(RIVER,
	    BSN("The ford is deep and wide, but probably can " +
	    "be crossed safely.")));
    add_item( ({ "wide flat plain", "wide plain", "flat plain", 
	"plain", "grasslands", "grassland", "great river", "river anduin",
	"anduin river", "anduin", "river", }),
	BSN("The Great River, flowing through a wide flat " +
	    "plain, is a grey seam dividing a green blanket of grass."));
    add_item( ({ "little-used path", "grassy path", "path", }),
	BSN("The path is narrow, and thickly grown with grass. " +
	    "Evidently little traffic passes this way."));
    add_item( ({ "far horizon", "west horizon", "horizon",
	"great mountains", "great mountain", "mountain", "mountains", }),
	BSN("Great mountains march on the far horizon, " +
	    "dim and blue with distance. These must be the " +
	    "Misty Mountains."));
    add_item( ({ "dim lofty shapes", "dim shapes", "lofty shapes",
	"shapes", "misty mountains", }),
	BSN("From this distance, the Misty Mountains are but " +
	    "dim, lofty shapes on the horizon."));
    add_item( ({ "western bank", "west bank", "this shore", "this side",
	"this side of river", "western shore", "west shore" }),
	BSN("From the water's edge, green grasses stretches west " +
	    "to the horizon."));
    add_item( ({ "riverbank", "river bank", "shore", "shores", }),
	BSN("Tall green grasses grow up to the very edge of the river."));
    add_item( ({ "far shore", "far side", "far side of river",
	"eastern bank", "east bank", "eastern shore", "east shore" }),
	BSN("Endless grasses are all that may be seen on the far shore."));
    add_item( ({ "tall grass", "tall grasses", "endless grass",
	"endless grasses", "green grasses", "green grass",
	"grasses", "grass", }),
	BSN("The grass of the plains, waist-high and deep green in " +
	    "colour, whispers with the passing breeze."));
    add_item( ({ "grey seam", "seam" }),
	BSN("The Anduin, grey, wide and swift, divides the grasslands " +
	    "as it rolls south."));
    add_item( ({ "green blanket of grass", "blanket of grass",
    	"green blanket", "blanket", }),
	BSN("Broad grasslands stretch away from the river, " +
	    "looking for all the world like a soft green blanket."));
    add_item( ({ "water's edge", "river's edge", "edge of river",
	"edge of the river", "edge" }),
	BSN("The grasses grow tall and thick along the river's edge, " +
	    "obscuring the waters save where the path dips to the ford."));
    add_item( ({ "earth", "ground" }),
	BSN("The grasses grow so thickly that no earth is " +
	    "visible beneath them."));

    set_drink_from( ({ "deep ford", "ford", "great river", "river",
	"anduin", "river anduin", "anduin river" }) );

    herbslist = HERB_MASTER->query_herbs( ({ "moderate", "plains",
					     "middle earth" }) );
    set_up_herbs( ({ ONE_OF_LIST(herbslist), ONE_OF_LIST(herbslist), 
    		     ONE_OF_LIST(herbslist), }),
	    	  ({ "riverbank", "bank", "shore", "ground",
		     "grass", "grasses", }),
		  5);
} /* create_shore_room */
