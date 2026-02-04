/*
    House1_roof_window.c attic access 
 */

inherit "/std/door";
#include "/d/Terel/include/Terel.h"

public void
create_door()
{
    ::create_door();

    set_door_id("attic_window");
    set_pass_command(({"in","in"}));
    set_door_name(({"shuttered window", "window"}));
    set_other_room(CALATHIN_DIR + "houses/house1_attic");
    set_open(0);
    set_locked(0);
}

