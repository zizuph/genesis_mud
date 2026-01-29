inherit "/std/door";

#include "/d/Emerald/defs.h"

void create_door()
{
   set_door_id("cottagedoor");
   set_pass_command(({"w", "west"}));
   set_door_name(({"blue door", "door"}));
   set_other_room(VILLAGE_DIR + "g6");
    set_open(0);
}
