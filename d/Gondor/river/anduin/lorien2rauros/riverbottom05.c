/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom05.c
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
	BSN("The dark waters seem to flow from northwest to southeast."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("northwest");
    set_downstreamdir("southeast");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river05", "up");
    add_exit("riverbottom04", "northwest");
    add_exit("riverbottom06", "southeast");
    set_distance("northwest", 20);
    set_distance("southeast", 25);
} /* create_anduin_underwater */
