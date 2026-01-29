#pragma strict_types
/*
 * ~/arc_ne.c
 *
 * Northeast Arcade
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
    set_short("Northeast Arcade");
    set_long("The northeastern section of the arcade which circles the "+
	"public bath. Fingers of mist curl around the pedestals of "+
	"the columns that support a series of arches through which "+
	"the pool of water can be glimpsed. To the northeast is a "+
	"heavy door with a number carved into the wood.\n"); 

    ARCADE;

    add_item("number", "It is the number 7.\n");
    add_cmd_item("number", "read", "It is the number 7.\n");

    add_exit(BATHRM + "arc_e", "southeast");
    add_exit(BATHRM + "arc_n", "northwest");

    add_npc(BATH + "npc/attendant", 1, &->equip_me());

    bath_door("seven", "priv_7", "ne");
}
