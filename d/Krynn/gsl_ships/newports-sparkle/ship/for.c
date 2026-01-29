#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit "/d/Krynn/std/gsl_deck";

void
create_room()
{
  ::create_shiproom();

  set_short("On the ship");
  set_long("You're standing in the narrow prow of the ship." +
           " You feel the wind in your hair and occasionally you hear a " +
           "seagull cry out over the waters." +
           "\n");
  
  add_item("oars", "@@oars");
  
  add_exit(DECK, "aft", 0);
  
  set_deck_sound("@@sounds");
  set_is_deck(1);
}

oars()
{
    string str;

    str = "You notice oars sticking out from each side of the ship.\n";

    if (environment(query_ship())->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
      str += "They move with astonnishing force and speed.\n";
    else
      str += "They rest motionless now.\n";

    return str;
}

sounds()
{
    if (random(3))
      return "The ship splashes into a high wave, causing water to " +
        "spray onto the deck.\n";

    return "The ship is rocking gently with the waves.\n";
}

