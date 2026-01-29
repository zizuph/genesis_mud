inherit "/d/Krynn/std/cabin";

#include <stdproperties.h>
#include "local.h"

void
create_cabin()
{
    set_short("A small, empty cabin");
    set_long("You stand in a small cabin at the back of the ferry. " +
      "There is very little here of interest, with only a sleeping " +
      "mat that the ferry master probably sleeps on while in port.\n");

    add_item(({"sleeping mat","mat"}),
      "Urg, it is quite filthy. You think you would rather sleep " +
      "on the deck rather than on this poor excuse for a sleeping " +
      "mat.\n");

    add_exit(SHIP_D + "deck","out",0);

    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

sounds()
{
    /*    if (file_name(environment(ship)) == TDIR + "sea1" ||
	  file_name(environment(ship)) == TDIR + "lake1")
    return "The ship shakes incredibly hard and you hear a big splash!\n";*/

    if (random(2))
	return "The cabin sways slightly as the ferry moves along the river.\n";

    return "The cabin creaks as the ferry moves along the river.\n";
}

