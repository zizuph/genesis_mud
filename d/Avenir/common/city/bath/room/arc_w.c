#pragma strict_types
/*
 * ~/arc_w.c
 *
 * West Arcade
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
    set_short("West Arcade");
    set_long("This is the west arcade. Through clouds of steam you can "+
	"just glimpse the fountain at the center of the pool. You "+
	"find the sound of falling water soothing to the ear. "+
	"Northwest and southwest are two open doorways through "+
	"you can see colourful fabrics. A bench overlooks the pool, "+
	"providing a place to relax and inhale the thick, "+
	"herb-scented air.\n");

    ARCADE;

    add_exit(BATHRM + "arc_sw", "southeast");
    add_exit(BATHRM + "arc_nw", "northeast");

    add_object(COM +"obj/bench");
}
