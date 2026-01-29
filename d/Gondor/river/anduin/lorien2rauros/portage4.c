/*
 * /d/Gondor/river/anduin/lorien2rauros/portage4.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * on north end of the portage trail, just above the slope
 * leading to the bay
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
    set_short("a rocky trail");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"Under the lee of weather-beaten cliffs, a narrow "+
	"trail winds south among sprawling briars and fallen "+
	"boulders. To the east, the ground slopes steeply down "+
	"toward the Great River.");

    set_tod_landtype("trail");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("portage3", "east", move_msg, 8);
    add_exit("portage5", "south", move_msg, 5);

    set_no_exit_msg( ({ "northwest", "west", "southwest", }),
	BSN("The cliffs are too steep to climb."));
    set_no_exit_msg( ({ "northeast", "southeast", }),
	BSN("You try to head downslope, but cannot find a path "+
	    "among the bogs and brambles."));
    set_no_exit_msg( ({ "north", }),
	BSN("You try to make your way north, but the trail "+
	    "vanishes in a jumble of rocks."));

    add_item( ({ "lee" }),
	BSN("Weathered cliffs provide some shelter for the trail "+
	    "that runs along their base."));
    add_item( ({ "emyn muil", }),
	BSN("The cliffs of the Emyn Muil are swept bare by wind."));
    add_item( ({ "path", "narrow trail", "rocky trail", "trail",
	"land", }),
	BSN("The narrow trail leads south, under the shelter of a "+
	    "wall of crumbling rock. To the east, the land falls away "+
	    "towards the Anduin far below."));
    add_item( ({ "base", "ground" }),
	BSN("The ground is stone, heaped with fallen rocks "+
	    "and tangled with brambles. In several places, "+
	    "water trickles down the cliff face, across the trail "+
	    "and down the eastern slope."));
    add_item( ({ "great river", "river anduin", "anduin river", "water",
	"anduin", "river", }),
	BSN("At the distant bottom of the slope, the Anduin flows south."));
    add_item( ({ "terraced cliff", "terraced cliffs",
    	"weather-beaten cliff", "cliff", "weather-beaten cliffs",
	"cliffs", "wall", "rock wall", }),
	BSN("Terraced cliffs of weathered stone run along the west side "+
	    "of the trail. To the north, a narrow stone chimney "+
	    "rises from a jumble of fallen rocks."));
    add_item( ({ "narrow pile", "pile", "narrow pile of stone",
	"pile of stone", "narrow stone chimney", "narrow chimney",
	"stone chimney", "chimney", }),
	BSN("A narrow pile of stone rises precariously from the "+
	    "jumble of rocks to the north."));
    add_item( ({ "narrow terrace", "narrow terraces", "terrace",
	"terraces", "cliff face", "face", }),
	BSN("Along the face of the cliff run narrow terraces, from which a "+
	"meagre trickle of water flows down the eastern slope."));
    add_item( ({ "water", "waters", "meagre trickle",
	"meagre trickles", "trickle", "trickles", }),
	BSN("Water trickles across the trail and down the slope "+
	    "to collect below in boggy pools."));
    add_item( ({ "downhill slope", "eastern slope", "east slope",
	"slope", "hill" }),
	BSN("The land to the east is a steep barren slope, "+
	    "cloaked by bramble thickets and boggy pools."));
    add_item( ({ "boggy pool", "boggy pools", "bog", "bogs",
	"pool", "pools", }),
	BSN("The pools on the slope below the trail appear to be "+
	    "fed by waters trickling down from the cliff."));
    add_item( ({ "bramble thicket", "bramble thickets", "thicket",
	"thickets", }),
	BSN("The slope below the trail is shrouded with dense "+
	    "thickets of brambles."));
    add_item( ({ "bramble", "brambles", "sprawling briar", "briar",
	"sprawling briars", "briars", }),
	BSN("Brambles overgrow the trail, and still more cloak "+
	    "the downhill slope to the east."));
    add_item( ({ "thorn", "thorns", }),
	BSN("The thorns are as long as your index finger, and appear "+
	    "to be razor-sharp."));
    add_item( ({ "fallen rock", "fallen rocks", "rock", "rocks",
	"tumbled boulder", "tumbled boulders", "boulder", "boulders", }),
	BSN("The trail is littered with tumbled boulders, apparently "+
	    "fallen from the cliffs above."));
    add_item( ({ "weathered stone", "stone", "limestone" }),
	BSN("The limestone of the cliffs is crumbled and eroded, "+
	    "and in places rocks have fallen onto the trail."));

    add_cmd_item( ({ "narrow pile", "pile", "narrow pile of stone",
	"pile of stone", "narrow stone chimney", "narrow chimney",
	"stone chimney", "chimney", }),
	"climb",
	BSN("The chimney appears much too precariously balanced "+
	    "to climb."));

    add_cmd_item( ({ "rock", "rocks", "boulder", "boulders", }),
	"climb", 
	BSN("You clamber among the boulders, but find nothing "+
	    "of interest."));

    add_cmd_item( ({ "bramble", "brambles", "sharp thorn",
	"thorn", "sharp thorns", "thorns", }),
	({ "search", "enter", }),
	BSN("The thorns draw blood, and you abandon the attempt."));
    add_cmd_item( ({ "thicket", "thickets", "bramble thicket",
	"bramble thickets", }),
	({ "search", "enter", }),
	BSN("The thickets are too far away."));

    add_cmd_item( ({ "boggy pool", "boggy pools", "weed-choked pool",
	"weed-choked pools", "pool", "pools", "in boggy pool",
	"in boggy pools", "in weed-choked pool", "in weed-choked pools",
	"in pool", "in pools", }),
	({ "search", "swim", "dive", "wade", "enter", }),
	BSN("The pools are too far away."));

    add_cmd_item( ({ "water from boggy pool", "water from boggy pools",
	"water from weed-choked pool", "water from weed-choked pools",
	"water from pool", "water from pools", }),
	"drink", 
	BSN("The pools are too far away."));

    add_cmd_item( ({ "terraced cliff", "terraced cliffs",
    	"weather-beaten cliff", "cliff", "weather-beaten cliffs",
	"cliffs", "wall", "rock wall", "narrow terrace",
	"narrow terraces", "terrace", "terraces", "cliff face",
	"face", }),
	"climb",
	BSN("The cliffs are steep, and the weathered stone "+
	    "easily crumbled. You make no progress at all."));

    add_cmd_item( ({ "fallen rock", "fallen rocks", "rock",
	"rocks", "limestone boulder", "limestone boulders",
	"boulder", "boulders", }),
	({ "shove", "push", "move", "roll", }),
	BSN("You give a mighty shove to the closest boulder, "+
	    "but it doesn't move an inch."));

    set_drink_from( ({ "meagre trickle", "meagre trickles",
	"trickle", "trickles", }) );

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
    if (QVB == "east")
    {
	WRITE( ({
	    "You carefully thread a path down the slope.",
	    "You plunge east down the steep slope.",
	    "Circling pools and boulders, you make your way downhill.",
	    })[random(3)] );
    }
    return 0;
} /* move_msg */
