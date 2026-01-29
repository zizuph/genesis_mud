inherit "/d/Krynn/std/deck";

#include <stdproperties.h>
#include "local.h"

void
create_deck()
{
    set_short("upper deck of a small courier vessel");
    set_long("This is the upper deck of a small courier vessel. It is sleek " +
        "and looks very fast. There are stairs leading down to the " +
        "lower deck.\n");

    add_item(({"ship","vessel"}),
      "You stand on the upper deck of a small courier vessel.\n");
    add_item(({"deck","upper deck"}), "The deck sways beneath your feet.\n");
    add_item(({"lower deck","stairs"}),
		"The stairs lead down to a lower deck. "+
		"Travelers not invited by Dragonarmy have to stay there.\n");

    add_exit(DECK,"down",0);

    set_deck_sound("@@sounds");
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";
    return "The ship cuts through the waves.\n";
}
