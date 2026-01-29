/*
 * a placeholder for nen hithoel
 */

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
    set_short("a placeholder for nen hithoel");
    set_long("A placeholder for nen hithoel.\n");

    set_watertype("lake");
    set_watername("Nen Hithoel");
    set_waterrefs( ({ "waters", "water", "lake", "nen hithoel" }) );
    set_downstreamdir("south");
    set_upstreamdir("north");
    set_currentstr(6);	/* rapid */
    set_depth(1220);	/* 40 feet */
    add_exit("river24", "north");
    add_exit("placeholder", "south");
} /* create_onwater */
