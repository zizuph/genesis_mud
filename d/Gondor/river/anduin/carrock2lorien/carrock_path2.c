/*
 * /d/Gondor/river/carrock2lorien/carrock_path2.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * on the Carrock path
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";

#include "/d/Gondor/defs.h"	/* ... always */


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
    set_tod_long("Steep, narrow steps wind round the west "+
	"side of the Carrock. Far below, the Anduin flows past.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("Carrock");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("carrock_path1", "southeast", move_msg, 7);
    add_exit("carrock_path1", "down", move_msg, 7, 1);
    add_exit("carrock_top", "northeast", move_msg, 7);
    add_exit("carrock_top", "up", move_msg, 7, 1);

    set_no_exit_msg( ({ "east", }),
	BSN("The rock wall is far too steep to climb."));
    set_no_exit_msg( ({ "north", "northwest", "west", "southwest",
	"south" }),
	BSN("Stepping off the path into thin air is not a good idea."));


    add_item( ({ "narrow path", "path", "steep narrow step",
	"steep step", "narrow step", "steep narrow steps", "steep steps",
	"narrow steps", "step", "steps", }),
	BSN("Slabs of stone, widely spaced, lead around the Carrock. "+
	    "Judging by their steepness, the steps were designed for "+
	    "someone with longer than average legs."));
    add_item( ({ "hard-packed earth", "earth", "dirt", "ground", }),
	BSN("The earth holding the steps has been firmly packed. "+
	    "The slabs appear unlikely to move."));
    add_item( ({ "rough slab", "rough slabs", "stone slab", "stone slabs",
	"slab", "slabs", }),
	BSN("Stone slabs are set in hard-packed earth to form "+
	    "steep narrow steps."));
    add_item( ({ "dark grey stone", "dark stone", "grey stone", "stone", }),
	BSN("The stone is weathered a dark grey."));
    add_item( ({ "steep rock wall", "steep wall", "rock wall", "wall", }),
	BSN("The rock wall is quite steep, and all but impossible "+
	    "to climb."));
    add_item( ({ "west side", "side", "hill", "great rock", "carrock", }),
	BSN("The west side of the Carrock is a steep rock wall, broken "+
	    "only by the narrow path."));
    add_item( ({ "middle", "great river", "waters", "water", "river",
	"anduin", "river anduin", "anduin river" }),
	BSN("Far below the narrow path, the Great River flows south "+
	    "between the Carrock and the grasslands to the west."));
    add_item( ({ "land", "vale of Anduin", "vale", }),
	BSN("From this vantage point, there is an excellent view "+
	    "west across the Anduin."));
    add_item( ({ "smooth grassland", "smooth grasslands",
	"grassland", "grasslands", }),
	BSN("Tall grasses stretch west from the river, rolling toward "+
	    "the horizon."));
    add_item( ({ "east", "eastern bank", "east bank", "eastern shore",
	"east shore", "eastern horizon", "east horizon", }),
	BSN("The Carrock rises steeply, blocking all views east."));
   
    add_item( ({ "river bank", "river banks", "bank", "banks",
	"shore", "shores", "west", "view", "western bank", "west bank",
	"western shore", "west shore", }),
	BSN("Tall grasses roll west towards the horizon, "+
	    "where dim blue mountains are just visible."));
    add_item( ({ "western horizon", "west horizon", "mountain",
	"mountains", "dim blue mountains", "dim mountains",
	"blue mountains", "horizon",  }),
	BSN("The Misty Mountains rise, blue with distance, "+
	    "on the west horizon."));
    add_item( ({  "peak", "peaks", "misty mountains", }),
	BSN("The Misty Mountains are only dimly visible from here, "+
	    "their peaks jagged against the horizon."));
    add_item( ({ "tall grass", "tall grasses",
	"thick grass", "thick grasses", "thick green grass",
	"thick green grasses", "green grass", "green grasses",
	"grass", "grasses", }),
	BSN("Green grass stretches west, away from the river."));

    add_item( ({ "northern horizon", "north horizon", "north",
	"southern horizon", "south horizon", "south" }),
	BSN("From this vantage point, little can be seen to the "+
	    "north or south, save for the Anduin flowing through "+
	    "wide grasslands."));

    add_cmd_item( ({ "up steep rock wall", "up steep wall", "up rock wall",
	"up wall",  "up carrock", "steep rock wall", "steep wall",
	"rock wall", "wall",  "carrock", }),
	"climb",
	BSN("You have not the skill to climb the steep wall "+
	    "of the Carrock. You would do better to use the path."));
    add_cmd_item( ({ "down steep rock wall", "down steep wall",
	"down rock wall", "down wall",  "down carrock", }),
	"climb",
	BSN("You have not the skill to climb down the steep wall "+
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
    if (vb == "northeast" ||
	vb == "up")
    {
	write( ({
	    "You struggle to take the tall steps in stride.\n",
	    "You climb the path, stretching a bit to manage the tall steps.\n",
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
