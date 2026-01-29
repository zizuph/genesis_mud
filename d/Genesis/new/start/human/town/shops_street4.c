/*
 * File		:	/d/Genesis/new/start/human/town/shops_street4.c
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
	"south end of shops street. second hand shop (general stuff) "+
	"to east, fish shop to west, rooming house to south. "+
	"of course, we won't just tell them what everything is flat out, "+
	"but will rather describe what they see and let them draw "+
	"the appropriate conclusions."));

    add_exit((TOWN + "shops_street3"), "north");
    add_exit((TOWN + "2nd_hand_shop"), "east");
    add_exit((TOWN + "rhouse2_enter"), "south");
    add_exit((TOWN + "fish_shop"), "west");

} /* create_room */
