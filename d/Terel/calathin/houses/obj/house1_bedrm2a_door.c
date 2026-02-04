/*
    House1_bedrm2a_door.c main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house1_bedrm2_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door", "south door"}));
    set_other_room(CALATHIN_DIR + "houses/house1_bedrm2");
    set_open(0);
    add_name("south door");    

}

