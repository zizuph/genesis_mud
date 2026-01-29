/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom15w.c
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
	BSN("The dark waters seem to flow from north to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir( ({ "north", "northeast" }) );
    set_downstreamdir( ({ "south", "southeast" }) );
    set_currentstr( ({ 6, 6 }) ); /* rapid */ 
    set_rock_density(SCATTERED_ROCKS + 2);
    add_exit("river15w", "up");
    add_exit("riverbottom15e", "east");
    add_exit("riverbottom14w", "north");
    add_exit("riverbottom14e", "northeast");
    add_exit("riverbottom16w", "south");
    add_exit("riverbottom16e", "southeast");
    set_distance("north", 25);
    set_distance("northeast", 25);
    set_distance("south", 25);
    set_distance("southeast", 25);
} /* create_anduin_underwater */
