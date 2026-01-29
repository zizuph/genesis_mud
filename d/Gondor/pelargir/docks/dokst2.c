#pragma strict_types

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Sailor;

void
reset_room()
{
    Sailor = add_citizen(Sailor, PELAR_DIR + "npc/swashb");
}

public int
block_npc()
{
    if (TP->query_npc())
	return 1;
    return 0;
}

void
create_room()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("This is Sailor's Boulevard. Along this stretch one "
      + "can find all sorts of sailors and their hangouts. To the east "
      + "are the vast docks of Pelargir, and to the west is another "
      + "sailors' building. The boulevard stretches on to the north "
      + "and south."));
    add_dockships();
    add_cobble();
    add_item(({"building","sailors' building"}), BSN("The building "
      + "that stands west sports a bit less grime than the rest of "
      + "the docks. Above the door is a huge sign with the words:")
      + "\t'HARBOUR MASTER'\n");
    add_exit(PELAR_DIR + "docks/dokst1",    "north", 0);
    add_exit(PELAR_DIR + "docks/dock3",     "east",  0);
    add_exit(PELAR_DIR + "docks/dokst3",    "south", 0);
    add_exit(PELAR_DIR + "docks/shipmastr", "west",  block_npc);

    reset_room();
}

