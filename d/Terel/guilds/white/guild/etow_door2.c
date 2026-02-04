/*
   west garden dor
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("east_tower_door");
    set_pass_command(({"ne","northeast"}));
    set_door_name(({"wooden door", "door","northeast door","tower door"}));
    set_other_room(WHITE + "guild/etower_1");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
