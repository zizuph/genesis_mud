/*
 * /d/Gondor/river/anduin/lorien2rauros/beach17w.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 65 miles downstream from the silverlode, the campsite for day 2.
 *
 * TBD: allow "force passage" to find a way into a thicket
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	BAY	(LORIEN_TO_RAUROS_DIR+"bay17")

/* prototypes */
public void	create_shore_room();
public void	init();
public int	move_msg();

/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    set_short("stony beach");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"From this level strip of beach, a steep rocky bank rises "+
	"to the west. To the east, a few low trees grow along the edge "+
	"of a shallow bay and beyond the bay, the Great River flows south.");
    set_tod_landtype("beach");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("east",
    	({ "small bay", "small shallow bay", "shallow bay",
	   "waters", "water", }) );

    add_exit("bay17", "east", 0, 2, 1);
    add_exit("portage1", "west", move_msg, 10);
    set_no_exit_msg( ({ "northeast", "north", "south", "southeast" }),
	BSN("The beach narrows quickly, leaving you no "+
	    "choice but to return to where you were."));
    set_no_exit_msg( ({ "northwest", "southwest" }),
	BSN("You struggle up the slope, but are unable to make "+
	    "much headway and so return to the beach."));

    add_item( ({ "small bay", "small shallow bay", "shallow bay",
	   "waters", "water", "bay", }),
	&exa_water(BAY,
	    "The bay is shallow, and quite calm.\n"));

    add_item( ({ "level strip", "strip", "stony beach", "beach" }),
	BSN("The beach is simply a level strip of stone at "+
	    "the edge of the bay. Inland, it quickly gives way to "+
	    "a steep slope, tumbled with boulders and bushes."));
    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }),
	    BSN("To the east, beyond the bay, the Anduin flows "+
	    "swiftly south."));
    add_item( ({ "rugged land", "wind-scoured land",
	"rugged wind-scoured land", "land", "shore", "shores",
	"western shore", "west shore", "western bank", "west bank", }),
	BSN("The western shore rises steeply up from "+
	   "the bay to meet weathered cliffs. It appears "+
	   "generously provided with bushes and boulders."));
    add_item( ({ "far side", "side", "eastern shore", "east shore",
	"eastern bank", "east bank", }),
	BSN("It is impossible to see much of the east shore from here."));
    add_item( ({ "tangled bush", "tangled bushes", 
        "bush", "bushes", }),
	BSN("Tangled bushes cover the shore like a cloak."));
    add_item( ({ "cloak", }),
	BSN("The bushes, thickly intertwined, cover much of the slope. "+
	    "Forcing a passage through them probably would be difficult."));
    add_item( ({ "steep rocky bank", "steep bank", "rocky bank",
	"river bank", "bank", "steep slope", "slope", }),
	BSN("The bank slopes sharply up to the west. The ground, "+
	    "broken by boulders and bushes, appears rough and uneven. "+
	    "Low cliffs run along the top of the bank."));
    add_item( ({ "ground" }),
	BSN("The stone of the beach is relatively smooth, but "+
	    "to the west the ground becomes rough and uneven."));
    add_item( ({ "low cliff", "low cliffs", "weathered cliff",
	"weathered cliffs", "cliff", "cliffs", }),
	BSN("A line of low cliffs runs along the top of the steep bank. "+
	    "Here and there, slender chimneys of weathered stone rise "+
	    "above the cliffs."));
    add_item( ({ "slender chimney", "chimney", "slender chimneys",
	"chimneys", "crooked finger", "crooked fingers",
	"finger", "fingers" }),
	BSN("The chimneys resemble crooked fingers of stone."));
    add_item( ({ "gray stone", "gray stones", "weathered stone",
	"weathered stones", "stone", "stones" }),
	BSN("The gray stone of the beach matches that of the cliffs "+
	    "and chimneys and clearly shows the effects of time "+
	    "and weather."));
    add_item( ({ "emyn muil", }),
	BSN("The Emyn Muil is a rugged, wind-scoured land. "+
	    "It seems harsh and unwelcoming."));
    /* XXX put a boulder up there, let them push it? */
    add_item( ({ "rock", "rocks", "great boulder", "boulder",
	"great boulders", "boulders", }),
	BSN("Great boulders lie tumbled about the slope. They appear "+
	    "somewhat precariously poised above the beach."));
    add_item( ({ "edge", "low scrubby tree", "low scrubby trees",
	"low tree", "low trees", "tree", "trees" }),
	BSN("Low scrubby trees grow along the edge of the bay, "+
	    "leaning out over the water."));

    add_cmd_item( ({ "low scrubby tree", "low scrubby trees",
	"low tree", "low trees", "tree", "trees" }),
	"climb",
	BSN("None of the trees is large enough to bear your weight."));


    set_drink_from( ({ "small bay", "small shallow bay", "shallow bay",
	   "bay", }) );

} /* create_shore_room */


/*
 * Function name:	init
 * Description	:	add drink verb
 */
public void
init()
{
    ::init();
    init_drink();
} /* init */


/*
 * Function name:	move_msg
 * Description	:	write a msg about struggling up the slope
 * Returns	:	0 (exit always allowed)
 */
public int
move_msg()
{
    WRITE( ({
	"With considerable difficulty, you struggle up the "+
	    "slope from the beach.",
	"You pick your way up the steep slope, avoiding the "+
	    "bushes as best you can.",
	"You clamber up the steep bank, threading your way between "+
	    "boulders and bushes.",
	})[random(3)] );
    return 0;
} /* move_msg */
