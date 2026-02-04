/*
 *  farm1_gate.c  --  Tomas 11/21/1999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("farm1_gate");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden gate","gate","east door"}));
    set_other_room(CALATHIN_DIR + "farms/farm1");
    set_open_mess(({"unlatches then pushes the gate open.\n", "The gate swings open.\n"}));

    set_open(0);
        

}

