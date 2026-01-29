/*
 * File		:	/d/Genesis/new/start/human/town/breakwater1.c
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
    set_short("breakwater");
    set_long(BSN(
	"beginning of the breakwater, which will extend west or "+
	"southwest. breakwater is stone, as "+
	"opposed to the paved quayside road to the ne. "+
	"public warehouse to northeast, breakwater is extending out "+
	"into water, so protected cove is northwest and open "+
	"seas to south/southeast."));

    add_exit((TOWN + "quay_south3"), "northeast");

} /* create_room */
