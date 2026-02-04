/*
    House4_yard.c door    
    Tomas 10271999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4d_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door", "door","south door"}));
    set_other_room(CALATHIN_DIR + "houses/house4d");
    set_open_mess(({"opens the door.\n", "The door opens.\n"}));
    set_open(0);
   
}    


