/*
    House1_bedrm1a_door.c main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house1_bedrm1_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door","door","north door"}));
    set_other_room(CALATHIN_DIR + "houses/house1_bedrm1");
    set_open(0);
    add_name("north door");
    

}

