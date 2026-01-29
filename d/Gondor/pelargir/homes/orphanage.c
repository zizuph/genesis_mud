inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define ORPHAN		({ "borphan", "dorphan", "lorphan", })

object *orphans = allocate(3);

void
add_stuff()
{
    int     i;

    for (i = 0; i < sizeof(orphans); i++)
    {
        if (!objectp(orphans[i]))
        {
            orphans[i] = clone_object(PELAR_DIR + "npc/" + ORPHAN[i]);
            orphans[i]->arm_me();
            orphans[i]->move_living("down", TO);
        }
    }
}

void
create_room()
{
    set_short("an old orphanage");
    set_long(BSN("This is the orphanage of Pelargir, though it is more "
      + "of a hang out for street urchins. A narrow doorway is leading "
      + "into an adjoining room to the east. Fortunately, it does not seem "
      + "the orphans lack for company, the refuse lying about this "
      + "part of town has attracted a few rats."));
    add_item("rats",BSN("There are a few of these "+
       "scampering about in the rafters, impossible to catch."));
    add_item(({"rooms","adjoining rooms"}),
        "Most are locked tightly shut.\n");
    add_item("boards",BSN("You should better not touch them as "
      + "something could definitely break."));
    add_item("refuse", BSN("The refuse here includes a bit of offal, a "
      + "few tattered rags, and a touch of condensed grime."));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PELAR_DIR + "homes/orph_paint","east",0);
    add_exit(PELAR_DIR + "streets/earnil02", "south", 0);

    add_stuff();
}

void
reset_room()
{
    add_stuff();
}

