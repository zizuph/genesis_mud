/*
 * File		:	/d/Genesis/new/start/human/town/shops_street1.c
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
	"north end of shops street. smithy to north, bank to west, "+
	"guild to east.  of course, we won't just tell them what everything "+
	"is flat out, "+
	"but will rather describe what they see and let them draw "+
	"the appropriate conclusions."));

    add_exit((TOWN + "smithy"), "north");
    add_exit((TOWN + "adv_guild"), "east");
    add_exit((TOWN + "shops_street2"), "south");
    add_exit((TOWN + "bank"), "west");

} /* create_room */
