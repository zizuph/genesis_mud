/*
 *	/d/Gondor/open/examples/street.c
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"

#define THIS_DIR	(OPEN_DIR + "examples/")

static object  Npc;

public void	create_gondor();
public void	reset_room();


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("a narrow street");
    set_long("The narrow street runs between two rows of three- and " +
	     "four-storeyed houses.\n");

    /* you would add items and exits here ... */

    reset_room();
}


/*
 * Function name:	reset_room
 * Description	:	clone up a kid at reset
 */
public void
reset_room()
{
    Npc = clone_npc(Npc, (THIS_DIR + "kid"));
}
