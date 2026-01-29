#pragma strict_types
/*
 * ~/arc_e.c
 *
 * East Arcade
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
    set_short("East Arcade");
    set_long("This is the east arcade. Through clouds of steam you can "+
	"just glimpse the fountain at the center of the pool. The "+
	"sound of water falling is soothing to the ear. Northeast "+
	"and southeast are two open doorways. A bench overlooks the "+
	"pool, providing a place to relax and inhale the thick, "+
	"herb-scented air.\n");

    ARCADE;

    add_exit(BATHRM + "arc_se", "southwest");
    add_exit(BATHRM + "arc_ne", "northwest");

    add_object(COM +"obj/bench");
}
