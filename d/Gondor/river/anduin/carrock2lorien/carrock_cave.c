/*
 * /d/Gondor/river/anduin/carrock2lorien/carrock_cave.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * "There was a little cave (a wholesome with a pebbly floor)
 * at the foot of the steps and near the end of the stony ford."
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>	/* for ROOM_I_* */
#include "/d/Gondor/defs.h"
#include "../anduin.h"

#define	MAX_PEBBLES	10	/* max pebbles per reset */
#define	PEBBLE_FILE	(RIVER_ANDUIN_DIR + "obj/pebble")

/* prototypes */
public void	create_gondor();
public void	reset_room();
public void	init();
public int	get_pebble(string arg);


/* global variables */
static int	Npebbles = MAX_PEBBLES;
static string	Get_arg;


/*
 * Function name:	create_gondor
 * Description	:	set up the cave
 */
public void
create_gondor()
{
    FIX_EUID;		/* will clone objects */
    set_short("cave");
    set_long(BSN(
	"The walls of this small cave curve gently overhead, and " +
	"and smooth pebbles lie underfoot. An opening " +
	"in the east wall leads out to a sandy beach."));

    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({ "cave", }),
	BSN("The cave is small, with smooth stone walls and a pebbly " +
	    "floor."));
    add_item( ({ "smooth stone wall", "smooth wall",
	"stone wall", "wall", "smooth stone walls", "smooth walls",
	"stone walls", "walls", }),
	BSN("The walls are quite smooth, gently curving and quite dry, "+
	    "despite the proximity of the Great River."));
    add_item( ({ "arch", "roof", "ceiling" }),
	BSN("The ceiling arches close overhead. Traces of smoke " +
	    "are visible on the smooth grey stone."));
    add_item( ({ "swirl", "swirls", "traces", "smoke", "traces of smoke" }),
	BSN("The stone of the ceiling is marked with sooty swirls, " +
	    "as if from a fire."));
    add_item( ({ "pebbly floor", "floor", "ground", }),
	BSN("The floor of the cave is covered with small " +
	    "brown pebbles."));
    add_item( ({ "dark grey stone", "dark stone", "grey stone",
	"stone", }),
	BSN("The dark grey stone of the cave is dry and smooth."));
    add_item( ({ "small brown pebble", "small pebble", "brown pebble",
	"pebble", "small brown pebbles", "small pebbles",
	"brown pebbles", "pebbles", }),
	BSN("The pebbles are light brown in colour, and perhaps an " +
	    "inch wide."));
    add_item( ({ "narrow fissure", "fissure", "narrow opening",
        "opening", }),
        "A narrow fissure leads from the cave out onto a sandy beach.");
    add_item( ({ "grey sand", "sand", "sandy beach", "beach", }),
        BSN("All that is visible through the fissure is grey sand leading " +
            "down to the river."));
    add_item( ({ "ford", "great river", "waters", "water",
        "river", "anduin", "river anduin", "anduin river" }),
        BSN("The river is barely visible from here -- it is just " +
            "a glimpse of swift-moving water beyond the sand."));
 

    add_exit("carrock_beach", "out");

    reset_room();
} /* create_gondor */


/*
 * Funtion name:	reset_room
 * Description	:	make pebbles available
 */
public void
reset_room()
{
    Npebbles = MAX_PEBBLES;
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add "get" verbs
 */
public void
init()
{
    ::init();
    add_action(get_pebble,	"get");
    add_action(get_pebble,	"take");
    add_action(get_pebble,	"pick");
    add_action(get_pebble,	"steal");
} /* init */


/*
 * Function name:	get_pebble
 * Description	:	respond to attempts to get pebbles
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we recognize the arg, 0 if not
 */
public int
get_pebble(string arg)
{
    object	ob;

    if (!strlen(arg))
    {
	return 0;
    }
    Get_arg = arg;

    arg = LOW(arg);
    if (parse_command(arg, ({}),
		      "[small] [brown] 'pebble' / 'pebbles'") &&
        !objectp(present("pebble", TO)))
    {
	if (Npebbles)
	{
	    --Npebbles;
	    ob = clone_object(PEBBLE_FILE);
	    write("You get a small brown pebble.\n");
	    SAY(" gets a pebble.");
	    if (ob->move(TP))
	    {
		write("Oops, you drop it.\n");
		SAY(" drops a pebble.");
		ob->move(TO, 1);
	    }
	}
	else
	{
	    WRITE("You look through the pebbles on the floor, " +
		"but none seems particularly interesting.");
	}
	return 1;
    }
    return 0;
} /* get_pebble */
