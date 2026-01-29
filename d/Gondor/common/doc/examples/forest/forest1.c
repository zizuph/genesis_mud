/*
 * /d/Gondor/common/doc/examples/forest/forest1.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * Example of using a master room
 *
 * This room adds only a short and a long description to what's 
 * inherited from forest_master.c
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
    set_short("a forest glade");
    set_tod_long(
        "This shady glade is surrounded on all sides by tall, " +
        "solemn beeches. Dense, thorny bushes crowd the trunks " +
        "of the large trees, enclosing the area further. " +
        "Two narrow paths lead through the bushes out of the glade, " +
        "one going southwest and the other northwest.");

    add_exit("forest2", "northwest");
    add_exit("forest3", "southwest", no_exit);
} /* create_forest */
