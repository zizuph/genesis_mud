/*
 * File		:	/d/Genesis/new/start/human/town/cove_street3.c
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
	"steep narrow street leading uphill from cove. "+
	"does a sharp jog here to ascend steep part of hill. "+
	"rooming house to north, pub to south."));

    add_exit((TOWN + "rhouse1_enter"), "north");
    add_exit((TOWN + "cove_street4"), "southeast");
    add_exit((TOWN + "pub1"), "south");
    add_exit((TOWN + "cove_street2"), "southwest");

} /* create_room */
