/* temple/doors/celldoor3_b.c is cloned by temple/cell4.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void create_door()
{
    ::create_door();
    set_door_id("celldoor3");
    set_pass_command(({"w", "west"}));
    set_door_name(({"cell door", "door"}));
    set_other_room(TEMPLE_DIR + "dungeon3");
    set_open(0);
}
