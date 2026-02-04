/*
    House2_bedrm1_door.c main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house2_bedrm_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden door","east door"}));
    set_other_room(CALATHIN_DIR + "houses/house2b");
    set_open(0);

}

