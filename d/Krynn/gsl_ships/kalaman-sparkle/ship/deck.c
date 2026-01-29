#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit "/d/Krynn/std/gsl_deck";

void
create_room()
{
  ::create_shiproom();
  set_short("On the ship");
  set_long("You're standing on a magnificent ship, your hair " +
           "rustling in the wind. A cabin is further back on the ship, " +
           "and a ladder " +
           "leads down to the rowing deck. From here you get a splendid " +
           "view of your surroundings.\n");

  add_item("oars", "You notice oars sticking out from each side of the ship.\n");

  add_exit(CABIN, "aft", 0);
  add_exit(ROWINGDECK, "down", 0);
  add_exit(FORE, "forward", 0);

  set_deck_sound("@@sounds");
  set_is_deck(1);
}

sounds()
{
    if (random(2))
      return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

