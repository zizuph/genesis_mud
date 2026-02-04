/*
    Stable Doors
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("stable_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"double door", "door","east door","stable door"}));
    set_other_room(WHITE + "guild/courtyard");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
