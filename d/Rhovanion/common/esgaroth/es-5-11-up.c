inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"

#define BACKPACK OBJ_DIR+"backpack"

create_room()
{
    set_short("What are you doing here?");
    set_long("What are you doing here?\n");

    create_backpacks();
}

create_backpacks()
{
    int i;
    i = 3 - sizeof(all_inventory());
    while (i-- > 0)
        clone_object(BACKPACK)->move(this_object(), 1);
}

leave_inv(object ob)
{
     set_alarm(100.0, 0.0, "create_backpacks");
    ::leave_inv(ob);
}
