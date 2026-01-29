#include "../defs.h"

inherit STD("room");

public void
dark_dom(void)
{
    set_short("You are in a tunnel somewhere in the Dark Dominion");
    set_long("You find yourself within a wide tunnel in the Dark Dominion.  "+
	"The rough, irregular walls mark this passageway "+
	"as natural, as opposed to having been carved out by someone, or "+
	"something. Dark passages lead to the north and southwest. \n");

    add_item(({"sides","side","irregular walls","walls","wall"}),
	"The walls are nothing but bare uncut stone.\n");

    add_exit("u35", "southwest", check_follow);
    add_exit("u37", "north", check_follow);
 }