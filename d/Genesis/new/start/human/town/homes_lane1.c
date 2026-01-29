/*
 * File		:	/d/Genesis/new/start/human/town/homes_lane1.c
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
    set_short("lane along top of bluff");
    set_long(BSN(
	"end of lane along top of bluff. houses (or walls of grounds) "+
	"to east and north, steep hill to west."));

    add_exit((TOWN + "homes_lane2"), "south");

} /* create_room */
