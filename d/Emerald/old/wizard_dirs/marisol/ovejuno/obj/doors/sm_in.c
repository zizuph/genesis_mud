inherit "/std/door";
#include "defs.h"

object
create_door()
{

    set_door_id("_smdoor_");
    set_pass_command(({"e", "east"}));
    set_door_name(({"wooden door","door"}));
    set_open(1);
    set_other_room(VILLAGE + "sm_house");
}
