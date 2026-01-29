/*
 * File		:	/d/Genesis/new/start/human/town/inside_gate.c
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
    set_short("inside town gate");
    set_long(BSN(
	"inside the gate of the town wall. wall runs north and south. "+
	"what's to the north and south? open land? grounds of houses "+
	"to north? do we want to let players walk south to cliffs? "+
	"while we're at it, what about this wall/gate --- are there "+
	"guards posted here all the time, or does it stand open unless "+
	"there's some trouble?"));

    add_exit((TOWN + "cove_street5"), "west");

} /* create_room */
