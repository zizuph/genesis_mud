inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("Deck of a great whaling vessel");
    set_long("You stand upon the deck of " +
	"a great ship made entirely of a strange and exotic white " +
	"wood. From the looks of its setup, it is a vessel " +
	"designed specifically for hunting the mighty beasts of " +
	"the sea. A hatch leads down to the cabin below.\n");

    add_item(({"ship","great ship","vessel"}),
      "You stand on the deck of a great ship made of exotic white wood.\n");
    add_item("deck",
      "The deck sways beneath your feet.\n");
    add_item(({"cabin","hatch"}),
      "A hatch leads down to a cabin below.\n");

    add_exit("cabin","down",0);

    set_deck_sound("@@sounds");
}


sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship glides smoothly through the calm waters.\n";
}

