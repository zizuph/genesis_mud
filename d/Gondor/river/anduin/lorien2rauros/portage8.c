/*
 * /d/Gondor/river/anduin/lorien2rauros/portage8.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * near the south end of the portage trail
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
 * Description	:	set up the trail
 */
public void
create_gondor()
{
    set_short("a narrow trail");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"A narrow trail threads its way through jumbled scree "+
	"along the base of weather-worn limestone cliffs.");

    set_tod_landtype("trail");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("portage7", "northwest", 0, 5);
    add_exit("beach22w", "east", move_msg, 5);

    set_no_exit_msg( ({ "west", "southwest", "south", "southeast", }),
	BSN("The cliffs are too steep to climb."));
    set_no_exit_msg( ({ "northeast", "north", }),
	BSN("You wander among the scree, but can find no other path."));

    add_item( ({ "emyn muil", }),
	BSN("The cliffs of the Emyn Muil rise above the scree."));
    add_item( ({ "path", "narrow trail", "trail", "land", }),
	BSN("The trail winds through the scree to run close under "+
	    "the shelter of the cliffs."));
    add_item( ({ "base", "boulder", "boulders", "rock", "rocks",
	"heap", "heap of scree", "jumbled scree", "scree", }),
	BSN("Rocks and boulders of all sizes are heaped at the "+
	    "base of the cliffs."));
    add_item( ({ "ground", }),
	BSN("The ground is covered with rocks and boulders."));
    add_item( ({ "weather-worn cliff", "limestone cliff",
	"cliff", "weather-worn cliffs", "limestone cliffs", "cliffs", }),
	BSN("The cliffs, crumbled and worn by weather, run "+
	    "along the trail to the south and west."));
    add_item( ({ "weathered stone", "stone", "limestone", }),
	BSN("The limestone of the cliffs is weathered and worn."));

    add_cmd_item( ({ "boulder", "boulders", "rock", "rocks",
	"jumbled scree", "scree", }),
	({ "shove", "push", "move", "roll", }),
	BSN("You push one of the smaller rocks over, but "+
	    "have little effect on the heap of scree."));

    add_cmd_item( ({ "boulder", "boulders", "rock", "rocks",
	"jumbled scree", "scree", }),
	"climb",
	BSN("You scramble atop the scree for a moment, then "+
	    "return to the trail."));

    add_cmd_item( ({ "weather-worn cliff", "limestone cliff",
	"cliff", "weather-worn cliffs", "limestone cliffs", "cliffs", }),
	"climb",
	BSN("The cliffs are too steep and the limestone too friable "+
	    "for you to ascend."));

} /* create_gondor */


/*
 * Function name:	move_msg
 * Description	:	write msg about transition from trail to beach
 * Returns	:	0 -- always (exit is allowed)
 */
public int
move_msg()
{
    if (QVB == "east")
    {
	WRITE("You follow the trail east through the scree "+
	   "to emerge on a stony beach.");
    }
    return 0;
} /* move_msg */
