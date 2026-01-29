inherit "/std/door";
#include "defs.h"

/*
* The normal create routine
*/
void
create_door()
{
   set_door_id("guild_door");
   set_pass_command(({"e","east"}));
   set_door_name(({"stone door", "door"}));
   set_other_room(CAVERNS_DIR+"main5");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   set_open(0);
   set_locked(0);
   set_pick(20);
}
