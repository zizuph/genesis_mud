/*
 * File		:	/d/Genesis/new/start/human/town/cove_street1.c
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
	"harbour office is to north -- small wooden building, "+
	"perhaps with cupola overlooking harbour. "+
	"wall of public warehouse to south."));

    add_exit((TOWN + "harbour_office"), "north");
    add_exit((TOWN + "cove_street2"), "east");
    add_exit((TOWN + "harbour_intersection"), "west");

} /* create_room */
