/*
    House4_2e.c main door    
    Tomas 10271999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_2db_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door", "door","west door"}));
      set_other_room(CALATHIN_DIR + "houses/house4_2d");
    set_open(0);
    set_locked(0);
    set_pick(1);
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");
}    


