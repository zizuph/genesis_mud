/*
    House2_bedrm2a_door.c main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house2_bedrm_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(CALATHIN_DIR + "houses/house2a");
    set_open(0);

}

