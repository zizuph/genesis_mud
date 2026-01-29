#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Shade1,
               Shade2;

public void
create_gondor()
{
    set_short("a dimly lit room");
    set_long(BSN("This seems to be the main hall of the Shades quarters. "+
  "A few tables and chairs are placed on the floor, and oil-lamps suspended "+
    "from the ceiling only dimly lights the room. A dark passageway "+
    "leads out east, and a set of curtains hangs on the south wall, "+
    "only partly covering another doorway. North is another small hall."));
    add_item(({"lamp","oil lamp","oil_lamps","oil lamps","lamps","oil-lamps"}),
	     "A couple of oil-lamps are burning quietly in a corner.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    add_item("doorway","The doorway is made of grey-white stone and leads south.");
    add_item(({"passage","passageway"}),"A dark corridor leads to the east, it doesn't look very safe.\n");
    add_item(({"chairs","chair"}),BSN("Simple wooden chairs, nothing special at " +
    "all."));
    add_item(({"tables","table"}), BSN("Wooden tables with heavy amounts of nicks and " +
				       "carvings from dagger points."));
    add_item(({"curtains","curtain"}) ,BSN("A set of dark black curtains drapped over the " +
					   "south wall cover a arch to the southern quarters."));
    add_item("walls","The walls are made of grey-white stone.\n");
    add_item("ground", "The ground is dusty and made of a grey-white stone.\n");
    add_item("ceiling", "The ceiling is low and made of a grey-white stone.\n");
    add_item("rug", "An old tattered rug lies on the floor, dirty and trampled.\n");
    add_item(({"carving","carvings"}),BSN(
          "There are many things carved into the table, mostly nicks and " +
          "marks made by the cut throat men who inhabit this hideout."));
    add_exit(SHADES_DIR + "hall2", "south", 0, 4);
    add_exit(SHADES_DIR + "corr2", "east",  0, 4);
    add_exit(SHADES_DIR + "hall3", "north", 0, 4);
    reset_room();
}

public void
reset_room()
{
    Shade1 = clone_npc(Shade1, SHADES_DIR+"shade");
    Shade2 = clone_npc(Shade2, SHADES_DIR+"shade2");
    Shade2->team_join(Shade1);
}
