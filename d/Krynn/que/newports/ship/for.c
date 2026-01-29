inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("On the ship");
    set_long("You're standing in the narrow prow of the ship." +
	" You feel the wind in your hair and occasionally you hear a " +
	"seagull cry out over the waters." +
	"\n");

    add_item("oars", "@@oars");

    add_exit(TDIR + "deck", "aft", 0);
    set_no_disembark();

    set_deck_sound("@@sounds");
}

oars()
{
    string str;

    str = "You notice oars sticking out from each side of the ship.\n";

    if (environment(ship)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
	str += "They move with astonnishing force and speed.\n";
    else
	str += "They rest motionless now.\n";

    return str;
}

sounds()
{
    if (random(3))
    return "The ship splashes into a high wave, causing water to " +
        "spray onto the deck.\n";
	return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

