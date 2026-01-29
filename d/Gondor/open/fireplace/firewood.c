/*
 * /d/Gondor/open/fireplace/firewood.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * simple firewood for use by rooms inheriting 
 *	/d/Gondor/open/fireplace/fireplace.c
 *
 * not using the ranger firewood because the campfires are a
 * ranger privilege and should not be generally available.
 * this wood will only burn in containers (fireplaces, kilns,
 * fire pits, forges, ...), not in piles on the ground.
 * however, ranger firewood will also work in fireplaces.
 */


#pragma strict_types

inherit "/std/heap";

#include <stdproperties.h>	/* for HEAP_* 	*/

#define BSN(x)           (break_string((x), 75) + "\n")
#define NF0(x)           { notify_fail(x); return 0; }
#define WRITE(x)         write(BSN(x))

/* prototypes */
public void	create_heap();
public void	init();
public int	light_wood(string arg);


/*
 * Function name:	create_heap
 * Description	:	set up the firewood
 */
public void
create_heap()
{
    set_name("firewood");
    add_name("wood");
    set_short("piece of firewood");
    set_pshort("pieces of firewood");
    set_long(BSN("The wood is gray and splintery, with bits of bark "+
	"still attached."));
    set_heap_size(1);

    add_prop(HEAP_I_UNIT_WEIGHT, 1360);	/* 3 lbs */
    add_prop(HEAP_I_UNIT_VOLUME, 5244);	/* 20" x 4" x 4" */
    add_prop(HEAP_I_UNIT_VALUE, 1);
    add_prop(HEAP_S_UNIQUE_ID, "_gondor_firewood_");
} /* create_heap */


/*
 * Function name:	init
 * Description	:	add light/burn verbs
 */
public void
init()
{
    ::init();
    add_action(light_wood, "light");
    add_action(light_wood, "burn");
} /* init */


/*
 * Function name:	light
 * Description	:	handle (futile) attempts to burn/light wood
 * Argument	:	string arg -- whatever they typed
 * Returns	:	1 if we understand arg, 0 if not
 */
public int
light_wood(string arg)
{
    if ( arg == "wood" || arg == "firewood" ||
    arg == "piece of firewood" || arg == "pieces of firewood" )
    {
	WRITE("You should place the wood in a fireplace "+
	    "before trying to "+query_verb()+" it.");
	return 1;
    }
    NF0(query_verb()+" what?\n");
} /* light_wood */
