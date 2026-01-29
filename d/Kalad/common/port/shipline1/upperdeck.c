inherit "/d/Genesis/ship/deck";
#include "../default.h"

create_deck()
{
    ::create_deck();
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("The upperdeck");
    set_long("You are on the deck of the clipper ship.\n"+
      "Six tiers of masts lie on the expansive deck of the ship, billowing white "+
      "sails unfurled in the wind. On the highest mast you can see a crow's "+
      "nest, where "+
      "lookouts watch for pirates and other navigational hazards. To the "+
      "aft lies the ship's cabin.\n");
    add_item(({"masts","mast"}),
      "They lie along the ship's center line, running lengthwise. They "+
      "tower dozens of feet into the salty air. The tallest mast, in the "+
      "center has a crow's nest at its peak.\n");
    add_item(({"nest"}),
      "An observation post high up on the central mast.\n");
    add_item(({"cabin"}),
      "A large structure at the rear of the ship. Several portholes are "+
      "visible on the sides.\n");
    add_exit(PORT + "shipline1/cabin", "aft");
}

