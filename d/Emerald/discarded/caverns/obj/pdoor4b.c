inherit "/std/door";
#include "defs.h"

/*
* The normal create routine
*/
void
create_door()
{
   set_door_id("prison_door_4");
   set_pass_command(({"w","west"}));
   set_door_name(({"cell door","door","iron bar door",
            "heavy door","iron door","barred door",
            "heavy barred door","heavy iron door"}));
   set_door_desc(
      "It is a heavy door made of solid iron. "+
      "The iron bars are rusted from years of exposure "+
      "to the humid salty climate.\n");
   set_other_room(THIS_DIR+"5jail");
   set_lock_name("lock");
   set_unlock_command("unlock");
   set_locked(1);
   set_key(6970);
   set_open(0);
   set_str(45);
   set_pick(30);
}
