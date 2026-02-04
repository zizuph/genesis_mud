/*
    House4_gh.c  door    
    Tomas 10271999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_gh_door");
    set_pass_command(({"w","west"}));
    add_name("west door");
    set_door_name(({"glass door", "door","west door"}));
    set_other_room(CALATHIN_DIR + "houses/house4_gh");
    set_open_mess(({"the glass door opens.\n", "The glass door opens.\n"}));       
    set_open(0);
   
}    


