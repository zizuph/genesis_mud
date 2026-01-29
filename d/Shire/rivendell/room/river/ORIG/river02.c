/*
 * /d/Shire/rivendell/room/river/river02.c
 *
 * river rooms only reached by being flooded out of the ford
 * for evil alignment.
 *
 */

#pragma strict_types

inherit "/d/Shire/rivendell/room/river/river";

#include <stdproperties.h>
#include "local.h"

#define	NO_GONDOR_DEFS
#include "/d/Gondor/std/water/onwater.h"


public void	create_river();


/*
 * Function name:	create_river
 * Description	:	set up the river
 */
public void
create_river()
{
    /* XXX short & long descs */

    set_upstreamdir("northeast");
    set_downstreamdir("southwest");

    add_exit("river01", "northeast", block_exit, 10);
    add_exit("river03", "southwest", block_exit, 10);
    add_exit("riverbottom02", "down", block_exit, 10);
} /* create_river */
