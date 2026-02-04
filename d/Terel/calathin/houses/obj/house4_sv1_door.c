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
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden door", "door","east door"}));
    set_other_room(CALATHIN_DIR + "houses/house4_sv1");
    set_open(0);
    
}    


