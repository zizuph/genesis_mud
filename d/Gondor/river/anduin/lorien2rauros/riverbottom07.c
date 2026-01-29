/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom07.c
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
	BSN("The dark waters seem to flow from north to southwest."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("southwest");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river07", "up");
    add_exit("riverbottom06", "north");
    add_exit("riverbottom08", "southwest");
    set_distance("north", 25);
    set_distance("southwest", 30);
} /* create_anduin_underwater */


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give a "the river bends" msg
 *			if people or boats are going upstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- "swim", "wade", "row", "dive", "wash"
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "north" ||
	dir == "upstream")
    {
	desc = BSN("As you travel upstream, "+
	           "the Anduin bends to the northwest.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
