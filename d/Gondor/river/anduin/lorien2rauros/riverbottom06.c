/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom06.c
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
	BSN("The dark waters seem to flow from northwest to southeast."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("northwest");
    set_downstreamdir("southeast");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river06", "up");
    add_exit("riverbottom05", "northwest");
    add_exit("riverbottom07", "southeast");
    set_distance("northwest", 25);
    set_distance("southeast", 25);
} /* create_anduin_underwater */


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give a "the river bends" msg
 *			if people are going downstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- the verb used
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "southeast" ||
	dir == "downstream")
    {
	desc = BSN("As you travel downstream, "+
	           "the Anduin bends towards the south.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
