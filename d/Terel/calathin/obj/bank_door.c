
/*
     Bank door
 */
inherit "/std/door";

#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("bank_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(CALATHIN_DIR + "square1_2");


/* This door is open and not locked */
    set_open(0);
    set_locked(0);
}
