/*
    House4_gha_door.c  door    
    Tomas 10271999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_gh_door");
    set_pass_command(({"e","east"}));
    add_name("east door");
    set_door_name(({"glass door", "door","east door"}));
      set_other_room(CALATHIN_DIR + "houses/house4_yard2");
    set_open_mess(({"the glass door opens.\n", "The glass door opens.\n"}));  
    set_open(0);
  
}    


