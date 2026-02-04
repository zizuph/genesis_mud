/*
    House3_treehouse_door trapdoor 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house3_th_door");
    set_pass_command(({"u","up"}));
    set_door_name(({"trap door","trapdoor"}));
    set_other_room(CALATHIN_DIR + "houses/house3_th");
    set_open_mess(({"pushes the trapdoor open.\n", "Someone opens the trapdoor from below.\n"}));
    set_open(0);
      
   

}

