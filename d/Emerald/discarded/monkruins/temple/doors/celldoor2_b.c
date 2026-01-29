/* temple/doors/celldoor2_b.c is cloned by temple/cell2.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void create_door()
{
    ::create_door();
    set_door_id("celldoor2");
    set_pass_command(({"e", "east"}));
    set_door_name(({"cell door", "door"}));
    set_other_room(TEMPLE_DIR + "dungeon2");
    set_open(0);
}
