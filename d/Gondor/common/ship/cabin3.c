#pragma save_binary

inherit "/d/Genesis/ship/cabin";
#include "/d/Gondor/defs.h"

void
create_cabin()
{
    set_short("A warm and cosy cabin inside the magnificent ship");
    set_long(BSN("This cabin is warm and cosy and indeed a good "+
	     "place to ride out the sometimes bad weather of the seas. You "+
	     "feel very secure here. There's a small table with some maps and "+
	     "the whole room is illuminated by a lantern in the ceiling. A "+
             "set of finely crafted mahogany stairs lead up to the deck. "));
    add_item("lantern", break_string("The lantern is secured in the ceiling. "+
	     "It is a large and probably very expensive brass lantern with an "+
	     "oil container that should last quite a while.\n",76));
    add_item(({"table", "mahogany table"}), break_string("Like so many other "+
	     "things on this ship, the table is made out of finest mahogany "+
	     "despite its small size but it has some faintly visible marks "+
	     "and scratches upon its formerly polished surface, indicating "+
	     "that it is frequently used. On the table are some maps.\n",76));
    add_item(({"map", "maps"}), break_string("The maps are nautical maps and "+
	     "there seem to be several doublets, some being riddled with marks "+
	     "lines and notations while others seem brand new. Alas, you find "+
	     "no treasure map.\n",76));
    add_exit("/d/Gondor/common/ship/deck3", "up", 0);
}