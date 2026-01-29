inherit "/std/door";

#include "/d/Emerald/defs.h"

void create_door()
{
    ::create_door();
    set_door_id("objgate");
    set_pass_command(({"w", "west"}));
    set_door_name(({"bronze gate", "gate"}));
    set_other_room(VILLAGE_DIR + "centre");
}
