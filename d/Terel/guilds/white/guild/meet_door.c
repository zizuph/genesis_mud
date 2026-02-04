/*
   Meeting hall door
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("meet_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door", "door","south door"}));
    set_other_room(WHITE + "guild/hall2_1");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
