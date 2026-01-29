/* temple/doors/celldoor3_a.c is cloned by temple/dungeon3.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void create_door()
{
    ::create_door();
    set_door_id("celldoor3");
    set_pass_command(({"e", "east"}));
    set_door_name(({"cell door", "door"}));
    set_other_room(TEMPLE_DIR + "cell4");
    set_open(0);
}
