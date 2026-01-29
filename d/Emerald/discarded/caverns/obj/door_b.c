inherit "/std/door";

#include "defs.h"

/*
* The normal create routine
*/
void
create_door()
{
   set_name("door");
   set_door_id("guild_door");
   set_pass_command(({"w","west"}));
   set_door_name(({"stone door", "door"}));
   set_door_desc("It has a large symbol engraved on it.\n");
   set_lock_command("lock");
   set_lock_name("lock");
    set_unlock_command("_this_door_sealed_for_time_being_by_alaron_");
   set_open(0);
    /* set_other_room(PIRATES_DIR + "cave3") */
    set_other_room("/d/Genesis/obj/statue");
    set_no_pick();
    set_locked(1);
    set_key(66603);
}
