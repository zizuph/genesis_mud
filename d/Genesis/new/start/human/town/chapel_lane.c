/*
 * File		:	/d/Genesis/new/start/human/town/chapel_lane.c
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
    set_short("narrow lane");
    set_long(BSN(
	"narrow lane (unpaved?) runs from main street to "+
	"sailors' chapel. harbour office is to west. what's along "+
	"east side of lane?  steep hillside? brush? maybe something fun "+
	"hidden for diligent, observant mortals???"));

    add_exit((TOWN + "chapel_yard"), "north");
    add_exit((TOWN + "cove_street2"), "south");

} /* create_room */
