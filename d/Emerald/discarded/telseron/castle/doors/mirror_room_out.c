/*
 * Door from the Queen's mirror room. 
 * It is unlocked inside the mirror room
 * Called by ~telseron/castle/mirror_room.c
 * Coded Finwe, March 1997
 */
 
inherit "/std/door";
 
#include "/d/Emerald/defs.h" 
 
void
create_door()
{
    set_door_id("mirror_door");
    set_pass_command( ({ "o", "out" }) );
    set_door_name( "door" );
    set_door_desc("The door is carved from a single piece of maple " +
        "and polished to a deep shine. The grain of the wood is a " +
        "dark contrast in the door, almost like many golden rivers" +
        "running the length of surface.\n");
    set_other_room( TOWNSHIP_DIR + "castle/q_closet");
    set_open(0);
    set_locked(0);
 
}
