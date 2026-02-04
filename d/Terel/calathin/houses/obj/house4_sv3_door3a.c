/*
    House4_sv3_door3 
    Tomas 11171999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_sv3_door3");
    set_pass_command(({"w","west"}));
    set_door_name(({"oak door", "door","west door"}));
    set_other_room(CALATHIN_DIR + "houses/house4_sv3");
    set_open(0);

}    


