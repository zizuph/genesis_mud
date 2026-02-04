/*
    House3.c main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("fortk_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(MOUNTAIN_DIR + "stronghld/fortk");
    set_open_mess(({"opens the door.\n", "The door opens.\n"}));
    set_open(0);
    set_locked(1);
    set_pick(100);
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");
}

