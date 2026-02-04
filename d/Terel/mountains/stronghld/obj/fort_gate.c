/*
 *  fort_gate.c  --  Tomas 01/15/2000
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("fort_gate");
    set_pass_command(({"e","east"}));
    set_door_name(({"metal gate","gate","east gate"}));
    set_other_room(MOUNTAIN_DIR + "stronghld/fielde");
    set_open_mess(({"raises the gate.\n", "The gate rises.\n"}));
    set_open(0);
        

}

