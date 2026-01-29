/*
 * /d/Gondor/common/doc/examples/forest/forest2.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * Example of using a master room
 *
 * This room adds a short and a long description to what's 
 * inherited from forest_master.c, and a custom description 
 * for "mushroom".
 */

#pragma strict_types

inherit "/d/Gondor/common/doc/examples/forest/forest_master";

#include "/d/Gondor/defs.h"	/* always */

/* prototypes */
public void	create_forest();


/*
 * Function name:	create_forest
 * Description	:	set up the forest room
 */
public void
create_forest()
{
    set_short("A stand of trees in the northern part of the Dark " +
        "Wood");
    set_tod_long(
        "Oaks and beeches are mingled here, with thick bushes "+
        "growing among them. The bushes seem thinner to the "+
	"southeast.");

    add_item( ({ "mushroom", "mushrooms" }), BSN(
	"Tiny mushrooms with bright red caps grow at the foot " +
	"of the oaks."));


    add_exit("forest1", "southeast");
} /* create_forest */
