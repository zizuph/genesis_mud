#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

#include "/d/Gondor/common/lib/time.h"

void
create_room()
{
  ::create_shiproom();
    set_short("a small cabin inside the corsair");
    set_long("This small cabin is a good "+
	     "place to ride out the sometimes bad weather of the seas. You "+
	     "feel very secure here. There is a small table with some maps and "+
	     "the whole room is illuminated by a lantern in the ceiling. A "+
	     "set of crude wooden stairs leads up to the deck.\n");
    add_item("lantern", "The lantern is secured in the ceiling. "+
	     "It is a cheap brass lantern with an "+
	     "oil container that should last quite a while.\n");
    add_item(({"table", "small table"}), 
        "A small wooden table, covered by maps.\n");
    add_item(({"map", "maps"}), "The maps are nautical maps and "+
	     "there seem to be several doublets, some being riddled with marks "+
	     "lines and notations while others seem brand new. Alas, you find "+
	     "no treasure map.\n");
    add_item(({"stairs", "wooden stairs", "crude wooden stairs"}), "There "+
	     "is nothing special about the stairs. They lead up to the deck above.\n");
    add_exit(DECK, "up", 0);
}
