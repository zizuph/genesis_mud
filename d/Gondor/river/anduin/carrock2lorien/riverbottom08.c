/*
 * /d/Gondor/river/anduin/carrock2lorien/riverbottom08.c
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
	BSN("The dark waters seem to flow from north "+
	    "to southwest."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("southwest");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river08", "up");
    add_exit("riverbottom07", "north");
    add_exit("riverbottom09", "southwest");
    set_distance("north", 30);
    set_distance("southwest", 25);
} /* create_anduin_underwater */
