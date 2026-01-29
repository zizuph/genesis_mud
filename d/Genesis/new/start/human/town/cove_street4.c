/*
 * File		:	/d/Genesis/new/start/human/town/cove_street4.c
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
    set_short("narrow cobbled street");
    set_long(BSN(
	"steep narrow street leading uphill from cove. "+
	"hill levels out a bit here, where this street intersects the "+
	"main street of shops which runs north-south. this street "+
	"continues uphill towards houses at the top of the bluff."));

    add_exit((TOWN + "shops_street2"), "north");
    add_exit((TOWN + "cove_street5"), "northeast");
    add_exit((TOWN + "shops_street3"), "south");
    add_exit((TOWN + "cove_street3"), "northwest");

} /* create_room */
