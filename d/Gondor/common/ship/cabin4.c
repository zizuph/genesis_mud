#pragma save_binary

inherit "/d/Genesis/ship/cabin";
#include "/d/Gondor/defs.h"

void
create_cabin()
{
    set_short("A warm and cosy cabin inside the corsair ship");
    set_long(BSN("This cabin is warm and cosy and indeed a good "+
	     "place to ride out the sometimes bad weather of the seas. You "+
	     "feel very secure here. There's a small table with some maps and "+
	     "the whole room is illuminated by a lantern in the ceiling. A "+
	     "set of finely crafted mahogany stairs lead up to the deck. "+
	     "Another set of plain, wooden stairs lead down."));
    add_item("lantern", BSN("The lantern is secured in the ceiling. "+
	     "It is a large and probably very expensive brass lantern with an "+
	     "oil container that should last quite a while."));
    add_item(({"table", "mahogany table"}), BSN("Like so many other "+
	     "things on this ship, the table is made out of finest mahogany "+
	     "despite its small size but it has some faintly visible marks "+
	     "and scratches upon its formerly polished surface, indicating "+
	     "that it is frequently used. On the table are some maps."));
    add_item(({"map", "maps"}), BSN("The maps are nautical maps and "+
	     "there seem to be several doublets, some being riddled with marks "+
	     "lines and notations while others seem brand new. Alas, you find "+
	     "no treasure map."));
    add_exit(SHIP_DIR + "deck4", "up", 0);
    add_exit(SHIP_DIR + "slavedeck4", "down", 0);
}