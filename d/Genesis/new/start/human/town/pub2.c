/*
 * File		:	/d/Genesis/new/start/human/town/pub2.c
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
    set_short("pub2");
    set_long(BSN(
	"placeholder for pub2."));

    add_exit((TOWN + "shops_street3"), "east");

} /* create_room */
