/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom16w.c
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
	BSN("The dark, rocky waters seem to flow from north to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir( ({ "north", "northeast" }) );
    set_downstreamdir( ({ "south", "southeast" }) );
    set_currentstr( ({ 7, 7 }) ); /* rough */ 
    set_rock_density(ROCKY - 1);
    add_exit("river16w", "up");
    add_exit("riverbottom16e", "east");
    add_exit("riverbottom15w", "north");
    add_exit("riverbottom15e", "northeast");
    add_exit("riverbottom17w", "south");
    add_exit("riverbottom17e", "southeast");
    set_distance("north", 25);
    set_distance("northeast", 25);
    set_distance("south", 12);
    set_distance("southeast", 12);
} /* create_anduin_underwater */
