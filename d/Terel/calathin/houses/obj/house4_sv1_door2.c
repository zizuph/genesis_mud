/*
    House4_sv1_door     
    Tomas 11171999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_sv1_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door", "door","oak door"}));
    set_other_room(CALATHIN_DIR + "houses/house4_yard2");
    set_open(0);

}    


