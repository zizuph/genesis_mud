/*
 * File		:	/d/Genesis/new/start/human/town/rhouse1_enter.c
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
	"placeholder for rooming house. this one should have "+
	"a view of the chapel cemetery from its western windows, "+
	"so maybe we could work that into the name. probably not "+
	"a posh establishment, given that it's on main (noisy) "+
	"street and near harbour (smelly and noisy)."));

    add_exit((TOWN + "cove_street3"), "south");

} /* create_room */
