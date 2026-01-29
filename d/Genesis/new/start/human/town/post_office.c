/*
 * File		:	/d/Genesis/new/start/human/town/post_office.c
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
    set_short("post_office");
    set_long(BSN(
	"placeholder for post_office."));

    add_exit((TOWN + "shops_street2"), "west");

} /* create_room */
