/*
    Post office door 2
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("post_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door", "door","south door", "study door"}));
    set_other_room(WHITE + "guild/post");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
