/*
 * File		:	/d/Genesis/new/start/human/town/quay_north1.c
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


/*
 * Function name:	create_room
 * Description	:	set up the room
 */
public void
create_room()
{
    set_short("quayside road");
    set_long(BSN(
	"quayside road north of harbour intersection. side of "+
	"harbour office is up hill to east, road ends at entrance "+
	"to private warehouse to north. non-obvious exit to northeast "+
	"around harbour office towards sailors' chapel."));

    add_exit((TOWN + "private_warehouse1"), "north");
    add_exit((TOWN + "chapel_alley"), "northeast", 0, 2, 1);
    add_exit((TOWN + "harbour_intersection"), "south");

} /* create_room */
