/*
 * File		:	/d/Genesis/new/start/human/town/2nd_hand_shop.c
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
    set_short("2nd_hand_shop");
    set_long(BSN(
	"placeholder for 2nd_hand_shop."));

    add_exit((TOWN + "shops_street4"), "west");

} /* create_room */
