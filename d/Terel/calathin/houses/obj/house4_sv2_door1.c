/*
    House4_sv2_door1 
    Tomas 11171999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("house4_sv2_door1");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door", "door","north door"}));
    set_other_room(CALATHIN_DIR + "houses/house4_sv4");
    set_open(0);

}    


