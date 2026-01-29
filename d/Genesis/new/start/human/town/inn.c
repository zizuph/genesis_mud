/*
 * File		:	/d/Genesis/new/start/human/town/inn.c
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
    set_short("inn");
    set_long(BSN(
	"placeholder for inn. pretty substantial, expensive inn, "+
	"perched up at the top of the bluff."));

    add_exit((TOWN + "cove_street5"), "north");

} /* create_room */
