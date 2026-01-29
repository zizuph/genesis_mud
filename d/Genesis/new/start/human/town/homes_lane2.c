/*
 * File		:	/d/Genesis/new/start/human/town/homes_lane2.c
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
	"lane along top of bluff. hill drops sharply to west, "+
	"prosperous houses to east. houses are *not* open for the "+
	"dirty masses to wander thru. walled grounds on a few, perhaps, "+
	"so players could climb wall and explore gardens until their "+
	"trespass is detected and they are booted out."));

    add_exit((TOWN + "homes_lane1"), "north");
    add_exit((TOWN + "cove_street5"), "south");

} /* create_room */
