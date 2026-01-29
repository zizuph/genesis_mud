/*
 * File		:	/d/Genesis/new/start/human/town/fish_hut.c
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
    set_short("hut");
    set_long(BSN(
	"a *very* rough stew-and-grog hut -- "+
	"an extremely dubious shack, where you're never sure exactly "+
	"what's in the stew or the grog.  perhaps only the stew is "+
	"sold openly, and you have to know to ask for the grog."));

    add_exit((TOWN + "fish_alley"), "west");

} /* create_room */
