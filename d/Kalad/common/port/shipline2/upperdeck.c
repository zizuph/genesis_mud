inherit "/d/Genesis/ship/deck";
#include "../default.h"

create_deck()
{
    ::create_deck();
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("The upperdeck");
    set_long("This is the top deck of the spartan ship.\n"+
      "The wooden planks of the upperdeck are slightly slick with foam from "+
      "the sea, yet still clear of any debris. A single large mast rises "+
      "from the center of the deck, its overly large sails billowing in the "+
      "wind. A closed hatch leads down to the lower decks while the captain's cabin "+
      "is to the aft.\n");
    add_item(({"top deck","deck","upperdeck","wooden planks","wooden plank","planks","plank"}),
      "The surface of the deck is clean and well-kept.\n");
    add_item(({"large mast","mast"}),"A large pole upon which the ship's "+
      "sails are attacked. A large flag with the symbol of a blue wave flutters "+
      "from its peak.\n");
    add_item(({"overly large sails","large sails","sails","sail"}),
      "Great billowing canvases of white that power this large ship on its "+
      "travels across the sea.\n");
    add_item(({"large flag", "flag"}),
      "It flutters proudly from the top of the mainsail.\n");
    add_item(({"closed hatch","hatch"}),"A large iron door set in the deck that "+
      "bars the way into the lower decks of the ship. The hatch is locked.\n");
    add_exit(PORT + "shipline2/cabin", "aft");
}

