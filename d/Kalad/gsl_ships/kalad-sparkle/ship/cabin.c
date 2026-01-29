#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();
    add_prop(ROOM_I_INSIDE,1);
    set_short("Captain's Cabin");
    set_long("You stand within the captain's chambers.\n"+
      "Inside here you can see many navigational instruments, such as "+
      "compasses and sextants mounted on the walls. On the far side of the "+
      "cabin is a large redwood desk. An iron lantern hangs from the ceiling. "+
      "Several portholes look outside.\n");
    add_item(({"instruments","instrument","compasses","sextants","compass","sextant"}),
      "All manner of navigational tools can be seen, carefully mounted on "+
      "the cabin walls.\n");
    add_item(({"large redwood desk","redwood desk","desk"}),
      "A simple wooden desk with several maps spread out on top.\n");
    add_item(({"maps","map"}),
      "Nautical maps of the routes between Kalad and Sparkle.\n");
    add_item(({"portholes","porthole"}),
      "Looking out the holes you see the rolling waves of the sea.\n");
    add_item(({"iron lantern","lantern"}),"It fills the cabin with a wan, "+
      "cheerless light.\n");
    add_item(({"ceiling"}),"It is just plain hardwood.\n");
    add_exit(DECK,   "out");
    add_exit(PCABIN, "in");
}

