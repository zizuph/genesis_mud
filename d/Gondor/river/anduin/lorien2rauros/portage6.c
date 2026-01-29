/*
 * /d/Gondor/river/anduin/lorien2rauros/portage6.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * near the middle of the portage trail
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";

#include <adverbs.h>
#include "/d/Gondor/defs.h"	/* always */

/* prototypes */
public void	create_gondor();
public void	init();
public int	do_listen(string arg);

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
	"A rocky trail threads a narrow clear space between limestone "+
	"cliffs and tumbled boulders. From the east, beyond the "+
	"boulders, comes a faint sound of rushing water.");

    set_tod_landtype("trail");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("portage5", "north", 0, 5);
    add_exit("portage7", "south", 0, 5);

    set_no_exit_msg( ({ "northwest", "west", "southwest", }),
	BSN("The cliffs are too steep to climb."));
    set_no_exit_msg( ({ "northeast", "east", "southeast", }),
	BSN("You scramble among the boulders, but cannot "+
	    "find any trail leading that way."));

    add_item( ({ "emyn muil", }),
	BSN("The weather-worn cliffs of the Emyn Muil loom over the "+
	    "trail."));
    add_item( ({ "path", "rocky trail", "trail", "land", }),
	BSN("The trail extends north and south under "+
	    "the lee of the cliffs."));
    add_item( ({ "narrow clear space", "clear space", "space", }),
	BSN("This space under the cliffs is clear of boulders, "+
	    "although there is a tumbled heap of rock and briar "+
	    "to the east."));
    add_item( ({ "one side", "side", "side of trail",  "heap",
	"tumbled heap", "ground", "rock", "rocks", "tumbled boulder",
	"tumbled boulders", "boulder", "boulders", }),
	BSN("Rocks and boulders of all sizes lie heaped "+
	"to one side of the trail."));
    add_item( ({ "bramble", "brambles", "sprawling briar", "briar",
	"sprawling briars", "briars", }),
	BSN("A few briars grow among the tumbled boulders."));
    add_item( ({ "thorn", "thorns", }),
	BSN("The briars have thorns as long as your index finger."));
    add_item( ({ "weathered stone", "stone", "limestone", }),
	BSN("The limestone of the cliffs is crumbling and soft."));
    add_item( ({ "weather-worn cliff", "limestone cliff",
	"cliff", "weather-worn cliffs", "limestone cliffs", "cliffs", }),
	BSN("Limestone cliffs, crumbled and worn by weather, "+
	    "rise above the trail."));

    add_cmd_item( ({ "bramble", "brambles", "sprawling briar", "briar",
	"sprawling briars", "briars", }),
	({ "search", "enter", }),
	BSN("The thorns draw blood, and you abandon the attempt."));

    add_cmd_item( ({ "weather-worn cliff", "limestone cliff",
	"cliff", "weather-worn cliffs", "limestone cliffs", "cliffs", }),
	"climb",
	BSN("The cliffs are too steep and the stone friable -- "+
	    "you make no progress at all."));

    add_cmd_item( ({ "heap", "rock",  "rocks", "boulder", "boulders", }),
	({ "shove", "push", "move", "roll", }),
	BSN("You push a few of the boulders, but they don't move."));

    add_cmd_item( ({ "heap", "rock",  "rocks", "boulder", "boulders", }),
	"climb",
	BSN("You scramble among the boulders, but find "+
	    "nothing but briars."));

} /* create_gondor */


/*
 * Function name:	init
 * Description	:	add 'listen'
 */
public void
init()
{
    ::init();
    add_action(do_listen, "listen");
} /* init */


/*
 * Function name:	do_listen
 * Description	:	let 'em listen 
 *			XXX replace with gilmanor's when ready
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success or plausible failure,
 *			0 if we really really think they meant the
 *			soul command.
 */
public int
do_listen(string arg)
{
    string	tmpstr;

    if (!strlen(arg))
    {
	WRITE("You hear the hiss and rumble of racing water, "+
	   "somewhere to the east.");
	return 1;
    }

    arg = LOW(arg);
    if (arg == "." ||
        strlen(FULL_ADVERB(arg)))
    {
         return 0;	/* fall thru to soul */
    }

    if (parse_command(arg, ({}),
	"[to] [the] [faint] 'sound' / 'hiss' / 'rumble' "+
	"[of] [the] [racing] [water]"))
    {
	WRITE("You hear the hiss and rumble of racing water, "+
	   "somewhere to the east.");
    }
    else
    {
	write("Listen to what?\n");
    }
    return 1;
} /* do_listen */
