/*
    House1.c main door 
 */

inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house2_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(CALATHIN_DIR + "houses/house2");

    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* Noone is home, the door is locked */
    set_open(0);
    set_locked(0);
}

