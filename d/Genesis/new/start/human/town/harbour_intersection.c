/*
 * File		:	/d/Genesis/new/start/human/town/harbour_intersection.c
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
	"on an 8-foot-wide (??) stone quayside road. "+
	"wooden piers extend west into the cove.  road leads north "+
	"and south.  directly east, a street heads up a fairly steep hill. "+
	"to the right (south) is the corner of a large stone warehouse, "+
	"to the left, a bit uphill, a wooden building."));

    add_exit((TOWN + "quay_north1"), "north");
    add_exit((TOWN + "cove_street1"), "east");
    add_exit((TOWN + "quay_south1"), "south");
    add_exit((TOWN + "north_piers1"), "west", not_yet);

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
