/*
 * /d/Gondor/river/carrock2lorien/carrock_top.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * on top of the Carrock
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
    set_short("on top of the Carrock");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("The top of the Carrock is flat and open, "+
	"affording a splendid view in all directions. "+
	"A path with many steps descends steeply to "+
	"the Great River far below.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("Carrock");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("carrock_path2", "southwest", move_msg, 7);
    add_exit("carrock_path2", "down", move_msg, 7, 1);

    set_no_exit_msg( ({ "north", "northwest", "west", "south",
	"southeast", "east", "northeast", }),
	BSN("Stepping off the Carrock into thin air is not a good idea."));


    add_item( ({ "well worn path", "path", "steep step", "steep steps",
	"step", "steps", }),
	BSN("The steps on the well worn path appear quite steep, as if "+
	    "created by someone taller than the average human."));
    add_item( ({ "great hill of stone", "hill", "carrock", }),
	BSN("The top of the Carrock is quite flat, but at the "+
	    "edges the great hill drops quite steeply."));
    add_item( ({ "edge", "edges", }),
	BSN("The Carrock falls away sharply from the flat, open top."));
    add_item( ({ "ground", "stone", "weathered rock", "rock", 
	"flat open top", "flat top", "open top", "top", }),
	BSN("The stone of the Carrock is dark grey, with many "+
	   "small fissures."));
    add_item( ({ "mark", "marks", "small fissure", "fissure",
	"small fissures", "fissures", }),
	BSN("Wind and weather have left their mark on the rock."));
    add_item( ({ "middle", "great river", "waters", "water", "river",
	"anduin", "river anduin", "anduin river" }),
	BSN("Far below, the Anduin splits to flow around the Carrock."));
    add_item( ({ "land", "view", "vale", "horizon", }),
	BSN("You have an unobstructed view to the horizon in all "+
	    "directions."));
    add_item( ({ "river bank", "river banks", "bank", "banks",
	"shore", "shores", }),
	BSN("In the distance below, the Great River flows from "+
	    "north to south through wide grasslands."));
    add_item( ({ "wide plain", "plain", "wide plains", "plains",
	"smooth grassland", "smooth grasslands", "wide grassland",
	"wide grasslands", "grassland", "grasslands", }),
	BSN("Tall grasses lie like a smooth green blanket below "+
	    "the Carrock."));
    add_item( ({ "tall grass", "tall grasses", "green grass",
	"green grasses", "smooth green blanket", "green blanket",
	"blanket", "smooth expanse of green", "expanse of green",
	"smooth expanse", "expanse", "green", "grass", "grasses", }),
	BSN("From this height, the grasses are just a smooth "+
	    "expanse of green."));

    add_item( ({ "northwest view", "southwest view", "west view",
	"northwest", "southwest", "west", "western bank",
	"west bank", "western shore", "west shore", }),
	BSN("Wide grasslands stretch west towards dim "+
	    "blue mountains."));
    add_item( ({ "western horizon", "west horizon", "dim blue mountains",
	"dim mountains", "blue mountains", "misty mountains", }),
	BSN("Far to the west, at the very edge of sight, "+
	    "forested foothills give rise to the Misty Mountains."));
    add_item( ({ "base", "forest", "forests", "forested foothills",
	"foothills", }),
	BSN("Forests cloak the base of the distant mountains."));
    add_item( ({ "base", "forest", "forests",
	"forested foothills", "foothills", }),
	BSN("Forests cloak the base of the distant mountains."));

    add_item( ({ "mountain", "mountains", }),
	BSN("The Misty Mountains rise on the west horizon, and far "+
	   "to the north a dark line marks the beginnings of "+
	   "the Grey Mountains."));

    add_item( ({ "northeast view", "southeast view", "east view",
	"northeast", "southeast", "east", "eastern bank",
	"east bank", "eastern shore", "east shore", }),
	BSN("Green grasses flow east from the river. In the near "+
	    "distance tall oaks enclose some sort of farmstead, "+
	    "and far to the east a dark wall of trees marches "+
	    "along the horizon."));
    add_item( ({ "tall oaks", "oaks", "oak tree", "oak trees", "farmstead", 
	"large house", "house", }),
	BSN("Tall oaks around a large house are all that is "+
	    "visible from here."));
    add_item( ({ "eastern horizon", "east horizon", "dark wall of trees",
	"dark wall", "wall", "tree", "trees" }),
	BSN("Far to the east, the trees of Mirkwood form a wall "+
	    "beyond the grassland."));
    add_item( ({ "vast forest", "forest", "mirkwood" }),
	BSN("The vast forest of Mirkwood rises, dark and ominous, "+
	    "beyond the plains to the east."));

    add_item( ({ "north horizon", "north view", "north", }),
	BSN("The Anduin flows from the north, bisecting a wide "+
	    "plain of grass. Far to the north, a faint dark line "+
	    "marks the beginnings of the Grey Mountains."));
    add_item( ({ "faint dark line", "faint line", "dark line",
	"line", "grey mountains", }),
	BSN("The Grey Mountains are barely visible "+
	    "from this vantage point, marked only by a faint dark "+
	    "line on the horizon to the north."));

    add_item( ({ "south horizon", "south view", "south" }),
	BSN("Some little distance downstream of the Carrock, "+
	    "there seems to be a road or track crossing the river. "+
	    "Beyond that, the Great River rolls south between "+
	    "smooth grasslands, as far as the eye can see."));
    add_item( ({ "road", "track", }),
	BSN("The road appears to run east-west across the river, "+
	    "but it's too far away to see details."));

    add_cmd_item( ({ "up carrock", "carrock", }),
	"climb",
	BSN("You already are on top of the Carrock."));
    add_cmd_item( ({ "down carrock", }),
	"climb",
	BSN("You have not the skill to climb down the Carrock. "+
	    "You would do better to use the path."));
} /* create_gondor */


/*
 * Function name:	move_msg
 * Description	:	do nice msg re climbing the path
 * Returns	:	0 -- exit always succeeds
 */
public int
move_msg()
{
    write( ({
	"You scramble down the steep steps.\n",
	"You nearly stumble as you descend the steep path.\n",
	"You carefully make your way down the path.\n",
	"You descend with care, stretching from step to step.\n",
	})[random(4)] );
    return 0;
} /* move_msg */
