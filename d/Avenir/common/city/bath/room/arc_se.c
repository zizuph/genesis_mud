#pragma strict_types
/*
 * ~/arc_se.c
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
    set_short("Southeast Arcade");
    set_long("The southeastern section of the arcade which circles the "+
	"public bath. Fingers of mist wrap around the pedestals of "+
	"the columns that support a series of arches through which "+
	"the pool of water can be glimpsed. To the southeast is "+
	"a heavy door.\n"); 

    ARCADE;

    add_item("number", "It is the number 10.\n");
    add_cmd_item("number", "read", "It is the number 10.\n");

    add_exit(BATHRM + "arc_e", "northeast");
    add_exit(BATHRM + "arc_m", "southwest");

    bath_door("ten", "priv_10", "se");
}
