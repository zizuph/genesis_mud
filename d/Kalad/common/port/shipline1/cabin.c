#include "../default.h"
inherit "/std/room";

void
create_room()
{
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
      "Nautical maps of the routes between Kalad and the Shire.\n");
    add_item(({"portholes","porthole"}),
      "Looking out the holes you see the rolling waves of the sea.\n");
    add_item(({"iron lantern","lantern"}),"It fills the cabin with a wan, "+
      "cheerless light.\n");
    add_item(({"ceiling"}),"It is just plain hardwood.\n");
    add_exit(PORT + "shipline1/upperdeck", "out");
    add_exit(PORT + "shipline1/pcabin", "in");
}

