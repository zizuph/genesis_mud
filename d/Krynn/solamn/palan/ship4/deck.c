inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("On the ship");
    set_long("You're standing on a well crafted and fairly large passenger " +
	     "ship, your hair rustling in the wind. A cabin is further " +
	     "back on the ship, and a ladder leads down to the rowing " +
	     "deck. From here you get a splendid view of your surround" +
	     "ings.\n");

    add_item("oars", "@@oars");

    add_exit(SHIP_D + "cabin", "aft", 0);
    add_exit(SHIP_D + "rowingdeck", "down", 0);

    set_deck_sound("@@sounds");
}

sounds()
{
    switch(random(4))
      {
	case 0: return "The ship sways slightly in the wind.\n";
	case 1: return "The ship makes a turn back into the wind.\n";
	case 2: return "The ship turns gracefully out of the wind.\n";
	case 3: return "The ship is rocking gently with the waves.\n";
	default: return "The ship moves in the wind.\n";
      }
}

