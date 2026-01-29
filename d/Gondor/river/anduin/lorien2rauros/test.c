#pragma strict_types

inherit "/d/Gondor/std/water/onwater";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"

/* prototypes */
public void	create_onwater();


/*
 * Function name:	create_onwater
 * Description	:	set up the room
 */
public void
create_onwater()
{
    set_short("in a test pool");
    set_long("A test pool, very calm.\n");

    /* set up water stuff */
    set_watertype("pool");
    set_watername("Test Pool");
    set_waterrefs( ({ "pool", "test pool" }) );
    set_currentstr(0);	/* strong */
    set_depth(1524); /* 50 feet */

    add_exit("testbottom", "down");
} /* create_onwater */
