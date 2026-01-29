inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

public int
block_down()
{
    if (this_player()->query_prop(OBJ_I_WEIGHT) > 90000)
    {
        write("As you step onto the ladder, you notice the ropes tighten, " +
            "barely able to hold your weight.  It is far too dangerous " +
            "to continue down.\n");
        return 1;
    }

    return 0;
}

void
create_room()
{
    set_short("Small cave");
    set_long("A small natural cave.  The blackness of the stone " +
        "walls absorbs what little light shines in from the entrance, " +
        "making it quite dismal.  At the far end of the cave, you " +
        "notice a rather large tunnel leading down.  A rope ladder " +
        "extends down into it.\n");

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 0);

    add_exit("enter", "south");
    add_exit("lair5", "down", block_down, 2, 1);

    clone_object(THIEF_LAIR_DIR + "obj/platform")->move(this_object(), 1);
}
