/*
    House4_yard1.c main door    
    Tomas 10271999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_2d_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden door", "door","east door"}));
    set_other_room(CALATHIN_DIR + "houses/house4_2d");
    set_open_mess(({"opens the door.\n", "The door opens.\n"}));
    set_open(0);
    
}    


