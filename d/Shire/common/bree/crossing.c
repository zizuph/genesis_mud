#include "defs.h"

inherit STAND_LIB + "rom";

create_rom()
{

   object hob;

    set_short("Crossing in the middle of Bree");
    set_long(
	"You are standing in a crossing in the middle of the town Bree. "+
	"The Great Eastroad turns from the south to the west here, and "+
	"another road goes further north to the North-Gate. To the east "+
	"you can see an archway leading into the most famous inn in Bree, "+
   "'The Prancing Pony'. To the north, you see the road has been repaved "+
    "and there are several new-looking buildings to the north.\n");

    clone_object("/d/Genesis/obj/donation/column")->move(this_object(), 1);
    add_exit(BREE_DIR + "townrm", "south", 0);
    add_exit(BREE_DIR + "townr1",  "west", 0);
    add_exit(BREE_DIR + "middle","north",0,2);
//    add_exit(BREE_DIR + "inn_yard", "east", 0);
    add_exit("/d/Shire/bree/rooms/town/innyard", "east",0);

    add_item(({"crossing","eastroad","great eastroad"}),
	"The road seems well trodden, as this is the major walk for "+
	"both adventurers and local inhabitants.\n");
    add_item(({"inn","pony","prancing pony","building"}),
	"It looks like a cosy house standing into the Bree-Hill. An "+
	"archway leads east into the building.\n");
    add_item(({"archway"}),
	"Into the building it leads. Perhaps you should do a visit "+
	"here? If so, just go east.\n");

   hob = clone_object(BREE_DIR + "npc/wanderer");
   hob->move(TO);
}

int
no_go()
{
    if((TP->query_wiz_level()) > 0)
    return 0;
    write("A mean hobbit stops you.\n");
    write("Hobbit says: Sorry, you have to wait for the master to finish his construction work here.\n");
    write("Hobbit leaves home.\n");
    return 1;
}

