inherit "/std/door";

#include "/d/Emerald/defs.h"

void create_door()
{
    ::create_door();
    set_door_id("towerdoor");
    set_pass_command(({"n", "north"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(VILLAGE_DIR + "ground");
    set_open(0);
    set_locked(1);
    set_no_pick();
    set_key(66601);
}
