/*
 *  farm2_gate.c  --  Tomas 01/04/2000
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("farm2_gate");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden gate","gate","west gate"}));
    set_other_room(CALATHIN_DIR + "paths/track_n04");
    set_open_mess(({"unlatches then pushes the gate open.\n", "The gate swings open.\n"}));

    set_open(0);
        

}

