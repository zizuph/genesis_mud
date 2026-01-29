inherit "/std/door";
#include "defs.h"

create_door()
{

    set_door_id("_shop_door_");
    set_pass_command(({"n", "north"}));
    set_door_name(({"wooden door","door"}));
    set_open(0);
    set_other_room(VILLAGE + "store_ov.c");
}
