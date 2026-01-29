/*
 * /d/Gondor/river/anduin/carrock2lorien/riverbottom10.c
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
	BSN("The dark waters seem to flow southwest."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("northeast");
    set_downstreamdir("southwest");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river10", "up");
    add_exit("riverbottom09", "northeast");
    add_exit("riverbottom11", "southwest");
    set_distance("northeast", 40);
    set_distance("southwest", 30);
} /* create_anduin_underwater */
