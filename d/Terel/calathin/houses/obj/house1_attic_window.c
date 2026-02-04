/*
    House1_attic_window.c attic access 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("attic_window");
    set_pass_command(({"exit","exit"}));
    set_door_name(({"shuttered window", "window"}));
    set_other_room(CALATHIN_DIR + "houses/house1_roof");
    set_open(0);
    set_locked(0);
}

