/*  
 * Door into Queen's mirror room. It is locked from this end
 * Key is rewarded after the Queen's Quest is completed.
 * Called by ~telseron/castle/q_closet.c
 * Coded Finwe, March 1997
 */
 
inherit "/std/door";
 
#include "/d/Emerald/defs.h" 
 
void
create_door()
{
    set_door_id("mirror_door");
    set_pass_command( ({ "ne", "northeast" }) );
    set_door_name( "door"  );
    set_door_desc("The door is carved from a single piece of maple " +
        "and polished to a deep shine. The grain of the wood is a " +
        "dark contrast in the door, almost like many golden rivers " +
        "running the length of surface.\n");
    set_other_room( TOWNSHIP_DIR + "castle/mirror_room");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_locked(1);
    set_open(0);
    set_pick(100);
    set_key(8675309);
}
