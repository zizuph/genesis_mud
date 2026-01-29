/*
 * /d/Gondor/river/anduin/lorien2rauros/portage2.c
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
	"The steep slope is cloaked with thickets of brambles "+
	"and scattered with great gray boulders.");
    set_tod_landtype("slope");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("portage1", "east", move_msg, 8);
    add_exit("portage3", "west", move_msg, 8);

    set_no_exit_msg( ({ "northeast", "southeast", "north", "south", 
	"northwest", "southwest", }),
	BSN("You cannot find a path through the brambles."));

    add_item( ({ "emyn muil" }),
	BSN("The Emyn Muil is a harsh, unwelcoming land."));
    add_item( ({ "hill", "hills", "land", "slope", }),
	BSN("The land is a steep tumbled waste, barren of all but "+
	    "boulders and brambles, that climbs from the river below "+
	    "towards a line of low, weatherbeaten cliffs."));
    add_item( ({ "thickets", "bramble", "brambles", }),
	BSN("Great tangled masses of thorns cover the slope"));
    add_item( ({ "great tangled masses", "great masses", "tangled masses",
	"masses", "thorn", "thorns" }),
	BSN("The brambles have long, razor-sharp thorns."));
    add_item( ({ "steep tumbled waste", "steep waste", "tumbled waste",
	"waste", "ground" }),
	BSN("The ground is steep and hard. Brambles appear to be "+
	    "the only thing that can grow here."));
    add_item( ({ "texture", "gray limestone", "limestone", }),
	BSN("The gray limestone has a speckled, rough texture."));
    add_item( ({ "great gray boulder", "great boulder", "gray boulder", 
	"boulder", "great gray boulders", "great boulders", "gray boulders", 
	"boulders" }),
	BSN("Great gray boulders of limestone lie tumbled about "+
	    "the slope."));
    add_item( ({ "stone", "limestone", }),
	BSN("The stone is pitted and scarred by weather."));
    add_item( ({ "great river", "river anduin", "anduin river", "water",
	"anduin", "river", "calm shallow bay", "calm bay",
	"shallow bay", "bay", }),
	BSN("Far below, the Anduin flows past a calm shallow bay."));
    add_item( ({ "line", "low weatherbeaten cliff", "low cliff",
	"weatherbeaten cliff", "cliff", "low weatherbeaten cliffs",
	"low cliffs", "weatherbeaten cliffs", "cliffs", }),
	BSN("From low cliffs running along the top of the slope, "+
	    "slender chimneys of stone tower rise precariously "+
	    "towards the sky."));
    add_item( ({ "pile", "piles", "slender chimney",
	"slender chimneys", "chimney", "chimneys", }),
	BSN("The narrow piles of stone rise high above the cliffs."));

    add_cmd_item( ({ "maze", "gray limestone boulder",
	"gray limestone boulders", "gray boulder", "gray boulders",
	"limestone boulder", "limestone boulders",  "boulder", "boulders", }),
	({ "shove", "push", "move", "roll", }),
	BSN("You place your shoulder against a boulder and push "+
	    "with all your might, but to no avail."));

    add_cmd_item( ({ "maze", "gray limestone boulder",
	"gray limestone boulders", "gray boulder", "gray boulders",
	"limestone boulder", "limestone boulders",  "boulder", "boulders", }),
	({ "climb", }),
	BSN("You try to scramble atop a boulder, but can't quite "+
	    "manage it."));

    add_cmd_item( ({ "thickets", "bramble", "brambles", 
	"great tangled masses", "great masses", "tangled masses",
	"masses", "thorn", "thorns" }),
	({ "search", "enter" }),
	BSN("Ouch! Those thorns are too sharp!"));
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
	    "With considerable difficulty, you struggle further uphill.",
	    "You pick your way between the brambles, acquiring some "+
	    "painful scratches, and climb the slope.",
	    "You clamber up the steep slope, skirting boulders "+
	        "and brambles.",
	    })[random(3)] );
    }
    else
    {
	WRITE( ({
	    "You carefully thread a path between the boulders and "+
		"down the slope.",
	    "You stumble over a small boulder and rush headlong "+
		"down the slope, barely managing to stay on your feet.",
	    "You force a painful way past the brambles and down the slope.",
	    })[random(3)] );
    }
    return 0;
} /* move_msg */
