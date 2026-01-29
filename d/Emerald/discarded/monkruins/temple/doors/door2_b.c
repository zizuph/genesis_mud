/* temple/doors/door2_b.c is cloned by temple/monastery.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void create_door()
{
    ::create_door();
    set_door_id("monasterydoor");
    set_pass_command(({"w", "west"}));
    set_door_name(({"small door", "door"}));
    set_other_room(TEMPLE_DIR + "court_ne");
    set_open(0);
}
