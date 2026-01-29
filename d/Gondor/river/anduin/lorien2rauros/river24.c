/*
 * /d/Gondor/river/anduin/lorien2rauros/river24.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * at the argonath
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include "../anduin.h"

/* prototypes */
public void	create_anduin_onwater();


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("at the argonath, 379 miles downstream from the silverlode."));

    set_short("on the River Anduin");
    set_long("On the River Anduin.\n"+
	BSN("... Frodo peering forward saw in the distance two great rocks "+
	    "approaching: like great pinnacles or pillars of stone "+
	    "they seemed. Tall and sheer and ominous they stood upon "+
	    "either side of the stream. A narrow gap appeared between "+
	    "them, and the River swept the boats towards it. ")+
	BSN("Waters continue swift, river narrows. there is definitely "+
	    "a chance of running yourself into one of the rocks."));

    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("south");
    set_upstreamdir("north");
    set_currentstr(6);	/* rapid */
    set_depth(305);	/* 10 feet */
    /* no rocks */
    /* no shore rooms */
    add_exit("river23", "north");
    set_distance("north", 20);
    add_exit("placeholder", "south");
    add_exit("riverbottom24", "down");
} /* create_anduin_onwater */
