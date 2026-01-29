/*
 * /d/Gondor/river/anduin/lorien2rauros/portage5.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * near the north end of the portage trail
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";

#include "/d/Gondor/defs.h"	/* always */

/* prototypes */
public void	create_gondor();

/*
 * Function name:	create_gondor
 * Description	:	set up the trail
 */
public void
create_gondor()
{
    set_short("a rocky trail");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"A rocky trail winds its way through a maze of "+
	"boulders and briars beneath crumbling limestone cliffs.");

    set_tod_landtype("trail");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("portage4", "north", 0, 5);
    add_exit("portage6", "south", 0, 5);

    set_no_exit_msg( ({ "northwest", "west", "southwest", }),
	BSN("The cliffs are too steep to climb."));
    set_no_exit_msg( ({ "northeast", "east", "southeast", }),
	BSN("You cannot find a path through the boulders "+
	    "and brambles."));

    add_item( ({ "emyn muil", }),
	BSN("The cliffs of the Emyn Muil are crumbled by weather."));
    add_item( ({ "path", "rocky trail", "trail", "land", }),
	BSN("The rocky trail winds among boulders and briars to "+
	    "run roughly north-south under the cliffs."));
    add_item( ({ "maze" }),
	BSN("The trail twists and turns through a jumble "+
	    "of rocks and boulders."));
    add_item( ({ "jumble", "ground", "rock",  "rocks", "boulder",
	"boulders", }),
	BSN("Rocks and boulders of all sizes lie tumbled "+
	"over the ground, as if they had fallen from the cliffs."));
    add_item( ({ "bramble", "brambles", "sprawling briar", "briar",
	"sprawling briars", "briars", }),
	BSN("Sprawling briars overrun the trail, making passage "+
	    "difficult in spots."));
    add_item( ({ "long sharp-edged thorn", "long sharp-edged thorns", 
    	"long thorn", "long thorns", "sharp-edged thorn",
	"sharp-edged thorns", "thorn", "thorns", }),
	BSN("The briars are thick with long, sharp-edged thorns."));
    add_item( ({ "weathered stone", "stone", "limestone", }),
	BSN("The limestone of the cliffs has been badly eroded "+
	    "by wind and weather."));
    add_item( ({ "crumbling limestone cliff", "limestone cliff",
	"crumbling cliff", "cliff", "crumbling limestone cliffs", 
	"limestone cliffs", "crumbling cliffs", "cliffs", }),
	BSN("Limestone cliffs, crumbled and worn by weather, "+
	    "rise above the trail."));

    add_cmd_item( ({ "bramble", "brambles", "sprawling briar", "briar",
	"sprawling briars", "briars", }),
	({ "search", "enter", }),
	BSN("The thorns draw blood, and you abandon the attempt."));

    add_cmd_item( ({ "crumbling limestone cliff", "limestone cliff",
	"crumbling cliff", "cliff", "crumbling limestone cliffs", 
	"limestone cliffs", "crumbling cliffs", "cliffs", }),
	"climb",
	BSN("The limestone crumbles beneath your hands and "+
	    "you slide back to the ground."));

    add_cmd_item( ({ "rock",  "rocks", "boulder", "boulders", }),
	({ "shove", "push", "move", "roll", }),
	BSN("You push the nearest boulder with all your might, "+
	    "but it does not budge."));

    add_cmd_item( ({ "rock",  "rocks", "boulder", "boulders", }),
	"climb",
	BSN("You scramble among the boulders, but find "+
	    "nothing but briars."));

} /* create_gondor */
