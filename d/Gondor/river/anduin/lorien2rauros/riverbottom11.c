/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom11.c
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
	BSN("The dark waters seem to flow from northeast to southwest."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("northeast");
    set_downstreamdir("southwest");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river11", "up");
    add_exit("riverbottom10", "northeast");
    add_exit("riverbottom12", "southwest");
    set_distance("northeast", 20);
    set_distance("southwest", 33);
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
    string	desc;
    if (dir == "northeast" ||
	dir == "upstream")
    {
	desc = BSN("As you travel upstream, "+
	           "the river bends more to the north.");
    }
    else if (dir == "southwest" ||
	     dir == "downstream")
    {
    	desc = BSN("As you travel downstream, the river curves "+
	           "from southwest to southeast.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
