/*
 * /d/Gondor/river/anduin/carrock2lorien/gladdenmbottom.c
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
    set_long("Underwater.\n" +
	BSN("The dark waters seem to flow from north " +
	    "to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river",
	"anduin", "river anduin", "anduin river" }) );
    set_upstreamdir( ({ "north", "west" }) );
    set_downstreamdir("south");
    set_downstreamdir("south");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("gladdenm", "up");
    add_exit("riverbottom06", "north");
    set_distance("north", 35);
    add_exit("gladdenrbottom", "west");
    set_distance("west", 1);
    add_exit("riverbottom07", "south");
    set_distance("south", 40);
} /* create_anduin_underwater */
