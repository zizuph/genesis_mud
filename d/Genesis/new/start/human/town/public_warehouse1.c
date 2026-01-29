/*
 * File		:	/d/Genesis/new/start/human/town/public_warehouse1.c
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
    set_short("public warehouse");
    set_long(BSN(
	"public warehouse.  since this leases space to various "+
	"merchants/traders, it's probably quite large. some "+
	"merchants buy & sell from here, rather than incurring "+
	"the expense of a separate shop. since there's no outside "+
	"yard, there must be room inside for carts to drive in and "+
	"unload. probably several rooms, good place for hidden stuff "+
	"like trapdoors to water below, ladders up to loft, etc."));

    add_exit((TOWN + "quay_south2"), "west");

} /* create_room */
