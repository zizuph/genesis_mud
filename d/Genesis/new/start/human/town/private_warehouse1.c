/*
 * File		:	/d/Genesis/new/start/human/town/private_warehouse1.c
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
    set_short("private warehouse");
    set_long(BSN(
	"private warehouse for timber exporter. good-sized (carts "+
	"have to be able to unload indoors), altho not as large as "+
	"the public warehouse. to west (or north?) big doors open "+
	"directly onto water, with some kind of hoist mechanism "+
	"suspended from beam projecting from warehouse wall, up "+
	"near the roof, to allow direct load/unload of ships. "+
	"stacks of timber, some kind of loft or at least ladder to "+
	"allow access to hoist mechanism for maintenance. maybe small "+
	"office area for factor and night guard."));

    add_exit((TOWN + "quay_north1"), "south");

} /* create_room */
