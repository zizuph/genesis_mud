/*
    Post offoce door
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("library_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door", "door","west door","library door"}));
    set_other_room(WHITE + "guild/library");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
