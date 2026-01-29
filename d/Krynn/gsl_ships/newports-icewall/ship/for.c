inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("On the foredeck of the schooner");
    set_long("You're standing in the narrow prow of the ship. " +
        " As you look down, you can't help but notice that the entire " +
        " bow of the ship has been plated with metal, and a heavy bar " +
        " of what looks like brass lines to prow, perhaps to break any " +
        " icebergs the ship might hit." +
	"\n");

    add_exit(TDIR + "deck", "aft", 0);
    set_no_disembark();

    set_deck_sound("@@sounds");
}


sounds()
{
    if (random(3))
    return "The ship splashes into a high wave, causing water to " +
        "spray onto the deck.\n";
	return "The ship sways slightly in the wind.\n";

    return "Using favourable currents, the ship streams ahead.\n";
}

