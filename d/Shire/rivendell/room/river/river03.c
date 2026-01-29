/*
 * /d/Shire/rivendell/room/river/river03.c
 *
 * river rooms only reached by being flooded out of the ford
 * for evil alignment.
 *
 * 1998/10/04 Last update
 * 2011/08/07 Lavellan - Fixed destination
 */

#pragma strict_types

inherit "/d/Shire/rivendell/room/river/river";

#include <stdproperties.h>
#include "local.h"

#define	NO_GONDOR_DEFS
#include "/d/Gondor/std/water/onwater.h"

#define LANDING_DEST ONE_OF_LIST(({"forest80",\
                                   "forest81",\
                                   "forest82",\
                                   "forest83"}))

public void	create_river();


/*
 * Function name:	create_river
 * Description	:	set up the river
 */
public void
create_river()
{
    /* short & long descs */

    set_upstreamdir("northeast");
    set_downstreamdir("west");	/* "downstream" onto shore :-) */

    add_exit("river02", "northeast", block_exit, 10);
//    add_exit(RIVER_DIR + LANDING_DEST, "west", 10);
    add_exit(FOREST_DIR + LANDING_DEST, "west", block_exit, 10);
    add_exit("riverbottom03", "down", block_exit, 10);
} /* create_river */
