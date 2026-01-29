inherit "/std/door";
#include "defs.h"

create_door()
{
//    int key_name;
    
//    key_name = call_other("/d/Shire/common/hollin/steel_key", "set_key_name");

    set_door_id("trolls_treasure_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"heavy door","door"}));
    set_other_room(STAND_DIR + "trolls_treasure");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_door_desc(
        "This is a heavily built door made of steel.\n"+
        "Probably once built by dwarves.\n");
    set_door_name(({"door","heavy door"}));
    set_pick(50);
    set_key(333222111);
//    set_key(key_name);
}
