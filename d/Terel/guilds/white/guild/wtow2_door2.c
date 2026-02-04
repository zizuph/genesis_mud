/*
   west tower dor
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("west_tower2_door");
    set_pass_command(({"nw","northwest"}));
    set_door_name(({"wooden door", "door","northwest door","tower door"}));
    set_other_room(WHITE + "guild/wtower_2");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
