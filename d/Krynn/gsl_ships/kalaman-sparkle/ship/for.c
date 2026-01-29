#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();
    set_short("On the ship");
    set_long("You're standing in the narrow prow of the ship." +
             " You feel the wind in your hair and occasionally you hear a " +
             "seagull cry out over the waters.\n");
    
    add_item("oars", "You notice oars sticking out from each side of the ship.\n");
    
    add_exit(DECK, "aft", 0);
    
    set_deck_sound("@@sounds");
    set_is_deck(1);
}

sounds()
{
  if (random(2))
    return "The ship sways slightly in the wind.\n";
  
  return "The ship is rocking gently with the waves.\n";
}

