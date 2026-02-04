/*
    House1_bedrm1_door main door 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house1_bedrm1_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"oak door","door"}));
    set_other_room(CALATHIN_DIR + "houses/house1_hall");
    set_open(0);
      
   

}

