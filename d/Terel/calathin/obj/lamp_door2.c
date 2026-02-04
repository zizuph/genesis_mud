/*
    Talok's door 2
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("pack_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"blue door", "door"}));
    set_other_room(CALATHIN_DIR + "lampshop");


/* This door is open and not locked */
    set_open(1);
    set_locked(0);
}
