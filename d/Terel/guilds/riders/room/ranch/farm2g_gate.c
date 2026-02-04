/*
 *  farm2g_gate.c  --  Tomas 01/04/2000
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("farm2g_gate");
    set_pass_command(({"s","south"}));
    set_door_name(({"mesh gate","gate","south gate"}));
    set_other_room(CALATHIN_DIR + "farms/farm2h");
    set_open_mess(({"unlatches then pushes the gate open.\n", "The gate swings open.\n"}));

    set_open(0);
        

}

