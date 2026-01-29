/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom12.c
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
public string	scenery_msgs(object ob, string vb, string dir);


/*
 * Function name:	create_anduin_underwater
 * Description	:	create the room
 */
public void
create_anduin_underwater()
{
    set_short("underwater");
    set_long("Underwater.\n"+
	BSN("The dark waters seem to flow from northwest to the "+
	    "south and southeast."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir( ({ "southeast", "south" }) );
    set_upstreamdir("northwest");
    set_currentstr( ({ 5, 4 }) );	/* strong, brisk */
    set_rock_density(SCATTERED_ROCKS);

    add_exit("river12", "up");
    add_exit("riverbottom11", "northwest");
    add_exit("riverbottom13w", "south");
    add_exit("riverbottom13e", "southeast");
    set_distance("northwest", 33);
    set_distance("south", 2);
    set_distance("southeast", 2);
} /* create_anduin_underwater */

/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give a "the river bends" msg
 *			if people or boats are going downstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- the verb used
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "northwest" ||
	dir == "upstream")
    {
	desc = BSN("As you travel upstream, the river curves in "+
	           "a gradually narrowing arc from northwest "+
		   "to northeast.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
