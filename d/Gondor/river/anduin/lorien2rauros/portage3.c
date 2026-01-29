/*
 * /d/Gondor/river/anduin/lorien2rauros/portage3.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * on the slope leading from the bay to the portage trail
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";

#include "/d/Gondor/defs.h"	/* always */

/* prototypes */
public void	create_gondor();
public void	init();
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
	"Scattered among the thickets and boulders shrouding "+
	"the slope are boggy pools, their waters dull and "+
	"choked with weeds.");
    set_tod_landtype("slope");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("portage2", "east", move_msg, 8);
    add_exit("portage4", "west", move_msg, 8);

    set_no_exit_msg( ({ "northeast", "southeast", "north", "south", 
	"northwest", "southwest", }),
	BSN("You cannot find a path among the bogs and brambles."));

    add_item( ({ "emyn muil", }),
	BSN("The Emyn Muil is a harsh, wind-scoured land."));
    add_item( ({ "land", "slope", }),
	BSN("The land slopes steeply up to the west, cloaked by "+
	    "boulders, pools and bramble thickets. Along the top "+
	    "of the slope, narrow stone chimneys rise above "+
	    "low cliffs."));
    add_item( ({ "ground" }),
	BSN("The ground is hard, and appears to support "+
	    "only weeds and brambles."));
    add_item( ({ "boggy pool", "boggy pools", "bog", "bogs",
	"weed-choked pool", "weed-choked pools", "pool", "pools", }),
	BSN("The pools appear to be fed by waters trickling from "+
	    "terraces further inland. They are shallow, and choked "+
	    "with weeds."));
    add_item( ({ "water", "waters", "meagre trickle",
	"meagre trickles", "trickle", "trickles", }),
	BSN("Water seeps down the slope to collect in weed-choked "+
	    "pools."));
    add_item( ({ "clump", "clumps", "thirsty weed", "thirsty weeds",
	"weed", "weeds", }),
	BSN("Clumps of thirsty weeds clog the pools."));
    add_item( ({ "great boulder", "great boulders", "boulder", "boulders", }),
	BSN("Great boulders lie tumbled around the slope, "+
	    "as if giants were playing dice."));
    add_item( ({ "rough stone", "stone", "limestone",
	"rough stones", "stones", }),
	BSN("The rough stone has been worn down by wind and "+
	    "weather."));
    add_item( ({ "bramble", "brambles", "thicket", "thickets",
	"bramble thicket", "bramble thickets", }),
	BSN("Dense thickets of sharp thorns shroud the slope, "+
	    "making passage difficult and painful."));
    add_item( ({ "sharp thorn", "thorn", "sharp thorns", "thorns", }),
	BSN("The thorns are finger length, and appear very sharp."));
    add_item( ({ "great river", "river anduin", "anduin river", "water",
	"anduin", "river", "calm shallow bay", "calm bay",
	"shallow bay", "bay", }),
	BSN("Far below, the Anduin flows past a calm shallow bay."));
    add_item( ({ "top", "low cliff", "cliff", "low cliffs", "cliffs", }),
	BSN("From low cliffs of weathered stone at the top "+
	    "of the slope, stone chimneys pierce the sky."));
    add_item( ({ "narrow stone chimney", "narrow chimney",
	"stone chimney", "chimney", "accusing finger", "finger",
	"accusing fingers", "fingers", }),
	BSN("Narrow stone chimneys rise like accusing fingers "+
	    "from the cliffs along the top of the slope."));
    add_item( ({ "ledge", "ledges", "shelf", "shelves", 
	"series", "inland", "terrace", "terraces", }),
	BSN("Along the bases of the cliffs, ledges and shelves of "+
	"stone form a series of terraces, from which a meagre trickle "+
	"of water flows downhill."));

    add_cmd_item( ({ "maze", "gray limestone boulder",
	"gray limestone boulders", "gray boulder", "gray boulders",
	"limestone boulder", "limestone boulders",  "boulder", "boulders", }),
	({ "shove", "push", "move", "roll", }),
	BSN("You give a mighty shove to the closest boulder, "+
	    "but it doesn't move an inch."));

    add_cmd_item( ({ "maze", "gray limestone boulder",
	"gray limestone boulders", "gray boulder", "gray boulders",
	"limestone boulder", "limestone boulders",  "boulder", "boulders", }),
	({ "climb", }),
	BSN("You scrabble at the boulder, but cannot find "+
	    "a way up."));

    add_cmd_item( ({ "bramble", "brambles", "thicket", "thickets",
	"bramble thicket", "bramble thickets",  "sharp thorn",
	"thorn", "sharp thorns", "thorns", }),
	({ "search", "enter", }),
	BSN("The thorns draw blood, and you abandon the attempt."));

    add_cmd_item( ({ "boggy pool", "boggy pools", "weed-choked pool",
	"weed-choked pools", "pool", "pools", "in boggy pool",
	"in boggy pools", "in weed-choked pool", "in weed-choked pools",
	"in pool", "in pools", }),
	({ "swim", "dive", "wade", "enter", }),
	({ "The pools are too shallow for swimming.\n",
	   "The pools are much too shallow for diving.\n",
	   BSN("The pools are so choked with weeds, there is no room "+
	       "for wading."),
	   "The pools are too shallow for swimming.\n", }) );

    set_drink_from( ({ "meagre trickle", "meagre trickles",
	"trickle", "trickles", "boggy pool", "boggy pools",
	"bog", "bogs", "weed-choked pool", "weed-choked pools",
	"pool", "pools", }) );

} /* create_gondor */


/*
 * Function name:	init
 * Description	:	initialize the drink command
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
    if (QVB == "west")
    {
	WRITE( ({
	    "Snagged by thorns, you struggle to climb the slope.",
	    "You pick your way up the hill, carefully avoiding "+
		"the boggy pools.",
	    "You clamber up the steep slope, skirting bogs "+
	        "and brambles.",
	    })[random(3)] );
    }
    else
    {
	WRITE( ({
	    "You carefully thread a path between the boggy pools and "+
		"down the slope.",
	    "You negotiate a painful course among the thorns and downhill.",
	    "Circling pools and boulders, you make your way downhill.",
	    })[random(3)] );
    }
    return 0;
} /* move_msg */
