/* temple/doors/celldoor1_b.c is cloned by temple/cell1.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void create_door()
{
    ::create_door();
    set_door_id("celldoor1");
    set_pass_command(({"e", "east"}));
    set_door_name(({"cell door", "door"}));
    set_other_room(TEMPLE_DIR + "dungeon1");
    set_open(0);
    set_locked(1);
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_key("ringq_door");
    set_pick(120);
}
