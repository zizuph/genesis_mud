
/*
    Skin shop door
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("gem_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"purple door", "door"}));
    set_other_room(CALATHIN_DIR + "roads/road_w02");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
