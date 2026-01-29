inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("Deck of a long ferry");
    set_long("You stand upon the deck of a long ferry that " +
      "travels up and down the Vingaard River, stopping at " +
      "Kalaman and the Keep to drop off passengers and cargo. " +
      "An open door leads to a small cabin at the back of the " +
      "boat.\n");

    add_item(({"open door","door"}),
      "An open door leads into a small cabin.\n");
    add_item(({"ferry","long ferry","river boat","boat"}),
      "You stand upon the deck on a long river boat. Woo!\n");
    add_item(({"cabin","small cabin"}),
      "There is a small cabin at the back on the boat, just "+
      "large enough for someone to stretch out in.\n");
    add_item("deck","You stand upon the deck of a long river boat.\n");
    add_item("cargo","The cargo on the boat is of little interest.\n");

    add_exit(SHIP_D + "cabin","aft",0);


    set_deck_sound("@@sounds");
}


sounds()
{
    if (random(2))
	return "The ferry slowly glides along the Vingaard River.\n";

    return "The ferry rocks slightly as it makes its way along " +
    "the Vingaard River.\n";
}

