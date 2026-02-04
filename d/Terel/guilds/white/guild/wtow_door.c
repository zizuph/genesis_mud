/*
   west tower dor
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("west_tower_door");
    set_pass_command(({"se","southeast"}));
    set_door_name(({"wooden door", "door","southeast door","tower door"}));
    set_other_room(WHITE + "guild/hall_w3");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
