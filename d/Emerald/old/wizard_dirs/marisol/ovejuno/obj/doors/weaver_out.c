inherit "/std/door";
#include "defs.h"

object
create_door()
{

    set_door_id("_weaver_");
    set_pass_command(({"s", "south"}));
    set_door_name(({"wooden door","door"}));
    set_open(0);
    set_other_room(VILLAGE + "clothes_shop");
}
