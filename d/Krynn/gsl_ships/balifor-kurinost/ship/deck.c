inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("deck of a small transport ship");
    set_long("This is the deck of a small transport ship. A small crew "+
        "keeps the ship moving with good speed.  The ship is mainly "+
        "used to transport Dragonarmy troops.  A hatch leads down to "+
        "cabin.\n");

    add_item(({"ship","vessel"}),
      "You stand on the deck of a small transport ship.\n");
    add_item("deck",
      "The deck is made of wooden planks closely fit together.\n");
    add_item(({"cabin","hatch"}),
      "A hatch leads down to a cabin below.\n");

    add_exit(CABIN,"down",0);

    set_deck_sound("@@sounds");
}


sounds()
{
    if (random(2))
        return "The ship sails quickly over the smooth sea waters.\n";

    return "The sails fill with wind as the ship glides forward.\n";
}

