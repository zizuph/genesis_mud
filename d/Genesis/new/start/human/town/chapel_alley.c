/*
 * File		:	/d/Genesis/new/start/human/town/chapel_alley.c
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
	"an alley (or just an open area?) behind harbour office, "+
	"between quayside road and wall of chapel yard.  probably "+
	"should make 'em 'climb' to enter chapel yard."));

    add_exit((TOWN + "chapel_yard"), "east", 0, 2, 1);
    add_exit((TOWN + "quay_north1"), "southwest", 0, 2, 1);

} /* create_room */
