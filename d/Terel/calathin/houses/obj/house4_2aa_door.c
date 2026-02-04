/*
    House4_2b.c main door    
    Tomas 10271999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_2a_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden door", "door","oak door"}));
    set_other_room(CALATHIN_DIR + "houses/house4_2a");
    set_open_mess(({"opens the door.\n", "The door opens.\n"}));    

set_open(0);
   
}    


