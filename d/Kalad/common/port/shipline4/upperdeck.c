inherit "/d/Genesis/ship/deck";
#include "../default.h"

create_deck()
{
    ::create_deck();
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("The top deck of the transport ship");
    set_long("You are on the top deck of the transport ship.\n"+
      "Great unfurled sails billow out from the ship's main mast, catching "+
      "the awesome power of the wind, using it to speedily propel this ship "+
      "towards its next destination. The ship's cargo hold lies below you, "+
      "where trade goods are stored during passage on the sea. To the aft "+
      "lies the captain's cabin.\n");
    add_item(({"great unfurled sails","great sails","unfurled sails","sails","sail"}),
      "Large white canvas sails that fully harness the power of the sea.\n");
    add_item(({"main mast","mast"}),"A large wooden pole upon which "+
      "the ship's sails are attached.\n");
    add_item(({"cargo hold","hold"}),"A large wooden cover has been "+
      "place over the entrance. It is locked.\n");
    add_item(({"entrance"}),"Its been blocked by the wooden cover. There "+
      "is no way down into the hold.\n");
    add_item(({"large wooden cover","large cover","wooden cover","cover"}),
      "A square-shaped and very sturdy hatch used to make sure no seawater "+
      "enters the hold during travel.\n");
    add_item(({"cabin"}),"A large structure at the rear of the ship.\n");
    add_exit(PORT + "shipline4/cabin", "aft");
}

