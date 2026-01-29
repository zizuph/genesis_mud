/*
 * File		:	/d/Genesis/new/start/human/town/cove_street5.c
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
	"top of bluff. street heads sharply downhill to the southwest, "+
	"towards the cove, and runs pretty much level to the east "+
	"towards the town wall.  to the north are private houses -- "+
	"clearly of the well-to-do, since they command a fine view from "+
	"up here. to the south is a prosperous-looking inn. "+
        "This is probably the departure point for transport to the "+
        "wizards tower."));

    add_exit((TOWN + "homes_lane2"), "north");
    add_exit((TOWN + "inside_gate"), "east");
    add_exit((TOWN + "inn"), "south");
    add_exit((TOWN + "cove_street4"), "southwest");

} /* create_room */
