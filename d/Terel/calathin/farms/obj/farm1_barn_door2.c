/*
 *  farm1_barn_door1.c  --  Tomas 11/21/1999
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("farm1_barn_door2");
    set_pass_command(({"s","south"}));
    set_door_name(({"barndoor","door","south barndoor","south door"}));
    set_other_room(CALATHIN_DIR + "farms/farm1d");
    set_open_mess(({"swings the barndoor open.\n", "The barndoor opens.\n"}));

    set_open(0);
        

}

