inherit "/d/Genesis/ship/deck";
#include "../default.h"

create_deck()
{
    ::create_deck();
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("The upper deck of the passage ship");
    set_long("You are on the upper deck of the passage ship, exposed "+
      "to the whipping sea wind and the harsh sting of sea water. A few "+
      "deckhands can be seen diligently making sure that nothing on deck "+
      "goes amiss, insuring your safe passage. Two large masts stand in the "+
      "center of the deck, providing a place of attachment for the ship's "+
      "sails. In the aft section is located a dryer place, the deck's cabin.\n");
    add_item(({"upper deck","deck"}),"It is slightly slippery from the "+
      "constant spray of sea water.\n");
    add_item(({"deckhands","deckhand"}),"The young men look quite busy "+
      "with their work, as they are constantly moving about the deck like "+
      "so many ants.\n");
    add_item(({"large masts","masts","mast"}),"Large wooden poles planted "+
      "along the ship's center line.\n");
    add_item(({"sails","sail"}),"Large white canvases that power this "+
      "ship's journeys by harnessing the sea wind.\n");
    add_item(({"cabin"}),"A fairly large structure located in the ship's "+
      "aft, or rear section.\n");
    add_exit(PORT + "shipline5/cabin", "aft");
}

