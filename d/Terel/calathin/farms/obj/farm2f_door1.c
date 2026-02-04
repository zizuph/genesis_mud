/*
 *  farm2f_door1.c  --  Tomas 11/21/1999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("farm2f_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door","door","north door"}));
    set_other_room(CALATHIN_DIR + "farms/farm2c");
    set_open_mess(({"opens the door.\n", "The door opens.\n"}));

    set_open(0);
        

}

