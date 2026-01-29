#pragma strict_types
/*
 * ~/arc_n.c
 *
 * North Arcade
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
    set_short("North Arcade");
    set_long("This is the north arcade. A mist rises from the south, "+
	"where the sounds of a fountain and muted voices can be heard. "+
	"The room is warm and filled with the pungent scent "+
	"of herbs. Through the haze you can barely see two open "+
	"doorways, one leading northeast, the other, northwest.\n");

    ARCADE;

    add_exit(BATHRM + "steps_n", "south");
    add_exit(BATHRM + "arc_nw", "southwest");
    add_exit(BATHRM + "arc_ne", "southeast");
}
