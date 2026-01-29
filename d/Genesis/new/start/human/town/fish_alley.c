/*
 * File		:	/d/Genesis/new/start/human/town/fish_alley.c
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
    set_short("alley");
    set_long(BSN(
	"alley running along south side of public warehouse."));

    add_exit((TOWN + "fish_hut"), "east");
    add_exit((TOWN + "quay_south3"), "west");

} /* create_room */
