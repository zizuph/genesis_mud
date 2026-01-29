inherit "/std/door.c";
#include "defs.h"

void
create_door()
{
   ::create_door();
   set_pass_command(({"north", "n"}));
   set_door_name(({"kitchen door", "door"}));
   set_other_room(CAVERNS_DIR+"foodhall");
   set_open(0);
   set_no_pick();
}
