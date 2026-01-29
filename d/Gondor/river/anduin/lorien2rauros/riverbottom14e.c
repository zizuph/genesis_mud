/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom14e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_underwater";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/underwater.h"
#include "../anduin.h"

/* prototypes */
public void	create_anduin_underwater();


/*
 * Function name:	create_anduin_underwater
 * Description	:	create the room
 */
public void
create_anduin_underwater()
{
    set_short("underwater");
    set_long("Underwater.\n"+
	BSN("The waters seem to flow from north to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir( ({ "south", "southwest" }) );
    set_currentstr( ({ 6, 6 }) ); /* rapid */ 
    set_rock_density(SCATTERED_ROCKS + 1);
    add_exit("river14e", "up");
    add_exit("riverbottom13e", "north");
    add_exit("riverbottom14w", "west");
    add_exit("riverbottom15e", "south");
    add_exit("riverbottom15w", "southwest");
    set_distance("south", 25);
    set_distance("southwest", 25);
    set_distance("north", 20);
} /* create_anduin_underwater */
