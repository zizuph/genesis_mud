/*
 * File		:	/d/Genesis/new/start/human/town/cove_street2.c
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
	"harbour office is to northwest, and lane leads north "+
        "towards sailors' chapel. from here, street makes a "+
        "sharp northeast-southeast uphill jog. to the west, it "+
        "descends straight towards the water."));

    add_exit((TOWN + "chapel_lane"), "north");
    add_exit((TOWN + "cove_street3"), "northeast");
    add_exit((TOWN + "cove_street1"), "west");

} /* create_room */
