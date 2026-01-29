/*
 * File		:	/d/Genesis/new/start/human/town/rhouse2_enter.c
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
	"placeholder for rooming house. could have long wooden "+
	"stairs (hidden) down to beach at base of cliffs. better "+
	"still, the stairs could run from cellar down *inside* "+
	"stone of cliffs to emerge in cave at foot, like the "+
	"stairs in the seashell shop in la jolla."));

    add_exit((TOWN + "shops_street4"), "north");

} /* create_room */
