inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

object *ruf = allocate(2);

void
add_stuff()
{
    int     i;
    for (i = 0; i < sizeof(ruf); i++)
    {
        if (!objectp(ruf[i]))
        {
            ruf[i] = clone_object(PELAR_DIR + "npc/ruffian");
            ruf[i]->arm_me();
            ruf[i]->move_living("down", TO);
        }
    }
}

void
create_room()
{
    set_short("among a small cluster of houses");
    set_long(BSN("This is a dead end. The road here comes upon "+
        "the back of some building and is hedged in by houses to the "+
        "north and south. Because of the height of the building it is "+
        "exceptionally shady and dark here."));
    add_item("building",BSN("All you can see is the back of this " +
        "building. It is "+
        "fairly dirty and grimy, evidently this isn't a popular spot."));
    add_item(({"houses","buildings"}),BSN("These are the "+
        "houses of the common citizens of Pelargir."));
    add_item(({"shade","shadows"}),BSN("The shadows here give you an "+
        "edgy feeling, almost lonely."));

    add_exit(PELAR_DIR + "street/xroad","west",0);

    add_stuff();
}

void
reset_room()
{
    add_stuff();
}

