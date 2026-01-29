/*
 * File		:	/d/Genesis/new/start/human/town/harbour_office.c
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
    set_short("harbour office");
    set_long(BSN(
	"placeholder for harbour office."));

    add_exit((TOWN + "cove_street1"), "south");

} /* create_room */
