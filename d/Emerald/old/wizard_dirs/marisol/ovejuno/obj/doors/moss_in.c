inherit "/std/door";
#include "defs.h"

object
create_door()
{

    set_door_id("_mossd_");
    set_pass_command(({"n", "north"}));
    set_door_name(({"wooden door","door"}));
    set_open(1);
    set_other_room(VILLAGE + "moss_herb_shop");
}
