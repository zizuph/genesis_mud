/*
    Temple Doors
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("temple_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"ornate door", "door","north door","temple door"}));
    set_other_room(WHITE + "guild/temple");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
