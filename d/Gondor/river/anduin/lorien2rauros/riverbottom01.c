/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom01.c
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
	BSN("The dark waters seem to flow from the north "
	  + "to the southeast."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("southeast");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit((CARROCK_TO_LORIEN_DIR+"riverbottom11"), "north");
    set_distance("north", 15);
    add_exit("river01", "up");
    add_exit("riverbottom02", "southeast");
    set_distance("southeast", 20);
} /* create_anduin_underwater */
