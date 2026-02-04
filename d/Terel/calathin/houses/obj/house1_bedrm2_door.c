/*
    House1_bedrm2_door main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house1_bedrm2_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(CALATHIN_DIR + "houses/house1_hall");
    set_open(0);
      
   

}

