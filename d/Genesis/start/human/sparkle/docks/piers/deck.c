#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>

#include "../../defs.h"

void
create_deck()
{
    set_short("On the galleon");
    set_long(break_string("You're standing on the deck of a well built " +
	"galleon. The wind is in your hair and you can smell the sea. " +
	"A small cabin is south. From here you get a splendid " +
	"view of your surroundings.\n", 70));

    add_exit(TOWN_DIR + "ship/cabin", "south");

    set_deck_sound("@@sounds");
}

string
sounds()
{
    if (random(2))
	return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}
