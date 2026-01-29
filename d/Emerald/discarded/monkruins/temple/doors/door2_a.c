/* temple/doors/door2_a.c is cloned by temple/court_ne.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void create_door()
{
    ::create_door();
    set_door_id("monasterydoor");
    set_pass_command(({"e", "east"}));
    set_door_name(({"small door", "door"}));
    set_other_room(TEMPLE_DIR + "monastery");
    set_open(0);
}
