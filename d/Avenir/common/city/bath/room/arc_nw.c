#pragma strict_types
/*
 * ~/arc_nw.c
 *
 * Northwest Arcade
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
    set_short("Northwest Arcade");
    set_long("The northwestern section of the arcade which circles the "+
	"public bath. Mist curls around the pedestals of the "+
	"columns that support arches through which the pool of water "+
	"can be glimpsed. To the northwest is a heavy door with a "+
	"number inscribed into the wood.\n"); 

    add_item("number", "It is the number 4.\n");
    add_cmd_item("number", "read", "It is the number 4.\n");

    ARCADE;

    add_exit(BATHRM + "arc_w", "southwest");
    add_exit(BATHRM + "arc_n", "northeast");

    add_npc(BATH + "npc/servant", 1, &->equip_me());

    bath_door("four", "priv_4", "nw");
}
