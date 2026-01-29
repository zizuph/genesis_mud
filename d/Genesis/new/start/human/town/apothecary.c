/*
 * File		:	/d/Genesis/new/start/human/town/apothecary.c
 * Creator	:
 * Copyright	:
 * Date		:	3-oct-1998
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
    set_short("apothecary");
    set_long(BSN(
	"placeholder for apothecary."));

    add_exit((TOWN + "shops_street3"), "west");

} /* create_room */
