/* temple/doors/door1_b.c is cloned by temple/entrance.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void create_door()
{
    ::create_door();
    set_door_id("templedoor");
    set_pass_command(({"w", "west"}));
    set_door_name(({"golden door", "door"}));
    set_other_room(TEMPLE_DIR + "path4");
}
