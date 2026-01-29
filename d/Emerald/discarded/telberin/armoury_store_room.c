inherit "/std/room";
inherit "/lib/store_support";

#include "default.h"
#include <stdproperties.h>

void
create_room()
{
    set_short("Armory");
    set_long("This is the armory where all the weapons and armours are kept.\n");

    set_max_values(30, 3);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(THIS_DIR + "armoury", "south", 0);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
