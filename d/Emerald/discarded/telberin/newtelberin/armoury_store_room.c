#include "defs.h"

inherit TELBERIN_ROOM;
inherit "/lib/store_support";

#include <stdproperties.h>

void
create_telberin_room()
{
    set_short("Armory");
    set_long("This is the armory where all the weapons and armours are kept.\n");

    set_max_values(30, 3);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("armoury", "south", 0);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
