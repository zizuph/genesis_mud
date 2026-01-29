inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("On the ship");
    set_long(break_string("You're standing in the narrow prow of the ship." +
	" You feel the wind in your hair and occasionally you hear a " +
	"seagull cry out over the waters." +
	"\n", 70));

    add_item("oars", "@@oars");

    add_exit(SHIP_D + "deck", "aft", 0);
    set_no_disembark();

    set_deck_sound("@@sounds");
}

oars()
{
    string str;

    str = "You notice oars sticking out from each side of the ship.\n";

    if (environment(ship)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
	str += "They move with astonishing force and speed.\n";
    else
	str += "They rest motionless now.\n";

    return str;
}

sounds()
{
/*    if (file_name(environment(ship)) == TDIR + "lake1" ||
	    file_name(environment(ship)) == TDIR + "sea1")
	return "The captain chants a few strange words, and the ship makes\n" +
		"a tremendous leap in the air.\n";*/

    if (random(2))
	return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

