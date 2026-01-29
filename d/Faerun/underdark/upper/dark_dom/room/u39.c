#include "../defs.h"

inherit STD("room");

public void
dark_dom(void)
{
    set_short("You are in a narrow passage somewhere in the Dark Dominion");
    set_long("You find yourself within a narrow passage in the Dark Dominion.  "+
	"The rough, irregular walls mark this passageway "+
	"as natural, as opposed to having been carved out by someone, or "+
	"something. A dark narrow passage lead to the north and south. \n");

    add_item(({"sides","side","irregular walls","walls","wall"}),
	"The walls are nothing but bare uncut stone.\n");

    add_exit("u40", "north", check_follow);
    add_exit("u38", "south", check_follow);
 }