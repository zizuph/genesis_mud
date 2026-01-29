/* towncastle/doors/cdoor3_a.c is cloned by towncastle/corridor_wend.c */
inherit "/std/door";
 
#include "../default.h"
 
void
create_door()
{
    set_door_id("celldoor_3");
    set_pass_command(({ "e", "east" }));
    set_door_name(({ "cell door", "door", "east cell door", "east door" }));
    set_door_desc( "The door looks old, but quite solid. You can "+
		  "hear some sounds from the other side of it.\n" );
 
    set_other_room(TCASTLE_DIR + "cell_3");
    set_open(0);
    set_locked(1);
    set_key("dungeon_celldoor");
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_desc("The lock is well-oiled, as if in frequent use.\n");
}
