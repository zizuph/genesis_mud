/*
 * /d/Shire/rivendell/room/river/river03.c
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

#ifdef NOTYET
#define LANDING_DEST ONE_OF_LIST(({"landing01",\
                                   "landing02",\
                                   "landing03",\
                                   "landing03",\
                                   "landing04",\
                                   "landing05"}))
#else /* NOTYET */
#define LANDING_DEST ONE_OF_LIST(({"tmp3",\
                                   "tmp4",\
                                   "tmp5"}))
#endif /* NOTYET */


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
    set_downstreamdir("west");	/* "downstream" onto shore :-) */

    add_exit("river02", "northeast", block_exit, 10);
    add_exit(RIVER_DIR + LANDING_DEST, "west", 10);
    add_exit("riverbottom03", "down", block_exit, 10);
} /* create_river */
