/*
    Skin shop door 2
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("wep_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door", "door","north door"}));
    set_other_room(CALATHIN_DIR + "wepshop");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
