#pragma strict_types
/*
 * ~/corr.c
 *
 * Corridor leading into the Bath proper
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
    set_short("Corridor");
    set_long("A wide corridor lined with shelves. Diffuse light floods "+
	"the room from a concealed source. The scent of herbs "+
	"drifts in on clouds of steam. The muted sounds of falling "+
	"water and murmuring voices come from the north.\n"); 

    add_item("light", "It is soft and easy on the eyes.\n");

    add_exit(BATHRM + "desk", "south");
    add_exit(BATHRM + "arc_m", "north");

    add_npc(BATH + "npc/attendant", 1, &->equip_me());
}
