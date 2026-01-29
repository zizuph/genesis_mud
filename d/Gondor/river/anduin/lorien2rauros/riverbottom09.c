/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom09.c
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
	BSN("The dark waters seem to flow from west to east."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("west");
    set_downstreamdir("east");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river09", "up");
    add_exit("riverbottom08", "west");
    add_exit("riverbottom10", "east");
    set_distance("west", 20);
    set_distance("east", 20);
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

    if (dir == "west" ||
	dir == "upstream")
    {
	desc = BSN("As you travel upstream, "+
	           "the river bends to the north.");
    }
    else if (dir == "east" ||
	     dir == "downstream")
    {
    	desc = BSN("As you travel downstream, the river gradually "+
	           "bends to the southeast.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
