/*
 * /d/Gondor/river/anduin/carrock2lorien/riverbottom02.c
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
public void	msgs_before_move(string vb, string dir, int ashore);


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
	    "to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("south");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river02", "up");
    add_exit("riverbottom01", "north");
    add_exit("river03", "south");
    set_distance("north", 15);
    set_distance("south", 20);
} /* create_anduin_underwater */

/*
 * Function name:	msgs_before_move
 * Description	:	write a you-rise msg when swim downstream
 * Arguments	:	string vb -- player verb
 *			string dir -- direction of movement
 *			int ashore -- 1 if moving to shore
 */
public void
msgs_before_move(string vb, string dir, int ashore)
{
    ::msgs_before_move(vb, dir, ashore);
    if (dir == "south" ||
	dir == "downstream")
    {
	WRITE("The water grows shallow, and you rise to the surface.");
    }
} /* msgs_before_move */
