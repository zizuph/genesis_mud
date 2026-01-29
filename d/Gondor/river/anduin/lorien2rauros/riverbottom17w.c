/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom17w.c
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
	BSN("The dark, rocky waters seem to flow from north to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir( ({ "north", "northeast" }) );
    set_downstreamdir( ({ "south", "southeast" }) );
    set_currentstr( ({ 7, 7 }) ); /* rough */ 
    set_rock_density(ROCKY);
    add_exit("river17w", "up");
    add_exit("bay17", "west");
    add_exit("riverbottom17e", "east");
    add_exit("riverbottom16w", "north");
    add_exit("riverbottom16e", "northeast");
    add_exit("river18", "south");
    add_exit("river18", "southeast");
    set_distance("north", 12);
    set_distance("northeast", 12);
} /* create_anduin_underwater */


/*
 * Function name:	msgs_before_move
 * Description	:	write a you-rise msg when swim west
 *			or downstream
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
    else if (dir == "south" ||
	     dir == "southeast")
    {
	WRITE("The churning waters tumble you to the surface.");
    }
} /* msgs_before_move */
