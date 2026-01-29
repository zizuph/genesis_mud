/*
 * File		:	/d/Genesis/new/start/human/town/quay_south2.c
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
	"south end of quayside road. entrance to public warehouse is to "+
	"east."));

    add_exit((TOWN + "quay_south1"), "north");
    add_exit((TOWN + "public_warehouse1"), "east");
    add_exit((TOWN + "quay_south3"), "southwest");

} /* create_room */
