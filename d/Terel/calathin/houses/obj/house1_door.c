/*
    House1.c main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house1_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(CALATHIN_DIR + "houses/house1_lr");
    set_open(0);
    set_locked(1);
    set_pick(1);
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");
    
   

}

