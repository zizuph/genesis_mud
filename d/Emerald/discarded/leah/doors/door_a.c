inherit "/std/door";

#include "/d/Emerald/defs.h"

void create_door()
{
    ::create_door();
    set_door_id("towerdoor");
    set_pass_command(({"s", "south"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(VILLAGE_DIR + "garden1");
}
