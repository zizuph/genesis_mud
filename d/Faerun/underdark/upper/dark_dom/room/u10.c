#include "../defs.h"

inherit STD("room");

public void
dark_dom(void)
{
    set_short("You are in a tunnel somewhere in the Dark Dominion");
    set_long("You find yourself within a wide tunnel in the Dark Dominion, sides sloping "+
	"towards the top. The rough, irregular walls mark this passageway "+
	"as natural, as opposed to having been carved out by someone, or "+
	"something. Dark passages lead to the west and east.\n");

    add_item(({"sides","side","irregular walls","walls","wall"}),
	"The walls are nothing but bare uncut stone.\n");

    add_exit("u9", "west", check_follow);
    add_exit("u11", "east", check_follow);
}
