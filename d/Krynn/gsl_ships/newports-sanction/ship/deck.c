inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("deck of a troop ferry");
    set_long("This is the deck of a lumbering troop ferry. It contains " +
        "nothing more than three masts and a large open hatch leading " +
        "down into the hold.\n");

    add_item(({"ship","vessel"}),
      "You stand on the deck of a lumbering troop ferry.\n");
    add_item("deck",
      "The deck sways beneath your feet.\n");
    add_item(({"hatch","hold","open hatch"}),
      "An open hatch leads down into the hold.\n");

    add_exit(CABIN,"down",0);

    set_deck_sound("@@sounds");
}


sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship cuts through the small waves.\n";
}

