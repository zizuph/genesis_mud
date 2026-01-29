/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom23.c
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
    set_upstreamdir("north");
    set_downstreamdir("south");
    set_currentstr(6);	/* rapid */
    add_exit("river23", "up");
    add_exit("riverbottom22", "north");
    add_exit("riverbottom24", "south");
    set_distance("north", 20);
    set_distance("south", 20);
} /* create_anduin_underwater */
