#pragma strict_types
/*
 * ~/arc_sw.c
 *
 * Southeast Arcade
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Grace,  Aug 1994: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../bath.h" 
inherit BATH_ROOM;

static void
create_bath_room(void)
{
    set_short("Southwest Arcade");
    set_long("The southwestern section of the arcade which circles the "+
	"public bath. Fingers of mist curl around the pedestals of "+
	"the columns that support a series of arches through which "+
	"the pool of water can be seen. To the southwest is a heavy "+
	"door with a number carved into the wood.\n"); 

    add_item("number", "It is the number 1.\n");
    add_cmd_item("number", "read", "It is the number 1.\n");

    ARCADE;

    add_exit(BATHRM + "arc_m", "southeast");
    add_exit(BATHRM + "arc_w", "northwest");

    bath_door("one", "priv_1", "sw");
}
