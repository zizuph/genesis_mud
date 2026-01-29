#pragma strict_types
/*
 * ~/arc_m.c
 *
 * Main Arcade
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
    set_short("Main Arcade");
    set_long("This is the beginning of the arcade which encircles the "+
	"public bathing pool. Fingers of mist wrap around the "+
	"pedestals of the columns that support a series of arches "+
	"through which the pool of water can be glimpsed to the "+
	"north.\n"); 

    ARCADE;

    add_exit(BATHRM + "corr",    "south");
    add_exit(BATHRM + "steps_s", "north");
    add_exit(BATHRM + "arc_se", "northeast");
    add_exit(BATHRM + "arc_sw", "northwest");

    add_npc(BATH + "npc/patron", 1, &->equip_me());
    add_npc(BATH + "npc/attendant", 1, &->equip_me());
}
