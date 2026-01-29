/*
 * /d/Gondor/river/anduin/lorien2rauros/beach01e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * east shore of the anduin, just below carrock ford,
 * 35 miles north of old forest rd
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	RIVER	(CARROCK_TO_LORIEN_DIR+"river01")


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
	"Tall grasses grow thickly on the low bank, up to the "+
	"very edge of the river.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("riverbank");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_exit("beach00e", "northeast", move_msg, 3);
    add_exit("river01", "west", 0, 2, 1);
    add_exit("beach02e", "south", 0, 3);
    set_no_exit_msg( ({ "north", "northwest", "southwest" }),
	BSN("You wander among the tall grasses of the riverbank."));
    set_no_exit_msg( ({ "east", "southeast", }),
	BSN("You strike a course inland, but soon lose your way "+
	    "and return to the river."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", "waters", "water", }),
	&exa_water(RIVER,
	    BSN("The Anduin is wide, and its waters move swiftly south.")));

    add_item( ({ "western bank", "west bank", "far shore", "far side",
	"far side of river", "western shore", "west shore" }),
	BSN("Nothing is visible on the far shore but grass."));
    add_item( ({ "this shore", "this side", "this side of river",
	"bank", "riverbank", "river bank", "edge",
	"shore", "shores", "eastern bank", "east bank", "eastern shore",
	"east shore" }),
	BSN("This bank of the river is covered with grass, which "+
	    "grows even taller and more lush inland."));
    add_item( ({ "inland", "tall grass", "tall grasses",
	"lush grasses", "lush grass", "grasses", "grass", }),
	BSN("Tall grasses, tossing in the least breath of wind, "+
	    "block all views inland."));
    add_item( ({ "earth", "ground" }),
	BSN("Lush grass covers the ground completely."));

    set_drink_from( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }) );

    herbslist = HERB_MASTER->query_herbs( ({ "moderate", "plains",
					     "middle earth" }) );
    set_up_herbs(({ ONE_OF_LIST(herbslist), ONE_OF_LIST(herbslist), 
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
    case "northeast":
	WRITE("You follow the riverbank to the northeast, where "+
	    "the grasses give way to a sandy beach.");
	break;
    case "south":
	WRITE("You head south along the riverbank, pushing "+
	    "through the tall grasses.");
	break;
    }
    return 0;
} /* move_msg */
