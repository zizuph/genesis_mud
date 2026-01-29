/*
 * /d/Gondor/river/anduin/carrock2lorien/gladdenrbottom.c
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
	BSN("The dark waters seem to flow from east " +
	    "to est."));

    set_watertype("river");
    set_waterrefs( ({ "waters", "water", "river", "gladden",
	"river gladden", "gladden river", "river ninglor",
	"ninglor river", "ninglor", }) );
    set_upstreamdir("west");
    set_downstreamdir("east");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("gladdenr", "up");
    add_exit("riverbottom06", "east");
    set_distance("east", 1);

    set_no_exit_msg("west",
	BSN("The current is swift, and you can make no headway."));
} /* create_anduin_underwater */
