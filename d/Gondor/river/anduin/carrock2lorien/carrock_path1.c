/*
 * /d/Gondor/river/carrock2lorien/carrock_path1.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * on the Carrock path
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";

#include "/d/Gondor/defs.h"	/* ... always */


/* prototypes */
public void	create_gondor();
public int	move_msg();


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("narrow path");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"A narrow path of widely spaced steps climbs the " +
	"south side of the Carrock. Directly below, the hill " +
	"drops steeply away to the Anduin. To the east, the path " +
	"descends to a sandy beach.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("Carrock");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("carrock_beach", "east", move_msg, 7);
    add_exit("carrock_beach", "down", move_msg, 7, 1);
    add_exit("carrock_path2", "northwest", move_msg, 7);
    add_exit("carrock_path2", "up", move_msg, 7, 1);

    set_no_exit_msg( ({ "north", "northeast", }),
	BSN("The rock wall is far too steep to climb."));
    set_no_exit_msg( ({ "southeast", "south", "southwest", "west", }),
	BSN("Stepping off the path into thin air is not a good idea."));


    add_item( ({ "narrow path", "path", "widely spaced step", "step",
	"narrow step", "narrow steps", "widely spaced steps", "steps", }),
	BSN("The stone slabs that form the path seem to be spaced for " +
	    "someone with very long legs."));
    add_item( ({ "hard-packed earth", "earth", "dirt", "ground", }),
	BSN("The steps are set in hard-packed earth."));
    add_item( ({ "rough slab", "rough slabs", "stone slab", "stone slabs",
	"slab", "slabs", }),
	BSN("Stone slabs are set far apart in hard-packed earth to " +
	    "form the steps of the Carrock."));
    add_item( ({ "dark grey stone", "dark stone", "grey stone",
	"stone", }),
	BSN("The dark grey stone is shaped into rough slabs."));
    add_item( ({ "north edge", "edge", "steep rock wall", "steep wall",
	"rock wall", "wall", }),
	BSN("The rock wall rises nearly vertically along the " +
	    "north edge of the path."));
    add_item( ({ "south side", "side", "hill", "carrock", }),
	BSN("The south side of the Carrock drops away sharply " +
	    "to the river below. The narrow path is the only " +
	    "way of traversing the rock."));
    add_item( ({ "middle", "great river", "waters", "water", "river",
	"anduin", "river anduin", "anduin river" }),
	BSN("The waters of the Anduin flow around the Carrock " +
	    "to merge almost directly below the path."));
    add_item( ({ "land", "view", "horizon", "vale", }),
	BSN("Wide grasslands stretch from the Carrock on " +
	    "either shore, and the Great River rolls away south."));
    add_item( ({ "river bank", "river banks", "bank", "banks",
	"shore", "shores", "wide grassland", "wide grasslands",
	"smooth grassland", "smooth grasslands",
	"grassland", "grasslands", }),
	BSN("The banks of the Anduin are cloaked with tall grasses " +
	    "that ripple with the wind, or with the passage of some " +
	    "unseen animal."));
    add_item( ({ "tall grass", "tall grasses",
	"thick grass", "thick grasses", "thick green grass",
	"thick green grasses", "green grass", "green grasses",
	"grass", "grasses", }),
	BSN("The grasses are easily waist-high, and very thick. " +
	    "Occasionally they ripple and bend, though the " +
	    "cause is not evident."));

    add_item( ({ "east", "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Tall grasses stretch east to the horizon, where a " +
	    "dark wall of trees looms ominously."));
    add_item( ({ "eastern horizon", "east horizon", 
    	"forest", "trees", "dark wall of trees", "dark wall", "wall",
	"wall of trees", }),
	BSN("A dark wall of trees -- the boundary of Mirkwood -- " +
	     "marches along the east horizon."));
    add_item( ({ "boundary", "boundary of mirkwood",
	"forest of mirkwood", "mirkwood", }),
	BSN("What little is visible of Mirkwood seems dark and ominous."));

    add_item( ({ "west", "western bank", "west bank", "western shore",
	"west shore", }),
	BSN("Tall grasses extend west from the river to the far " +
	    "horizon, where a dim outline of mountains is just " +
	    "visible."));
    add_item( ({ "dim outline", "outline", "west horizon", "mountain",
	"mountains", "misty mountains", }),
	BSN("The Misty Mountains rise, barely visible, " +
	    "on the west horizon."));

    add_item( ({ "north", "north horizon", "northern horizon", }),
	BSN("The steep wall of the Carrock blocks the view north."));
    add_item( ({ "south", "south horizon", "southern horizon", }),
	BSN("The Great River flows south, wide and swift, " +
	    "between smooth grasslands."));

    add_cmd_item( ({ "up steep rock wall", "up steep wall",
	"up rock wall", "up wall",  "up carrock", "steep rock wall",
	"steep wall", "rock wall", "wall",  "carrock", }),
	"climb",
	BSN("You have not the skill to climb the steep wall " +
	    "of the Carrock. You would do better to use the path."));
    add_cmd_item( ({ "down steep rock wall", "down steep wall",
	"down rock wall", "down wall",  "down carrock", }),
	"climb",
	BSN("You have not the skill to climb down the steep wall " +
	    "of the Carrock. You would do better to use the path."));
} /* create_gondor */


/*
 * Function name:	move_msg
 * Description	:	do nice msg re climbing the path
 * Returns	:	0 -- exit always succeeds
 */
public int
move_msg()
{
    string	vb = QVB;
    if (vb == "northwest" ||
	vb == "up")
    {
	write( ({
	    "You struggle to take the tall steps in stride.\n",
	    "You climb the path, stretching a bit to manage the " +
		"tall steps.\n",
	    "You clamber up the tall steps.\n",
	    "With some difficulty, you climb the widely-spaced steps.\n",
	    })[random(4)] );
    }
    else
    {
	write( ({
	    "You scramble down the steep steps.\n",
	    "You nearly stumble as you descend the steep path.\n",
	    "You carefully make your way down the path.\n",
	    "You descend with care, stretching from step to step.\n",
	    })[random(4)] );
    }
    return 0;
} /* move_msg */
