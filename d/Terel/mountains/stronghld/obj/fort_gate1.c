/*
 *  fort_gate.c  --  Tomas 01/04/2000
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("fort_gate");
    set_pass_command(({"w","west"}));
    set_door_name(({"metal gate","gate","west gate"}));
    set_other_room(MOUNTAIN_DIR + "stronghld/forta");
    set_open_mess(({"raises the gate.\n", "The gate rises.\n"}));
    set_open(0);
        

}

