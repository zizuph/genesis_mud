inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("On the ship");
    set_long("You're standing on a magnificent ship, your hair " +
	"rustling in the wind. A cabin is further back on the ship, " +
	"and a ladder " +
	"leads down to the rowing deck. From here you get a splendid " +
	"view of your surroundings.\n");

    add_item("oars", "@@oars");

    add_exit(SHIP_D + "cabin", "aft", 0);
    add_exit(SHIP_D + "rowingdeck", "down", 0);
    add_exit(SHIP_D + "for", "forward", 0);

    set_deck_sound("@@sounds");
}

sounds()
{
    if (random(2))
	return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

