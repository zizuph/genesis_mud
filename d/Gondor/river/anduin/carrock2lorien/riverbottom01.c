/*
 * /d/Gondor/river/anduin/carrock2lorien/riverbottom01.c
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
	BSN("The dark waters seem to flow from northwest and northeast "+
	    "to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir( ({ "northwest", "northeast" }) );
    set_downstreamdir("south");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river01", "up");
    add_exit("river00", "northeast");
    add_exit("riverbottom02", "south");
    set_distance("south", 15);

    set_no_exit_msg("northwest",
	BSN("The current is too strong for you to travel northwest."));

} /* create_anduin_underwater */

/*
 * Function name:	msgs_before_move
 * Description	:	write a you-rise msg when swim upstream
 * Arguments	:	string vb -- player verb
 *			string dir -- direction of movement
 *			int ashore -- 1 if moving to shore
 */
public void
msgs_before_move(string vb, string dir, int ashore)
{
    ::msgs_before_move(vb, dir, ashore);
    if (dir == "northeast" ||
	dir == "upstream")
    {
	WRITE("The water grows shallow, and you rise to the surface.");
    }
} /* msgs_before_move */
