/*
 * File		:	/d/Genesis/new/start/human/town/pub1.c
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
    set_short("rooming house entrance");
    set_long(BSN(
	"placeholder for pub. like the rooming house across the "+
	"street, this is probably not a posh establishment."));

    add_exit((TOWN + "cove_street3"), "north");

} /* create_room */
