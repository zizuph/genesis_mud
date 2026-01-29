/*
 * File		:	/d/Genesis/new/start/human/town/chapel_yard.c
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
	"yard of sailors' chapel. graves are here, presumably. "+
	"maybe a small herb garden? some kind of access (climb wall?) "+
	"to non-obvious exit to west. and, of course, entrance "+
	"to the chapel ..."));

    add_exit((TOWN + "chapel_lane"), "south");
    add_exit((TOWN + "chapel_alley"), "west", 0, 2, 1);

} /* create_room */
