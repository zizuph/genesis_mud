/* towncastle/doors/cdoor3_b.c is cloned by towncastle/cell_3.c */
inherit "/std/door";
 
#include "../default.h"
 
void
create_door()
{
    set_door_id("celldoor_3");
    set_pass_command(({ "w", "west" }));
    set_door_name(({ "cell door", "door" }));
    set_door_desc( "The door looks old, but quite solid.\n" );
 
    set_other_room(TCASTLE_DIR + "corridor_wend");
    set_open(0);
    set_locked(1);
    set_no_pick();
    set_key("dungeon_celldoor");
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_desc("The lock is well-oiled, as if in frequent use.\n");
}
