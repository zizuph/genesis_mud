#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Far corner of the Seahawk. Quite dusty here");
    set_long("This is the far corner at the stern of the ship. A large iron "+
      "cannon sits on the side of this vessel, pointing south out over the docks "+
      "and the bay. Wooden barrels sit in one corner. Squeeking noises emanate "+
      "from below the floor.\n");
    add_item(({"large iron cannon","large cannon","iron cannon","cannon"}),
      "An ancient weapon of war, used by the captain of the Seahawk back in "+
      "the ship's heyday. It is now covered with streaks of rust, "+
      "apparently from lack of proper maintenance.\n");
    add_item(({"docks","dock"}),"You can see the wooden piers that "+
      "surround this vessel to the west, south and east.\n");
    add_item(({"bay"}),"The sparkling waters of the bay mirror the "+
      "deep blue sky above.\n");
    add_item(({"deep blue sky","deep sky","blue sky","sky"}),"A mirror "+
      "image of the bay below.\n");
    add_item(({"wooden barrels","barrels","barrel"}),"Storage cases "+
      "for the cannon's gunpowder.\n");
    add_item(({"floor"}),"The upper deck of the ship. Its slightly "+
      "warped boards look aged and weathered but seem to hold up your "+
      "weight easily.\n");
    add_item(({"slightly warped boards","warped boards","boards","board"}),
      "Visible beneath the wooden floor of the deck are the tiny holes of "+
      "ship rats.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/boat9", "north");
    add_exit(PORT + "seahawk/boat7", "east");
}

