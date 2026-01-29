/*
 * /d/Gondor/river/anduin/lorien2rauros/portage1.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * on the slope leading from the bay to the portage trail
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";

#include "/d/Gondor/defs.h"	/* always */

/* prototypes */
public void	create_gondor();
public int	move_msg();

/*
 * Function name:	create_gondor
 * Description	:	set up the slope
 */
public void
create_gondor()
{
    set_short("a steep slope");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The land slopes up and away from the Great River, a tumbled waste "+
	"of gray limestone boulders, shrouded with weeds and bushes.");
    set_tod_landtype("slope");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("beach17w", "east", move_msg, 8);
    add_exit("portage2", "west", move_msg, 8);
    set_no_exit_msg( ({ "northeast", "southeast", }),
	BSN("You try to cut a diagonal path down toward the river, "+
	    "but cannot force your way through the tangled bushes."));
    set_no_exit_msg( ({ "north", "south" }),
	BSN("You strike out along the slope, parallel to the river, "+
	    "but find your way blocked by a maze of limestone boulders."));
    set_no_exit_msg( ({ "northwest", "southwest" }),
	BSN("Your path uphill is blocked by tumbled boulders and "+
	    "thickly tangled bushes."));

    add_item( ({ "emyn muil" }),
	BSN("The hills of the Emyn Muil loom stark and forbidding."));
    add_item( ({ "shore", "slope", "land", "hill", "hills", }),
	BSN("Boulders, grown about with tangled weeds and bushes, "+
	    "are tumbled about the hill, which rises steeply "+
	    "west towards low cliffs."));
    add_item( ({ "waste", "ground" }),
	BSN("The ground is barren and hard. Only weeds and stunted "+
	    "bushes grow here."));
    add_item( ({ "thickly tangled bush", "thickly tangled bushes",
	"tangled bush", "tangled bushes", "stunted bush",
	"stunted bushes", "bush", "bushes", }),
	BSN("The bushes are low and scrubby; they grow together in "+
	    "impenetrable tangles."));
    add_item( ({ "sere tangled weed", "sere tangled weeds", "sere weed",
	"sere weeds", "tangled weed", "tangled weeds", "weed", "weeds", }),
	BSN("Sere, tangled weeds grow thickly around the boulders."));
    add_item( ({ "surface", "gray limestone", "limestone", }),
	BSN("The limestone is light gray in colour, and has a rough, "+
	    "uneven surface."));
    add_item( ({ "maze", "gray limestone boulder", "gray limestone boulders",
	"gray boulder", "gray boulders", "limestone boulder",
	"limestone boulders",  "boulder", "boulders", }),
	BSN("Limestone boulders are tumbled about the "+
	    "slope, making passage extremely difficult."));
    add_item( ({ "great river", "river anduin", "anduin river",
	"water", "anduin", "river", }),
	BSN("To the east, down the slope and beyond a shallow bay, "+
	    "the Great River flows swiftly south."));
    add_item( ({ "calm shallow bay", "calm bay", "shallow bay", "bay", }),
	BSN("At the foot of the slope lies a calm, shallow bay. "+
	    "Beyond it, the Anduin flows past with some force."));
    add_item( ({ "strip of stone", "strip", "stone", "narrow beach",
	"beach", }),
	BSN("A narrow beach ... a mere strip of stone ... "+
	    "runs along the side of the bay, at the foot of the slope."));
    add_item( ({ "top", "low cliff", "low cliffs", "cliff", "cliffs", }),
	BSN("At the very top of the slope are low cliffs, "+
	    "from which slender fingers of stone rise to the sky."));
    add_item( ({ "slender finger of stone", "slender fingers of stone", 
	"finger of stone", "fingers of stone", "slender finger",
	"slender fingers", "finger", "fingers", }),
	BSN("Fingers of stone jab upwards from the low cliffs."));

    add_cmd_item( ({ "maze", "gray limestone boulder",
	"gray limestone boulders", "gray boulder", "gray boulders",
	"limestone boulder", "limestone boulders",  "boulder", "boulders", }),
	({ "shove", "push", "move", "roll", }),
	BSN("You shove the nearest boulder, but it does not budge."));

    add_cmd_item( ({ "maze", "gray limestone boulder",
	"gray limestone boulders", "gray boulder", "gray boulders",
	"limestone boulder", "limestone boulders",  "boulder", "boulders", }),
	({ "climb", }),
	BSN("You try to climb the boulder, but cannot get "+
	    "a good handhold. You slide back to the ground."));
} /* create_gondor */


/*
 * Function name:	move_msg
 * Description	:	write a msg about struggling up the slope
 * Returns	:	0 (exit always allowed)
 */
public int
move_msg()
{
    if (QVB == "west")
    {
	WRITE( ({
	    "With considerable difficulty, you struggle up the "+
	        "slope.",
	    "You pick your way between the boulders and climb the slope.",
	    "You clamber up the steep slope, forcing your way past "+
	        "the tangled bushes and weeds.",
	    })[random(3)] );
    }
    else
    {
	WRITE( ({
	    "You carefully thread a path between the boulders and "+
		"down the slope.",
	    "You stumble down the steep slope, barely managing "+
		"to retain your balance.",
	    "You force your way past the bushes and down the slope.",
	    })[random(3)] );
    }
    return 0;
} /* move_msg */
