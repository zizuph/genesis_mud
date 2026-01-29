/*
 * File		:	/d/Genesis/new/start/human/town/quay_south1.c
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
	"quayside road south of harbour intersection. wall of "+
	"public warehouse is to east, entrance further south."));

    add_exit((TOWN + "harbour_intersection"), "north");
    add_exit((TOWN + "quay_south2"), "south");

} /* create_room */
