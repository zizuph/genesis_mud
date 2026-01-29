/*
 * File		:	/d/Genesis/new/start/human/town/bank.c
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
    set_short("bank");
    set_long(BSN(
	"placeholder for bank."));

    add_exit((TOWN + "shops_street1"), "east");

} /* create_room */
