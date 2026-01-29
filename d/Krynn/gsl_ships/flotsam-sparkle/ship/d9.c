#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>

inherit "/d/Krynn/std/deck";

void
create_deck()
{

    set_short("before some stairs to the upper aft deck");
    set_long("You stand at the aft of the main deck of the " +
      "Golden Lion, before some wooden stairs that lead up to " +
      "upper aft deck, the deck where the helmsman steers the " +
      "vessel in a dance where its music is the captains hoarse " +
      "orders.\n");

    add_item(({"aft","main deck","deck"}),
      "You stand to the aft of the main deck of the Golden Lion.\n");
    add_item(({"ship","Golden Lion","golden lion"}),
      "You stand upon the main deck of the Golden Lion, " +
      "a fit and trim ship that sails these dangerous seas.\n");
    add_item(({"upper aft deck","aft deck","helmsman"}),
      "Above you is the upper aft deck, the deck where the " +
      "helmsman skillfully guides the ship through the seas she " +
      "travels.\n");
    add_item(({"wooden stairs","stairs"}),
      "Wooden stairs lead up before you to the upper aft deck.\n");

    add_exit("d3","fore",0);
    add_exit("u2","up",0);
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

