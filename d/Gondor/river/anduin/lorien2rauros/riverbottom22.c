/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom22.c
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
public int	no_way();
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
	BSN("The dark waters seem to flow from north to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("south");
    set_currentstr(6);	/* rapid */
    add_exit("river22", "up");
    add_exit("riverbottom21", "north", no_way);
    add_exit("riverbottom23", "south");
    add_exit("pool22", "west");
    set_distance("south", 20);
} /* create_anduin_underwater */


/*
 * Function name:	no_way
 * Description	:	exit efunc to block attempts to swim north
 * Returns	:	1 -- exit always fails
 */
public int
no_way()
{
    WRITE("You attempt to swim upstream, but the current is "+
	"much too strong and you make no progress at all.");
    return 1;
} /* no_way */


/*
 * Function name:	msgs_before_move
 * Description	:	write a you-rise msg when swim west
 * Arguments	:	string vb -- player verb
 *			string dir -- direction of movement
 *			int ashore -- 1 if moving to shore
 */
public void
msgs_before_move(string vb, string dir, int ashore)
{
    ::msgs_before_move(vb, dir, ashore);
    if (dir == "west")
    {
        WRITE("The water becomes more shallow and you rise to the surface.");
    }
} /* msgs_before_move */
