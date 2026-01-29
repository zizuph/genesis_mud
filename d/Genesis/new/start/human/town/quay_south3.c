/*
 * File		:	/d/Genesis/new/start/human/town/quay_south3.c
 * Creator	:
 * Copyright	:
 * Date		:	3-Oct-1998
 * Purpose	:	placeholder in "walkable map"
 * Related Files:
 * Comments	:
 * TODO		:
 *
 * Modifications:
 */

#pragma strict_types

inherit	"/std/room";

#include "town.h"

/* prototypes */
public void	create_room();
public int	not_yet();


/*
 * Function name:	create_room
 * Description	:	set up the room
 */
public void
create_room()
{
    set_short("quayside road");
    set_long(BSN(
	"south end of quayside road. public warehouse is to "+
	"northeast, stone breakwater is to southwest, some piers "+
	"extend into water to northwest. non-obvious "+
	"exit (alley?) alongside warehouse."));

    add_exit((TOWN + "quay_south2"), "northeast");
    add_exit((TOWN + "fish_alley"), "east", 0, 2, 1);
    add_exit((TOWN + "breakwater1"), "southwest");
    add_exit((TOWN + "south_piers1"), "northwest", not_yet);

} /* create_room */


/*
 * Function name:	not_yet
 * Description	:	block exit to parts that don't exist yet
 * Returns	:	1 -- exit always fails
 */
public int
not_yet()
{
    write("can't go there yet -- pier layout is still unknown.\n");
    return 1;
} /* not_yet */
