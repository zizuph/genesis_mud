/*
    Playhouse 2 door
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("play_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden door", "door", "east door"}));
    set_other_room(CALATHIN_DIR + "playhouse");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
