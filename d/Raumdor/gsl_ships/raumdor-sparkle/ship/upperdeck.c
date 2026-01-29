#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

create_room()
{
    ::create_shiproom();

    set_short("The upperdeck");
    set_long("You are on the deck of the small barque. "+
      "The ship boards squeak and groan under your weight. "+
      "A single mast shoots straight up here, and on top you "+
      "see a giant cross. The breeze is cool, and the salty "+
      "air stings your nose. "+
      "Looking out over the rails, you see the sea.\n");
    add_item("cross","It is a wooden cross.\n");
    add_item("sea","The beautiful sparkling blue waves shine "+
      "in the light. The birds fly overhead, and you intake the cool "+
      "air.\n");
    add_exit(CABIN, "aft");
    set_is_deck(1);
}

